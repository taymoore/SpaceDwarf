#include "stdafx.h"
#include "Ship.h"

// X is down-right
// Y is up-right
// Z is upwards

// Coordinates are z y x
Ship::TileType starterShip[defaultShipSizeZ][defaultShipSizeY][defaultShipSizeX] = {/*z = 0*/                                      /*x*/
                              {      {Ship::TileType::SPACE, Ship::TileType::WALL, Ship::TileType::WALL,  Ship::TileType::WALL, Ship::TileType::SPACE} ,
                                     {Ship::TileType::SPACE, Ship::TileType::WALL, Ship::TileType::FLOOR, Ship::TileType::WALL, Ship::TileType::SPACE},
                               /*y*/ {Ship::TileType::SPACE, Ship::TileType::WALL, Ship::TileType::FLOOR, Ship::TileType::WALL, Ship::TileType::SPACE},
                                     {Ship::TileType::SPACE, Ship::TileType::WALL, Ship::TileType::WALL,  Ship::TileType::WALL, Ship::TileType::SPACE}
                                     }
                                     };

Ship::Ship(sf::RenderWindow* window, SHIP shipType) {
    memset(tileList, 0, sizeof(tileList[0][0][0]) * defaultShipSizeX * defaultShipSizeY * defaultShipSizeZ);
    LoadFromFile("Assets/Ships/starterShip.csv", window);
    //TileType* defaultShip;
    //switch(shipType) {
    //    case STARTER_SHIP:
    //        defaultShip = &starterShip[0][0][0];
    //        shipSize.x = defaultShipSizeX;
    //        shipSize.y = defaultShipSizeY;
    //        shipSize.z = defaultShipSizeZ;
    //        break;
    //    default:
    //        defaultShip = &starterShip[0][0][0];
    //        shipSize.x = defaultShipSizeX;
    //        shipSize.y = defaultShipSizeY;
    //        shipSize.z = defaultShipSizeZ;
    //        break;
    //}

    //for(int z = 0; z < defaultShipSizeZ; z++) {
    //    for(int y = 0; y < defaultShipSizeY; y++) {
    //        for(int x = 0; x < defaultShipSizeX; x++) {
    //            tileList[x][y][z] = CreateShipTile(*(defaultShip + defaultShipSizeY * defaultShipSizeX * z + defaultShipSizeX * y + x), x, y, z);
    //        }
    //    }
    //}
} 

//Ship::TileType*** Ship::LoadFromFile(char* file) {
void Ship::LoadFromFile(std::string file, sf::RenderWindow* window) {
    // Allocate memory
    //Ship::TileType*** ship;
    //ship = new Ship::TileType**[defaultShipSizeX];
    //for(int x = 0; x < defaultShipSizeX; x++) {
    //    ship[x] = new Ship::TileType*[defaultShipSizeY];
    //    for(int y = 0; y < defaultShipSizeY; y++) {
    //        ship[x][y] = new Ship::TileType[defaultShipSizeZ];
    //    }
    //}
    std::ifstream shipFile(file);
    if(shipFile.is_open()) {
        char tileType[5];
        char* newLinePtr;
        int x = 0;
        int y = 0;
        int z = 0;
        shipSize.x = defaultShipSizeX;
        shipSize.y = defaultShipSizeY;
        shipSize.z = defaultShipSizeZ;
        while(shipFile.good()) {
            shipFile.getline(tileType, 5, ',');
            // If last entry
            if((newLinePtr = strchr(tileType, '\n')) != nullptr) {
                tileList[x][y][z] = CreateShipTile((Ship::TileType)atoi(tileType), x, y, z);
                window->clear();
                tileList[x][y][z]->Draw(window);
                window->display();
                x = 0;
                y++;
                tileList[x][y][z] = CreateShipTile((Ship::TileType)atoi(newLinePtr + 1), x, y, z);
                window->clear();
                tileList[x][y][z]->Draw(window);
                window->display();
                x++;
            } else {
                tileList[x][y][z] = CreateShipTile((Ship::TileType)atoi(tileType), x, y, z);
                window->clear();
                tileList[x][y][z]->Draw(window);
                window->display();
                x++;
            }
            //if(x >= defaultShipSizeX) {
            //    x = 0;
            //    y++;
            //}
            //if(y >= defaultShipSizeY) {
            //    y = 0;
            //    z++;
            //}
        }
    } else {
        throw std::invalid_argument("Cannot locate " + file);
    }
    //tileList[0][0][0] = new Floor(1, 1);
}

Tile* Ship::CreateShipTile(TileType tileType,int x, int y, int z) {
    switch(tileType) {
        case Ship::TileType::SPACE:
            return nullptr;
        case Ship::TileType::FLOOR:
            return new Floor(x, y);
        case Ship::TileType::WALL:
            return new Wall(x, y);
    }
}

void Ship::Draw(sf::RenderWindow* window) {
    for(int z = shipSize.z - 1; z >= 0; z--) {
        //for(int x = shipSize.x - 1; x >= 0; x--) {
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
