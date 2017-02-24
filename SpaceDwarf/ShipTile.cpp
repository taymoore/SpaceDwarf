#include "stdafx.h"
#include "ShipTile.h"

static sf::Texture shipTileset;

//shiptile::shiptile(b2body* shipbody) {
//    // create fixture
//    b2polygonshape dynamicbox;
//    // this works when box is maximum size of ship
//    //dynamicbox.setasbox(shipsize.x * world::meterspertile / 2, shipsize.y * world::meterspertile / 2);    // dimentions are half-box size
//    //b2vec2 tilecentre()
//    //dynamicbox.setasbox(world::meterspertile, world::meterspertile, );    // dimentions are half-box size
//
//    b2fixturedef fixturedef;
//    fixturedef.shape = &dynamicbox;
//    fixturedef.density = 1.0f;
//    fixturedef.friction = 0.3f;
//
//    shipbody->createfixture(&fixturedef);
//    //shipbody->settransform(shipbody->getposition(), world::sf2boxangle(90));
//    shipbody->settransform(shipbody->getposition(), 0);
//}
//
void ShipTile::Initialize() {
    if (!shipTileset.loadFromFile("Assets/Images/Ship.png")) {
        throw std::invalid_argument("Cannot locate Assets/Image/Ship.png");
    }
}

ShipTile::ShipTile(Ship* ship) : Tile(ship) {
}

Floor::Floor(int xPos, int yPos, Ship* ship, Floor::FloorType floorType) : ShipTile(ship) {
    // Load texture
    sprite.setTexture(shipTileset);
    int spriteIndex_X, spriteIndex_Y;
    this->floorType = floorType;
    switch(floorType) {
        case Floor::FloorType::NONE:
            spriteIndex_X = 2;
            spriteIndex_Y = 2;
            break;
        case Floor::FloorType::NORTH:
            spriteIndex_X = 2;
            spriteIndex_Y = 1;
            break;
        case Floor::FloorType::EAST:
            spriteIndex_X = 0;
            spriteIndex_Y = 1;
            break;
        case Floor::FloorType::SOUTH:
            spriteIndex_X = 1;
            spriteIndex_Y = 0;
            break;
        case Floor::FloorType::WEST:
            spriteIndex_X = 1;
            spriteIndex_Y = 2;
            break;
        case Floor::FloorType::CORNER_INSIDE_NE:
            spriteIndex_X = 3;
            spriteIndex_Y = 1;
            break;
        case Floor::FloorType::CORNER_INSIDE_SE:
            spriteIndex_X = 3;
            spriteIndex_Y = 3;
            break;
        case Floor::FloorType::CORNER_INSIDE_SW:
            spriteIndex_X = 1;
            spriteIndex_Y = 3;
            break;
        case Floor::FloorType::CORNER_INSIDE_NW:
            spriteIndex_X = 1;
            spriteIndex_Y = 1;
            break;
        case Floor::FloorType::CORNER_OUTSIDE_NE:
            spriteIndex_X = 4;
            spriteIndex_Y = 0;
            break;
        case Floor::FloorType::CORNER_OUTSIDE_SE:
            spriteIndex_X = 4;
            spriteIndex_Y = 4;
            break;
        case Floor::FloorType::CORNER_OUTSIDE_SW:
            spriteIndex_X = 0;
            spriteIndex_Y = 4;
            break;
        case Floor::FloorType::CORNER_OUTSIDE_NW:
            spriteIndex_X = 0;
            spriteIndex_Y = 0;
            break;
        case Floor::FloorType::ALCOVE_N:
            spriteIndex_X = 3;
            spriteIndex_Y = 0;
            break;
        case Floor::FloorType::ALCOVE_E:
            spriteIndex_X = 0;
            spriteIndex_Y = 2;
            break;
        case Floor::FloorType::ALCOVE_S:
            spriteIndex_X = 2;
            spriteIndex_Y = 0;
            break;
        case Floor::FloorType::ALCOVE_W:
            spriteIndex_X = 0;
            spriteIndex_Y = 3;
            break;
    }
    sf::IntRect spriteRect(spriteIndex_X * 100, spriteIndex_Y * 100, 100, 100);
    sprite.setTextureRect(spriteRect);

    spriteOffset_pixel.x = (float)(xPos * World::pixelsPerTile);
    spriteOffset_pixel.y = (float)(yPos * World::pixelsPerTile);
}

