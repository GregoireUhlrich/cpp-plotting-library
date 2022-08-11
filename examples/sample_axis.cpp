#include "plotter/axis.hpp"

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!", sf::Style::Close | sf::Style::Resize, settings);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    cpt::Axis right(cpt::Axis::Right, 50.f, {.line_width = 1.f});
    cpt::Axis left(cpt::Axis::Left,   50.f, {.color = sf::Color::Blue});
    cpt::Axis up(cpt::Axis::Up,   50.f, {.color = sf::Color::Red});
    cpt::Axis down(cpt::Axis::Down,   50.f, {.arrow_width = 25.f});

    right.set_position(150.f, 150.f);
    left.set_position(150.f, 150.f);
    up.set_position(150.f, 150.f);
    down.set_position(150.f, 150.f);

    sf::RectangleShape hwitness(sf::Vector2f{100.f, 1.f});
    hwitness.setPosition(100.f, 157.f);
    hwitness.setFillColor(sf::Color::Red);
    sf::RectangleShape vwitness(sf::Vector2f{1.f, 100.f});
    vwitness.setPosition(157.f, 100.f);
    vwitness.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        left.draw(window);
        right.draw(window);
        up.draw(window);
        down.draw(window);
        window.draw(hwitness);
        window.draw(vwitness);
        window.display();
    }

    return 0;
}