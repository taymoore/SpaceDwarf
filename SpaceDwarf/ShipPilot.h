#pragma once
#include <vector>
#include "Arena.h"
#include "ArenaFaction.h"

class ShipPilot {
public:
    ShipPilot(Ship* ownerShip);
    ~ShipPilot();

    virtual void Update(std::vector<ArenaFaction*>* factionList);
    virtual void Draw(sf::RenderWindow* window);

protected:
    Ship* ownerShip;    // Ship this autopilot exists in
};

class FighterPilot : public ShipPilot {
public:
    FighterPilot(Ship* ownerShip);
    ~FighterPilot();

    void Update(std::vector<ArenaFaction*>* factionList);
    void Draw(sf::RenderWindow* window);

private:
    Ship* targetShip;   // Ship this autopilot is targetting
};