// xPos, yPos Sprite location in sprite coordinates
Wall::Wall(int xPos, int yPos, Wall::WallType wallType, Ship* ship, b2World* world) : ShipTile(ship) {
    // Load texture
    sprite.setTexture(shipTileset);
    int spriteIndex_X, spriteIndex_Y;
    this->wallType = wallType;
    switch(wallType) {
        case Wall::WallType::BLOCK:
            spriteIndex_X = 0;
            spriteIndex_Y = 0;
            break;
        case Wall::WallType::NORTH:
            spriteIndex_X = 2;
            spriteIndex_Y = 6;
            break;
        case Wall::WallType::EAST:
            spriteIndex_X = 0;
            spriteIndex_Y = 6;
            break;
        case Wall::WallType::SOUTH:
            spriteIndex_X = 1;
            spriteIndex_Y = 5;
            break;
        case Wall::WallType::WEST:
            spriteIndex_X = 1;
            spriteIndex_Y = 7;
            break;
        case Wall::WallType::CORNER_OUTSIDE_NE:
            spriteIndex_X = 0;
            spriteIndex_Y = 9;
            break;
        case Wall::WallType::CORNER_OUTSIDE_SE:
            spriteIndex_X = 0;
            spriteIndex_Y = 5;
            break;
        case Wall::WallType::CORNER_OUTSIDE_SW:
            spriteIndex_X = 4;
            spriteIndex_Y = 5;
            break;
        case Wall::WallType::CORNER_OUTSIDE_NW:
            spriteIndex_X = 4;
            spriteIndex_Y = 9;
            break;
        case Wall::WallType::CORNER_INSIDE_NE:
            spriteIndex_X = 3;
            spriteIndex_Y = 6;
            break;
        case Wall::WallType::CORNER_INSIDE_SE:
            spriteIndex_X = 3;
            spriteIndex_Y = 8;
            break;
        case Wall::WallType::CORNER_INSIDE_SW:
            spriteIndex_X = 1;
            spriteIndex_Y = 8;
            break;
        case Wall::WallType::CORNER_INSIDE_NW:
            spriteIndex_X = 1;
            spriteIndex_Y = 6;
            break;
        case Wall::WallType::ALCOVE_N:
            spriteIndex_X = 3;
            spriteIndex_Y = 5;
            break;
        case Wall::WallType::ALCOVE_E:
            spriteIndex_X = 0;
            spriteIndex_Y = 7;
            break;
        case Wall::WallType::ALCOVE_S:
            spriteIndex_X = 2;
            spriteIndex_Y = 5;
            break;
        case Wall::WallType::ALCOVE_W:
            spriteIndex_X = 0;
            spriteIndex_Y = 8;
            break;
    }
    sf::IntRect spriteRect(spriteIndex_X * (int)World::pixelsPerTile, spriteIndex_Y * (int)World::pixelsPerTile, (int)World::pixelsPerTile, (int)World::pixelsPerTile);
    sprite.setTextureRect(spriteRect);

    // Remember location of sprite relative to body
    spriteOffset_pixel.x = (float)(xPos * World::pixelsPerTile);
    spriteOffset_pixel.y = (float)(yPos * World::pixelsPerTile);

    // Create fixture
    b2PolygonShape wallShape;
    wallShape.SetAsBox((float)World::metersPerTile / 2, (float)World::metersPerTile / 2, World::sfPos2BoxPos(sf::Vector2f((float)xPos * World::pixelsPerTile + World::pixelsPerTile / 2, (float)yPos * World::pixelsPerTile + World::pixelsPerTile / 2)), 0);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wallShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    ship->createFixture(&fixtureDef);
}
