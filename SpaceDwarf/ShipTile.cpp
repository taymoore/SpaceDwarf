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

Window::Window(int xPos, int yPos, ShipTile::Orientation orientation) {
    // Load texture
    sprite.setTexture(shipTileset);
    SetOrientation(orientation);
    sprite.setPosition((float)((xPos + yPos) * 195), (float)((xPos - yPos) * 112 - 111));
}

void Window::SetOrientation(ShipTile::Orientation orientation) {
    int spriteIndexX = 0;
    int spriteIndexY = 1;
    switch(orientation) {
        case ShipTile::Orientation::NE:
            spriteIndexX = 0;
            break;
        case ShipTile::Orientation::SE:
            spriteIndexX = 3;
            break;
        case ShipTile::Orientation::SW:
            spriteIndexX = 2;
            break;
        case ShipTile::Orientation::NW:
            spriteIndexX = 1;
            break;
    }
    sf::IntRect spriteRect(spriteIndexX * 388, spriteIndexY * 335, 388, 335);
    sprite.setTextureRect(spriteRect);
}
