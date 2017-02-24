#pragma once
#include "Tile.h"
#include "World.h"
#include "Ship.h"
#include "Box2D/Box2D.h"

class ShipTile : public Tile {
public:
    static void Initialize();
    ShipTile(Ship* ship);
    //ShipTile(b2Body* shipBody);
    //enum class Orientation {
    //    NORTH,
    //    EAST,
    //    SOUTH,
    //    WEST
    //};
};

class Floor : public ShipTile {
public:
    enum class FloorType {
        NONE,
        NORTH,
        EAST,
        SOUTH,
        WEST,
        CORNER_INSIDE_NE,
        CORNER_INSIDE_SE,
        CORNER_INSIDE_SW,
        CORNER_INSIDE_NW,
        CORNER_OUTSIDE_NE,
        CORNER_OUTSIDE_SE,
        CORNER_OUTSIDE_SW,
        CORNER_OUTSIDE_NW,
        ALCOVE_N,
        ALCOVE_E,
        ALCOVE_S,
        ALCOVE_W
    };
    Floor(int xPos, int yPos, Ship* ship, Floor::FloorType floorType);
private:
    FloorType floorType;
};

class Wall : public ShipTile {
public:
    enum class WallType {
        BLOCK,
        NORTH,
        EAST,
        SOUTH,
        WEST,
        CORNER_OUTSIDE_NE,
        CORNER_OUTSIDE_SE,
        CORNER_OUTSIDE_SW,
        CORNER_OUTSIDE_NW,
        CORNER_INSIDE_NE,
        CORNER_INSIDE_SE,
        CORNER_INSIDE_SW,
        CORNER_INSIDE_NW,
        ALCOVE_N,
        ALCOVE_E,
        ALCOVE_S,
        ALCOVE_W
    };
    Wall(int xPos, int yPos, Wall::WallType wallType, Ship* ship, b2World* world);
private:
    WallType wallType;
};
