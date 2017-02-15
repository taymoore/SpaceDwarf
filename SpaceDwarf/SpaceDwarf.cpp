#include "stdafx.h"
#include "Tile.h"
#include "ShipTile.h"
#include "Ship.h"

#include <SFML/Graphics.hpp>

void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom) {
    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(pixel) };
    sf::View view{ window.getView() };
    view.zoom(zoom);
    window.setView(view);
    const sf::Vector2f afterCoord{ window.mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    view.move(offsetCoords);
    window.setView(view);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
    // Create window
	sf::VideoMode currentVideoMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(currentVideoMode, "SFML works!", sf::Style::Fullscreen);

    // Set initial zoom 
    const float initialZoom = 4;
    sf::View view(window.getView());
    view.zoom(initialZoom);
    window.setView(view);

    // Load assets
    //Floor::Initialize();
    //Wall::Initialize();
    ShipTile::Initialize();

    // Build starter ship
    Ship playerShip = Ship(&window);

    // Transformation
    //sf::Transform mapTransform = sf::Transform();

    // UI variables
    bool isPanning = false;
    sf::Vector2i oldMousePoint;
    static float viewZoom = initialZoom;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
            if(event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            // Mouse button pressed
            if(event.type == sf::Event::MouseButtonPressed) {
                // Middle mouse button pressed
                if(event.mouseButton.button == sf::Mouse::Button::Middle) {
                    isPanning = true;
                    oldMousePoint = sf::Mouse::getPosition();
                }
            // Mouse button released
            } else if(event.type == sf::Event::MouseButtonReleased) {
                // Middle mouse button released
                if(event.mouseButton.button == sf::Mouse::Button::Middle) {
                    isPanning = false;
                }
            }
            // Move mouse
            if(event.type == sf::Event::MouseMoved) {
                // Pan camera
                if(isPanning == true) {
                    sf::View view(window.getView());
                    view.move((oldMousePoint.x - event.mouseMove.x) * viewZoom, (oldMousePoint.y - event.mouseMove.y) * viewZoom);
                    window.setView(view);
                    //oldMousePoint = window.mapPixelToCoords(sf::Mouse::getPosition());
                    oldMousePoint = sf::Mouse::getPosition();
                }
            }
            // Mouse wheel moved
            if(event.type == sf::Event::MouseWheelScrolled) {
                // Zoom)
                if(event.mouseWheelScroll.delta > 0) {
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / 1.2f));
                    viewZoom *= (1.f / 1.2f);
                } else if(event.mouseWheelScroll.delta < 0) {
                    zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, 1.2f);
                    viewZoom *= 1.2f;
                }
            }
		}

        // Render
		window.clear();
        //for(int i = 0; i < tileCount; i++) {
        //    tileList[i]->Draw(&window);
        //}
        playerShip.Draw(&window);
		window.display();
	}


	return 0;
}

