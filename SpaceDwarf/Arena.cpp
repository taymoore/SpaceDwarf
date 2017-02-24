#include "stdafx.h"
#include "Arena.h"

sf::Font font;

Arena::Arena(sf::RenderWindow* window) : world(b2Vec2(0.0f, -1.0f) /* gravity */) {
    // Remember window
    this->window = window;

    // Load assets
    font.loadFromFile("Assets/Fonts/OpenSans-Regular.ttf");

    // Ground Plane
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -25.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    //Build Factions
    factionList.push_back(new ArenaFaction(this));
    factionList[0]->AddShip(new Ship(0, 0, 0, &world, factionList[0]));
    factionList.push_back(new ArenaFaction(this));
    factionList[1]->AddShip(new Ship(-100, -1000, 0, &world, factionList[1]));
    // Build starter ship
    //playerShip = new Ship(000, 0, 0, &world, this);
    //ship2 = new Ship(-100, -1000, 0, &world, this);

    ////Ship velocity test
    //b2Vec2 vel = ship2->GetVelocity();
    //vel.y++;
    //vel.x++;
    //ship2->SetVelocity(vel);
}

Arena::~Arena() {
    for(int i = factionList.size(); i; i--) {
        //delete &factionList[i - 1];
        factionList.pop_back();
    }

    //delete playerShip;
    //delete ship2;
}

void Arena::Update() {
    // Set physics parameters
    constexpr float timeStep = 1.0f / 60.0f;
    constexpr int velocityInterations = 6;
    constexpr int positionIterations = 2;

    // Update physics
    world.Step(timeStep, velocityInterations, positionIterations);

    // update factions
    for(unsigned int i = 0; i < factionList.size(); i++) {
        factionList[i]->Update();
    }
    //playerShip->Update();
    //ship2->Update();
}

extern int lastFps;
extern sf::Vector2f screenSize;
//extern sf::Vector2i screenPosition;

void Arena::Draw() {
    window->clear();

    // Draw ships
    for(unsigned int i = 0; i < factionList.size(); i++) {
        factionList[i]->Draw(window);
    }
    //playerShip->Draw(window);
    //ship2->Draw(window);

    // Draw ground plane
    sf::Vertex line[] = {
        sf::Vertex(World::boxPos2SfPos(b2Vec2(-50, -15))),
        sf::Vertex(World::boxPos2SfPos(b2Vec2(50, -15)))
    };
    window->draw(line, 2, sf::Lines);

    // Draw FPS Counter
    char charStr[500];
    sprintf_s(charStr, "%d", lastFps);
    std::string str(charStr);
    sf::Text fpsText(str, font, screenSize.y / 80);
    //fpsText.setPosition(sf::Vector2f(screenPosition.x, screenPosition.y));
    window->draw(fpsText);

    //// Draw debug string
    //playerShip->UpdatePosition();
    //playerShip->UpdateRotation();
    //char charStr[500];
    //b2Vec2 shipSize_b2 = playerShip->getShipSize_b2();
    //b2Vec2 halfShipSize_b2 = playerShip->getShipSize_b2();
    //halfShipSize_b2.x = (halfShipSize_b2.x / 2) * cos(World::sf2BoxAngle(playerShip->rotation)) - (halfShipSize_b2.y / 2) * sin(World::sf2BoxAngle(playerShip->rotation));
    //halfShipSize_b2.y = (halfShipSize_b2.x / 2) * sin(World::sf2BoxAngle(playerShip->rotation)) + (halfShipSize_b2.y / 2) * cos(World::sf2BoxAngle(playerShip->rotation));
    //sprintf_s(charStr, "ShipLocation: %f, %f\n"
    //                    "Rotation: %f\n"
    //                    "Ship Size: %f, %f\n"
    //                    "Centre offset: %f, %f", 
    //                                                playerShip->spritePosition_b2.x, playerShip->spritePosition_b2.y, 
    //                                                playerShip->rotation,
    //                                                shipSize_b2.x, shipSize_b2.y,
    //                                                halfShipSize_b2.x, halfShipSize_b2.y);
    //std::string str(charStr);
    //sf::Text text(str, font, 100);
    //window->draw(text);

    window->display();
}

std::vector<ArenaFaction*>* Arena::getArenaFactionList() {
    return &factionList;
}
