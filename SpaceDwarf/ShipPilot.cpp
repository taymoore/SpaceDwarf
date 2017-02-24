#include "stdafx.h"
#include "ShipPilot.h"


// auto pilot
ShipPilot::ShipPilot(Ship* ownerShip) : ownerShip(ownerShip) {
}

ShipPilot::~ShipPilot() {
}

void ShipPilot::Update(std::vector<ArenaFaction*>* factionList) {
}

void ShipPilot::Draw(sf::RenderWindow* window) {
}

// Fighter Pilot
FighterPilot::FighterPilot(Ship* ownerShip) : ShipPilot(ownerShip) {
    targetShip = nullptr;
}

FighterPilot::~FighterPilot() {
}

void FighterPilot::Update(std::vector<ArenaFaction*>* factionList) {
    if(targetShip == nullptr) {
        // find target
        for(unsigned int i = 0; i < factionList->size(); i++) {
            // If this ship belongs to this faction
            if(factionList->at(i) != ownerShip->getArenaFaction()) {
                // Target first ship in faction
                // targetShip will be null if arenaFaction->shipList is empty
                targetShip = factionList->at(i)->shipAt(0);
            }
        }
    }
}

void FighterPilot::Draw(sf::RenderWindow* window) {
    // Draw line to target
    if(targetShip != nullptr) {
        sf::Vertex lineToTarget[] = {
            sf::Vertex(World::boxPos2SfPos(ownerShip->shipCentre_b2)),
            sf::Vertex(World::boxPos2SfPos(targetShip->shipCentre_b2))
        };
        window->draw(lineToTarget, 2, sf::Lines);
    }
}
