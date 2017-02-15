#pragma once
#include <fstream>
#include <string>
#include "Structure.h"
#include "Tile.h"
#include "ShipTile.h"

constexpr int defaultShipSizeX = 6;
constexpr int defaultShipSizeY = 4;
constexpr int defaultShipSizeZ = 1;

class Ship : public Structure {
public:
    // Index of Tile type
    enum class TileType {
        SPACE = -1,
        FLOOR = 0,
        WALL = 1
    };

    enum SHIP {
        STARTER_SHIP,
        RANDOM_ENEMY
    };
    Ship(sf::RenderWindow* window, SHIP shipType = STARTER_SHIP);
	~Ship();
    Tile* tileList[defaultShipSizeX][defaultShipSizeY][defaultShipSizeZ];
    void Ship::Draw(sf::RenderWindow* window);
    void Ship::LoadFromFile(std::string file, sf::RenderWindow* window);
private:
    Tile* Ship::CreateShipTile(TileType tileType, int x, int y, int z);
    sf::Vector3i shipSize;
};

