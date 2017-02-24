#pragma once
#include <SFML\Graphics.hpp>
//#include "ObjectTile.h"
#include "Ship.h"

class Ship;

class Tile {
public:
    Tile(Ship* ship);
    ~Tile();
    //virtual void Tile::Draw(sf::Vector2f shipPosition, float rotation, sf::Vector2f shipSize, sf::RenderWindow* window);
    virtual void Tile::Draw(sf::RenderWindow* window);
    //void addObjectTile(ObjectTile* objectTile);
protected:
    sf::Sprite sprite;
    sf::Vector2f spriteOffset_pixel;  // Offset from b2Body in pixels
private:
    Ship* ship;
    //std::vector<ObjectTile*> objectTileList;
};

