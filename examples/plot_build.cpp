#include <SFML/Graphics.hpp>

#include "graphics/pad.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "i3Float");

    graphics::Pad pad;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        pad.draw(window);
        window.display();
    }

    return 0;
}
