#include "stdafx.h"
#include "ShipTile.h"

static sf::Texture shipTileset;
constexpr int shipTilesetSpriteWidth = 2;

void ShipTile::Initialize() {
    if (!shipTileset.loadFromFile("Assets/Images/Ship.png")) {
        throw std::invalid_argument("Cannot locate Assets/Image/Ship.png");
    }
}

Floor::Floor(int xPos, int yPos) {
    // Load texture
    sprite.setTexture(shipTileset);
    sf::IntRect spriteRect(0 * 388, 0 % shipTilesetSpriteWidth * 335, 388, 335);
    sprite.setTextureRect(spriteRect);
    sprite.setPosition((float)((xPos + yPos) * 195), (float)((xPos - yPos) * 112 - 111));
}

Wall::Wall(int xPos, int yPos) {
    // Load texture
    sprite.setTexture(shipTileset);
    sf::IntRect spriteRect(1 * 388, 1 / shipTilesetSpriteWidth * 335, 388, 335);
    sprite.setTextureRect(spriteRect);
    sprite.setPosition((float)((xPos + yPos) * 195), (float)((xPos - yPos) * 112 - 111));
}