#include "stdafx.h"
#include "Ship.h"

// X is down-right
// Y is up-right
// Z is upwards

Ship::Ship(SHIP shipType) {
    memset(tileList, 0, sizeof(tileList[0][0][0]) * defaultShipSizeX * defaultShipSizeY * defaultShipSizeZ);
    switch(shipType) {
        case STARTER_SHIP:
            LoadFromFile("Assets/Ships/starterShip.csv");
            break;
        default:
            throw std::invalid_argument("Invalid Ship Type");
    }
} 

void Ship::LoadFromFile(std::string file) {
    std::ifstream shipFile(file);
    if(shipFile.is_open()) {
        char shipLine[50];
        char* lineTracer;
        int x = 0;
        int y = 0;
        int z = 0;
        shipSize.x = defaultShipSizeX;
        shipSize.y = defaultShipSizeY;
        shipSize.z = defaultShipSizeZ;
        Ship::TileType tileType;
        ShipTile::Orientation tileOrientation;
        // Determine lines in file
        while(shipFile.good() && shipFile.getline(shipLine, 50)) {
            y++;
        }
        // Go to beginning of file
        shipFile.clear();
        shipFile.seekg(0, std::ios::beg);
        // Read file from top down
        while(shipFile.good()) {
            shipFile.getline(shipLine, 50);
            // If end of file
            if(shipLine[0] == '\0') {
                // Stop reading file
                break;
            }
            lineTracer = shipLine;
            lineTracer--;
            do {
                switch(atoi(++lineTracer)) {
                    case -1:
                        tileType = Ship::TileType::SPACE;
                        break;
                    case 0:
                        tileType = Ship::TileType::FLOOR;
                        break;
                    case 1:
                        tileType = Ship::TileType::WALL;
                        break;
                    case 4:
                        tileOrientation = ShipTile::Orientation::NE;
                        tileType = Ship::TileType::WINDOW;
                        break;
                    case 5:
                        tileOrientation = ShipTile::Orientation::NW;
                        tileType = Ship::TileType::WINDOW;
                        break;
                    case 6:
                        tileOrientation = ShipTile::Orientation::SE;
                        tileType = Ship::TileType::WINDOW;
                        break;
                    case 7:
                        tileOrientation = ShipTile::Orientation::SW;
                        tileType = Ship::TileType::WINDOW;
                        break;
                    default:
                        throw std::invalid_argument("Read invalid tile type from ship file");
                }
                tileList[x][y][z] = CreateShipTile(tileType, x, y, z, tileOrientation);
                x++;
            } while(lineTracer = strpbrk(lineTracer, ",\n\r"));
            x = 0;
            y--;
        }
    } else {
        throw std::invalid_argument("Cannot locate " + file);
    }
}

Tile* Ship::CreateShipTile(TileType tileType,int x, int y, int z, ShipTile::Orientation orientation) {
    switch(tileType) {
        case Ship::TileType::SPACE:
            return nullptr;
        case Ship::TileType::FLOOR:
            return new Floor(x, y);
        case Ship::TileType::WALL:
            return new Wall(x, y);
        case Ship::TileType::WINDOW:
            return new Window(x, y, orientation);
    }
}

void Ship::Draw(sf::RenderWindow* window) {
    for(int z = shipSize.z - 1; z >= 0; z--) {
        for(int x = 0; x < shipSize.x; x++) {
            for(int y = shipSize.y - 1; y >= 0; y--) {
                if(tileList[x][y][z] != nullptr) {
                    tileList[x][y][z]->Draw(window);
                }
            }
        }
    }
}


Ship::~Ship()
{
}
