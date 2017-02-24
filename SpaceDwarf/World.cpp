#include "stdafx.h"
#include "World.h"

const bool World::debugMode = true;

const int World::pixelsPerMeter = 100;
const float World::pixelsPerTile = 100;
const int World::metersPerTile = 1;

World::World() {
}


World::~World() {
}

// Use for scaling object size
b2Vec2 World::Pixel2Meter(const sf::Vector2f& pixelSize) {
    return b2Vec2(pixelSize.x / pixelsPerMeter, pixelSize.y / pixelsPerMeter);
}

// Use for scaling object size
sf::Vector2f World::Meter2Pixel(float xMeter, float yMeter) {
    sf::Vector2f pixelVector;
    pixelVector.x = xMeter * pixelsPerMeter;
    pixelVector.y = yMeter * pixelsPerMeter;
    return pixelVector;
}

float World::sf2BoxAngle(float deg) {
    return -deg * 0.0174533f;
}

float World::box2SfAngle(float rad) {
    return -rad * 57.29578f;
}

// Use for world coordinates
b2Vec2 World::sfPos2BoxPos(const sf::Vector2f& vec) {
    return b2Vec2(vec.x / pixelsPerMeter, -vec.y / pixelsPerMeter);
}

// Use for world coordinates
sf::Vector2f World::boxPos2SfPos(const b2Vec2& vec) {
    return sf::Vector2f(vec.x * pixelsPerMeter, -vec.y * pixelsPerMeter);
}
