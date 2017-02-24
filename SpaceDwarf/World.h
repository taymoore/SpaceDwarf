#pragma once
#include "World.h"
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

class World {
public:
    World();
    ~World();

    static const int pixelsPerMeter;
    static const float pixelsPerTile;
    static const int metersPerTile;

    static const bool debugMode;

    // Scale conversion
    static b2Vec2 Pixel2Meter(const sf::Vector2f& pixelSize);
    static sf::Vector2f Meter2Pixel(float xMeter, float yMeter);

    static float sf2BoxAngle(float deg);
    static float box2SfAngle(float rad);

    // World Conversion
    static b2Vec2 sfPos2BoxPos(const sf::Vector2f& vec);
    static sf::Vector2f boxPos2SfPos(const b2Vec2& vec);
};

