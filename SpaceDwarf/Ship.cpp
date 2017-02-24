#include "stdafx.h"
#include "Ship.h"
#include "ShipTile.h"
//#include "ShipObject.h"

// X is down-right
// Y is up-right
// Z is upwards

Ship::Ship(int xPixel, int yPixel, int rot, b2World* b2World, ArenaFaction* arenaFaction, SHIP shipType) : arenaFaction(arenaFaction) {
    // Create physics
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Vec2 shipPosition_meter = World::Pixel2Meter(sf::Vector2f((float)xPixel, (float)yPixel));
    bodyDef.position.Set(shipPosition_meter.x, shipPosition_meter.y);
    shipBody = b2World->CreateBody(&bodyDef);

    // Load tiles
    switch(shipType) {
        case STARTER_SHIP:
            LoadShipFromFile("Assets/Ships/starterShip_Ship.csv", b2World);
            break;
        default:
            throw std::invalid_argument("Invalid Ship Type");
    }

    //// Create fixture
    //b2PolygonShape dynamicBox;
    ////dynamicBox.SetAsBox(3.5f, 3.0f);    // Dimentions are half-box size
    //b2Vec2 shipSize(shipSize_Tile.x, shipSize_Tile.y);
    //// This works when box is maximum size of ship
    //dynamicBox.SetAsBox(shipSize.x * World::metersPerTile / 2, shipSize.y * World::metersPerTile / 2);    // Dimentions are half-box size

    //b2FixtureDef fixtureDef;
    //fixtureDef.shape = &dynamicBox;
    //fixtureDef.density = 1.0f;
    //fixtureDef.friction = 0.3f;

    //shipBody->CreateFixture(&fixtureDef);
    ////shipBody->SetTransform(shipBody->GetPosition(), World::sf2BoxAngle(90));
    //shipBody->SetTransform(shipBody->GetPosition(), 0);
} 

void Ship::createFixture(b2FixtureDef* b2fixtureDef) {
    shipBody->CreateFixture(b2fixtureDef);
    //shipBody->SetTransform(shipBody->GetPosition(), World::sf2BoxAngle(90));
    //shipBody->SetTransform(shipBody->GetPosition(), 0);
}

//void Ship::Rotate() {
//    for(int x = 0; x < shipSize.x; x++) {
//        for(int y = 0; y < shipSize.y; y++) {
//            for(int z = 0; z < shipSize.z; z++) {
//                //tileList[x][y][z].rotate
//            }
//        }
//    }
//}
//
void Ship::LoadShipFromFile(std::string file, b2World* world) {
    std::ifstream shipFile(file);
    if(shipFile.is_open()) {
        char shipLine[50];
        char* lineTracer;
        sf::Vector3i tileIndex;
        Ship::TileType tileType;
        Wall::WallType wallType;
        Floor::FloorType floorType;
        // Read file from top down
        while(shipFile.good()) {
            shipFile.getline(shipLine, 50);
            // If end of file
            if(shipLine[0] == '\0') {
                // Stop reading file
                break;
            }
            // Interpret line
            lineTracer = shipLine;
            lineTracer--;
            do {
                // Allocate memory
                if(tileList.size() == tileIndex.x) {
                    tileList.push_back(std::vector<std::vector<Tile*>>());
                }
                if(tileIndex.z == 0) {
                    tileList.at(tileIndex.x).push_back(std::vector<Tile*>());
                }
                // Determine type of tile based on index
                switch(atoi(++lineTracer)) {
                    case -1:
                        tileType = Ship::TileType::SPACE;
                        break;
                    // Floor
                    case 12:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::NONE;
                        break;
                    case 7:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::NORTH;
                        break;
                    case 13:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::EAST;
                        break;
                    case 1:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::SOUTH;
                        break;
                    case 11:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::WEST;
                        break;
                    case 8:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::CORNER_INSIDE_NE;
                        break;
                    case 18:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::CORNER_INSIDE_SE;
                        break;
                    case 16:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::CORNER_INSIDE_SW;
                        break;
                    case 6:
                        tileType = Ship::TileType::FLOOR;
                        floorType = Floor::FloorType::CORNER_INSIDE_NW;
                        break;
                    // Wall
                    case 0:
                        tileType = Ship::TileType::WALL;
                        wallType = Wall::WallType::BLOCK;
                        break;
                    default:
                        throw std::invalid_argument("Read invalid tile type from ship file");
                }
                // Create Tile
                switch(tileType) {
                    case Ship::TileType::SPACE:
                        tileList.at(tileIndex.x).at(tileIndex.y).push_back(nullptr);
                        break;
                    case Ship::TileType::FLOOR:
                        tileList.at(tileIndex.x).at(tileIndex.y).push_back(new Floor(tileIndex.x, tileIndex.y, this, floorType));
                        break;
                    case Ship::TileType::WALL:
                        tileList.at(tileIndex.x).at(tileIndex.y).push_back(new Wall(tileIndex.x, tileIndex.y, wallType, this, world));
                        break;
                }
                tileIndex.x++;
            } while(lineTracer = strpbrk(lineTracer, ",\n\r"));
            tileIndex.x = 0;
            tileIndex.y++;
        }
        // Store ship size
        shipSize_Tile.x = tileList.size();
        shipSize_Tile.y = tileList.at(0).size();
        shipSize_Tile.z = tileList.at(0).at(0).size();

        shipSize_b2 = b2Vec2((float)shipSize_Tile.x * World::metersPerTile, - (float)shipSize_Tile.y * World::metersPerTile);
        //shipSize_sf = World::Meter2Pixel(shipSize_b2);

        // Create autopilot
        shipPilot = new FighterPilot(this);
    } else {
        throw std::invalid_argument("Cannot locate " + file);
    }
}

