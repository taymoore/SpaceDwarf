#include "stdafx.h"
#include "ArenaFaction.h"


ArenaFaction::ArenaFaction(Arena* arena) : arena(arena) {
}


ArenaFaction::~ArenaFaction() {
}

// Adds ship to faction
void ArenaFaction::AddShip(Ship* ship) {
    shipList.push_back(ship);
}

// Update
void ArenaFaction::Update() {
    // Update ships
    for(unsigned int i = 0; i < shipList.size(); i++) {
        shipList[i]->Update(arena->getArenaFactionList());
    }
}

// Draw
void ArenaFaction::Draw(sf::RenderWindow* window) {
    // Draw ship sprite
    for(unsigned int i = 0; i < shipList.size(); i++) {
        shipList[i]->Draw(window);
    }

    // Draw autopilot debug
    if(World::debugMode == true) {
        for(unsigned int i = 0; i < shipList.size(); i++) {
            shipList[i]->DrawShipPilotDebug(window);
        }
    }

}

// Return ship at index
// Returns null if no ships in faction
Ship* ArenaFaction::shipAt(unsigned int i) {
    if(shipList.size() > 0) {
        return shipList.at(i);
    } else {
        return nullptr;
    }
}
