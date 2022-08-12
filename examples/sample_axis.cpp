#include "plotter/axis.hpp"
#include "plotter/ticks.hpp"
#include "math_views.hpp"

void test_ticks(float xmin, float xmax)
{
    auto res = cpt::calculate_ticks(xmin, xmax);
    std::cout << res.size() << " ticks for [" << xmin << ", " << xmax << "] : \t";
    cpt::print(res);
}
int main() {

    test_ticks(-3.5f, 0.0f);
    test_ticks(-1.f, 1.f);
    test_ticks(0.f, 20.f);
    test_ticks(1.5f, 5.7f);
    test_ticks(1e-2f, 3e2f);
    std::cout.precision(8);
    test_ticks(1e3f, 1e3f + 1e-2f);
    return 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!", sf::Style::Close | sf::Style::Resize, settings);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.display();
    }

    return 0;
}