#include "stdafx.h"

#include "Tile.h"
#include "ShipTile.h"
#include "ObjectTile.h"
#include "Arena.h"

#include "Ship.h"
//#include "ShipObject.h"

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

int currentFps = 0;
int lastFps = 0;
std::chrono::nanoseconds fpsCount_ns(0);

sf::Vector2f screenSize;

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
    sf::RenderWindow window(currentVideoMode, "Space Dwarf" , sf::Style::Fullscreen);

    // Set initial zoom 
    const float initialZoom = 3;
    sf::View view(window.getView());
    view.zoom(initialZoom);
    window.setView(view);

    // Get window size
    screenSize = view.getSize();
    //screenPosition = window.getPosition();

    // Load assets
    ShipTile::Initialize();
    //ObjectTile::Initialize();

    // Load arena
    Arena arena(&window);

    // Transformation
    //sf::Transform mapTransform = sf::Transform();

    // UI variables
    bool isPanning = false;
    sf::Vector2i oldMousePoint;
    static float viewZoom = initialZoom;

    using clock = std::chrono::high_resolution_clock;
    std::chrono::nanoseconds lag(0);
    auto timeStart = clock::now();

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

        // Update time
        auto deltaTime = clock::now() - timeStart;
        timeStart = clock::now();
        lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

        // Update physics
        constexpr std::chrono::nanoseconds timeStep_ns(1000000000 / 60);
        while(lag >= timeStep_ns) {
            lag -= timeStep_ns;
            currentFps++;

            arena.Update();
        }

        // FPS counter
        constexpr std::chrono::nanoseconds oneSecond_ns(1000000000);
        fpsCount_ns += deltaTime;
        if(fpsCount_ns >= oneSecond_ns) {
            lastFps = currentFps;
            currentFps = 0;
            fpsCount_ns -= oneSecond_ns;

            std::wostringstream os_;
            os_ << lastFps;
            OutputDebugString(os_.str().c_str());
        }

        // Render
        arena.Draw();
	}


	return 0;
}