//void Ship::LoadObjectsFromFile(std::string file) {
//    std::ifstream objectFile(file);
//    if(objectFile.is_open()) {
//        char objectLine[50];
//        char* lineTracer;
//        //ShipObject::ObjectType objectType;
//        sf::Vector3i tileIndex;
//        Floor::FloorType floorType;
//        // Read file from top down
//        while(objectFile.good()) {
//            objectFile.getline(objectLine, 50);
//            // If end of file
//            if(objectLine[0] == '\0') {
//                // Stop reading file
//                break;
//            }
//            // Interpret line
//            lineTracer = objectLine;
//            lineTracer--;
//            do {
//                // Determine type of tile based on index
//                //switch(atoi(++lineTracer)) {
//                //    case 12:
//                //        objectType = ShipObject::ObjectType::ENGINE;
//                //        break;
//                //    default:
//                //        objectType = ShipObject::ObjectType::NONE;
//                //        break;
//                //}
//                // Create object
//                switch(objectType) {
//                    case ShipObject::ObjectType::ENGINE:
//                        //shipEngineList.push_back(new Engine(tileIndex.x, tileIndex.y));
//                        //tileList[tileIndex.x + 0][tileIndex.y + 0][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 0, tileIndex.y + 0, 0));
//                        //tileList[tileIndex.x + 1][tileIndex.y + 0][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 1, tileIndex.y + 0, 1));
//                        //tileList[tileIndex.x + 0][tileIndex.y + 1][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 0, tileIndex.y + 1, 2));
//                        //tileList[tileIndex.x + 1][tileIndex.y + 1][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 1, tileIndex.y + 1, 3));
//                        //tileList[tileIndex.x + 0][tileIndex.y + 2][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 0, tileIndex.y + 2, 4));
//                        //tileList[tileIndex.x + 1][tileIndex.y + 2][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 1, tileIndex.y + 2, 5));
//                        //tileList[tileIndex.x + 0][tileIndex.y + 3][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 0, tileIndex.y + 3, 6));
//                        //tileList[tileIndex.x + 1][tileIndex.y + 3][tileIndex.z]->addObjectTile(new EngineTile(tileIndex.x + 1, tileIndex.y + 3, 7));
//                        break;
//                    case ShipObject::ObjectType::NONE:
//                        break;
//                }
//                tileIndex.x++;
//            } while(lineTracer = strpbrk(lineTracer, ",\n\r"));
//            tileIndex.x = 0;
//            tileIndex.y++;
//        }
//        // Store ship size
//        shipSize.x = tileList.size();
//        shipSize.y = tileList.at(0).size();
//        shipSize.z = tileList.at(0).at(0).size();
//    } else {
//        throw std::invalid_argument("Cannot locate " + file);
//    }
//}

