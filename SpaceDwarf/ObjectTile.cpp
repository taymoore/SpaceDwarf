#include "stdafx.h"
#include "ObjectTile.h"


static sf::Texture objectTileset;

constexpr int spriteIndex_X = 2;
constexpr int spriteIndex_Y = 1;

//void ObjectTile::Initialize() {
//    if (!objectTileset.loadFromFile("Assets/Images/Objects.png")) {
//        throw std::invalid_argument("Cannot locate Assets/Image/Objects.png");
//    }
//}
//
//EngineTile::EngineTile(int xPos, int yPos, int spriteIndex) {
//    // Load texture
//    sprite.setTexture(objectTileset);
//    sf::IntRect spriteRect(spriteIndex % 2 * 100 + spriteIndex_X * 100, spriteIndex / 2 * 100 + spriteIndex_Y * 100, 100, 100);
//    sprite.setTextureRect(spriteRect);
//    sprite.setPosition((float)(xPos * 100 + spriteIndex % 2 * 100), (float)(yPos * 100 + spriteIndex / 2 * 100));
//}
