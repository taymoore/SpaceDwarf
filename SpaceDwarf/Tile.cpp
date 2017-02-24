#include "stdafx.h"
#include "Tile.h"
#include "ObjectTile.h"

Tile::Tile(Ship* ship) {
    this->ship = ship;
}

Tile::~Tile() {
}

void Tile::Draw(sf::RenderWindow* window) {
    sprite.setPosition(ship->spritePosition_sf + spriteOffset_pixel);
    sf::Transform rotTransform;
    rotTransform.rotate(ship->rotation, ship->spritePosition_sf);
    //rotTransform.translate(ship->spritePosition_sf + spriteOffset_pixel);
    window->draw(sprite, rotTransform);
}

//void Tile::addObjectTile(ObjectTile* objectTile) {
//    //objectTileList.push_back(objectTile);
//}