void Ship::Draw(sf::RenderWindow* window) {
    // Draw tiles
    for(int z = shipSize_Tile.z - 1; z >= 0; z--) {
        for(int x = 0; x < shipSize_Tile.x; x++) {
            for(int y = shipSize_Tile.y - 1; y >= 0; y--) {
                if(tileList[x][y][z] != nullptr) {
                    tileList[x][y][z]->Draw(window);
                }
            }
        }
    }

    // Draw body Centre
    sf::CircleShape bodyCentre(6);
    bodyCentre.setFillColor(sf::Color(100, 250, 50));
    bodyCentre.setPosition(World::boxPos2SfPos(shipCentre_b2) - sf::Vector2f(3, 3));
    window->draw(bodyCentre);

    // Draw debug lines
    //b2Vec2 halfShipSize_b2 = getShipSize_b2();
    //sf::Vertex line[] = {
    //    sf::Vertex(World::boxPos2SfPos(spritePosition_b2)),
    //    sf::Vertex(World::boxPos2SfPos(b2Vec2(spritePosition_b2.x, spritePosition_b2.y + (halfShipSize_b2.x / 2) * sin(World::sf2BoxAngle(rotation)) + (halfShipSize_b2.y / 2) * cos(World::sf2BoxAngle(rotation))))),
    //    sf::Vertex(World::boxPos2SfPos(b2Vec2(spritePosition_b2.x + (halfShipSize_b2.x / 2) * cos(World::sf2BoxAngle(rotation)) - (halfShipSize_b2.y / 2) * sin(World::sf2BoxAngle(rotation)), spritePosition_b2.y + (halfShipSize_b2.x / 2) * sin(World::sf2BoxAngle(rotation)) + (halfShipSize_b2.y / 2) * cos(World::sf2BoxAngle(rotation))))),
    //};
    //window->draw(line, 2, sf::Lines);
    //window->draw(line + 1, 2, sf::Lines);

}


void Ship::Update(std::vector<ArenaFaction*>* factionList) {
    // Update ship status
    UpdateRotation();
    UpdatePosition();

    // Run AI
}

inline void Ship::UpdatePosition() {
    //bodyPosition_sf = World::boxPos2SfPos(shipBody->GetPosition());
    spritePosition_b2 = shipBody->GetPosition();
    spritePosition_sf = World::boxPos2SfPos(spritePosition_b2);
    //sf::Vector2f halfShipSize = getShipSize();
    //halfShipSize.x /= 2;
    //halfShipSize.y /= 2;
    //spritePosition_sf = bodyPosition_sf - halfShipSize;
    //spritePosition_sf = bodyPosition_sf;

    //b2Vec2 halfShipSize_b2 = getShipSize_b2();
    ////halfShipSize_b2.x = (halfShipSize_b2.x / 2) * cos(shipBody->GetAngle()) - (halfShipSize_b2.y / 2) * sin(shipBody->GetAngle());
    ////halfShipSize_b2.y = (halfShipSize_b2.x / 2) * sin(shipBody->GetAngle()) + (halfShipSize_b2.y / 2) * cos(shipBody->GetAngle());
    //halfShipSize_b2.x = (halfShipSize_b2.x / 2) * cos(World::sf2BoxAngle(rotation)) - (halfShipSize_b2.y / 2) * sin(World::sf2BoxAngle(rotation));
    //halfShipSize_b2.y = (halfShipSize_b2.x / 2) * sin(World::sf2BoxAngle(rotation)) + (halfShipSize_b2.y / 2) * cos(World::sf2BoxAngle(rotation));
    ////halfShipSize_b2.x = halfShipSize_b2.x / 2;
    ////halfShipSize_b2.y = halfShipSize_b2.y / 2;
    ////halfShipSize_b2.x = 0;
    ////halfShipSize_b2.y = 0;
    //shipCentre_b2 = spritePosition_b2 + halfShipSize_b2;
    shipCentre_b2 = b2Vec2(spritePosition_b2.x + (shipSize_b2.x / 2) * cos(World::sf2BoxAngle(rotation)) - (shipSize_b2.y / 2) * sin(World::sf2BoxAngle(rotation)), spritePosition_b2.y + (shipSize_b2.x / 2) * sin(World::sf2BoxAngle(rotation)) + (shipSize_b2.y / 2) * cos(World::sf2BoxAngle(rotation)));
}

inline void Ship::UpdateRotation() {
    rotation = World::box2SfAngle(shipBody->GetAngle());
}

//sf::Vector2f Ship::getLocation() {
//    //return bodyLocation_Pixel;
//}


Ship::~Ship()
{
}

// Returns ship size in pixels
sf::Vector2f Ship::getShipSize_sf() {
    return sf::Vector2f((float)shipSize_Tile.x * World::pixelsPerTile, (float)shipSize_Tile.y * World::pixelsPerTile);
}

b2Vec2 Ship::getShipSize_b2() {
    return b2Vec2((float)((float)shipSize_Tile.x * World::metersPerTile), - (float)shipSize_Tile.y * World::metersPerTile);
}

b2Vec2 Ship::GetVelocity() {
    return shipBody->GetLinearVelocity();
}

void Ship::SetVelocity(const b2Vec2& velocity) {
    shipBody->SetLinearVelocity(velocity);
}

void Ship::DrawShipPilotDebug(sf::RenderWindow* window) {
    shipPilot->Draw(window);
}

ArenaFaction* Ship::getArenaFaction() {
    return arenaFaction;
}