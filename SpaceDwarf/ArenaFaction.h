#pragma once
#include <vector>
#include "Ship.h"

class Ship;
class Arena;

class ArenaFaction {
public:
    ArenaFaction(Arena* arena);
    ~ArenaFaction();

    void AddShip(Ship* ship);
    void Update();
    void Draw(sf::RenderWindow* window);

    Ship* shipAt(unsigned int i);
private:
    std::vector<Ship*> shipList;
    Arena* arena;
};

