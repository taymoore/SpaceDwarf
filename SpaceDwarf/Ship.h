#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "Structure.h"
#include "Tile.h"
#include "Box2D/Box2D.h"
#include "World.h"
#include "Arena.h"
#include "ShipPilot.h"

constexpr int defaultShipSizeX = 20;
constexpr int defaultShipSizeY = 20;
constexpr int defaultShipSizeZ = 2;

class Tile;
class Arena;
class ArenaFaction;
class ShipPilot;

class Ship : public Structure {
public:
    // Index of Tile type
    enum class TileType {
        SPACE,
        FLOOR,
        WALL
    };

    enum SHIP {
        STARTER_SHIP,
        RANDOM_ENEMY
    };
    Ship(int xPixel, int yPixel, int rot, b2World* b2World, ArenaFaction* arenaFaction, SHIP shipType = STARTER_SHIP);
	~Ship();
    void Draw(sf::RenderWindow* window);
    //sf::Vector2f getLocation();
    sf::Vector2f getShipSize_sf();
    b2Vec2 getShipSize_b2();
    b2Vec2 GetVelocity();
    void SetVelocity(const b2Vec2& velocity);

    void createFixture(b2FixtureDef* b2fixtureDef);

    //sf::Vector2f shipSize_sf;
    b2Vec2 shipSize_b2;

    // Update functions
    // factionList list of all factions in arena (including ship's faction)
    void Update(std::vector<ArenaFaction*>* factionList);

    ArenaFaction* getArenaFaction();

    void UpdatePosition();
    sf::Vector2f spritePosition_sf;
    b2Vec2 spritePosition_b2;
    b2Vec2 shipCentre_b2;
    //sf::Vector2f bodyPosition_sf;

    void DrawShipPilotDebug(sf::RenderWindow* window);

    void UpdateRotation();
    float rotation;

    std::vector<std::vector<std::vector<Tile*>>> tileList;   // Vectors in X, Y, Z
private:
    ShipPilot* shipPilot;
    //sf::Vector2f bodyLocation_Pixel;  // Location of ship in pixel coordinates
    ArenaFaction* arenaFaction;      // Arena faction this ship belongs to
    b2Body* shipBody;
    sf::Vector3i shipSize_Tile;      // Size of ship in tiles
    void LoadShipFromFile(std::string file, b2World* world);
    void LoadObjectsFromFile(std::string file, b2World* world);
    //std::vector<Engine*> shipEngineList;
};

