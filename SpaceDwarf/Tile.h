#pragma once
#include <SFML\Graphics.hpp>

class Tile {
public:
    Tile();
    ~Tile();
    virtual void Draw(sf::RenderWindow* window);
    void Translate(float x, float y);
    void Translate(sf::Vector2i pos);
    void Transform();
    void Scale(int zoomDirection);
protected:
    sf::Sprite sprite;
};

