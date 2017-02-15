#pragma once
#include "Tile.h"
#include "Ship.h"
class ShipTile : public Tile {
public:
    static void Initialize();
};

class Floor : public ShipTile {
public:
    Floor(int xPos, int yPos);
};

class Wall : public ShipTile {
public:
    Wall(int xPos, int yPos);
};