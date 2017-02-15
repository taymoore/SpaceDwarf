#pragma once
#include <fstream>
#include <string>
#include "Structure.h"
#include "Tile.h"
#include "ShipTile.h"

constexpr int defaultShipSizeX = 20;
constexpr int defaultShipSizeY = 20;
constexpr int defaultShipSizeZ = 2;

class Ship : public Structure {
public:
    // Index of Tile type
    enum class TileType {
        SPACE,
        FLOOR,
        WALL,
        WINDOW
    };

    enum SHIP {
        STARTER_SHIP,
        RANDOM_ENEMY
    };
    Ship(SHIP shipType = STARTER_SHIP);
	~Ship();
    Tile* tileList[defaultShipSizeX][defaultShipSizeY][defaultShipSizeZ];
    void Ship::Draw(sf::RenderWindow* window);
    void Ship::LoadFromFile(std::string file);
private:
    Tile* Ship::CreateShipTile(TileType tileType, int x, int y, int z, ShipTile::Orientation orientation);
    sf::Vector3i shipSize;
};

