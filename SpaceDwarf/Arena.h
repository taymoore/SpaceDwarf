#pragma once
#include <string>
#include <math.h>
#include <vector>
#include "Ship.h"
#include "ArenaFaction.h"
#include "Box2D\Box2D.h"

class Ship;
class ArenaFaction;

class Arena {
public:
    Arena(sf::RenderWindow* window);
    ~Arena();

    void Update();
    //void Draw(sf::RenderWindow* window);
    void Draw();

    std::vector<ArenaFaction*>* getArenaFactionList();
    std::vector<ArenaFaction*> factionList;
private:
    sf::RenderWindow* window;
    b2World world;


    //Ship* playerShip;
    //Ship* ship2;
};

