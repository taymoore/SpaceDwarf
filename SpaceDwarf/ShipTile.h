#pragma once
#include "Tile.h"
class ShipTile : public Tile {
public:
    static void Initialize();
    enum class Orientation {
        NE, // North East (up right)
        SE, // South East (down right)
        SW, // South West (down left)
        NW  // North West (up left)
    };
};

class Floor : public ShipTile {
public:
    Floor(int xPos, int yPos);
};

class Wall : public ShipTile {
public:
    Wall(int xPos, int yPos);
};

class Window : public ShipTile {
public:
    Window(int xPos, int yPos, ShipTile::Orientation orientation = ShipTile::Orientation::NE);
private:
    ShipTile::Orientation orientation;
    void SetOrientation(ShipTile::Orientation orientation);
};