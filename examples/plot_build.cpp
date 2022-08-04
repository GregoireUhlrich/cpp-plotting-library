#include <SFML/Graphics.hpp>

#include "graphics/esthetic.hpp"
#include "graphics/pad.hpp"
#include "graphics/subplot.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(cpt::GLOBAL_WIDTH, cpt::GLOBAL_HEIGHT), "i3Float");

    cpt::SubPlot subplot;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(subplot);
        window.display();
    }

    return 0;
}
