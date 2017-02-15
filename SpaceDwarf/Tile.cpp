#include "stdafx.h"
#include "Tile.h"

Tile::Tile() {
}

Tile::~Tile() {
}

void Tile::Draw(sf::RenderWindow* window) {
    window->draw(sprite);
}

void Tile::Transform() {
    //sprite.scale(0.3f, 0.3f);
}

void Tile::Translate(float x, float y) {
    sprite.move(x, y);
}

void Tile::Translate(sf::Vector2i pos) {
    sprite.move((sf::Vector2f)pos);
}

void Tile::Scale(int zoomDirection) {
    sprite.scale(zoomDirection * 0.2f, zoomDirection * 0.2f);
}
