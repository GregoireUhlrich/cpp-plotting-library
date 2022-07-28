#include <SFML/Graphics.hpp>

#include "graphics/circle.hpp"
#include "graphics/esthetic.hpp"
#include "graphics/pad.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(graphic::GLOBAL_WIDTH, graphic::GLOBAL_HEIGHT),
        "i3Float");

    graphic::Circle circle;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        circle.draw(window);
        window.display();
    }

    return 0;
}
