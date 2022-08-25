#include "graphics/axis_renderer.hpp"
#include "graphics/label.hpp"
#include "api/ticks.hpp"
#include "math_views.hpp"

void test_ticks(float xmin, float xmax)
{
    auto res = cpt::calculate_ticks(xmin, xmax);
    std::cout << res.size() << " ticks for [" << xmin << ", " << xmax << "] : \t";
    cpt::print(res);
}
int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!", sf::Style::Close | sf::Style::Resize, settings);
    cpt::AxisRenderer y (cpt::Anchor::Left,  200.f);
    cpt::AxisRenderer x (cpt::Anchor::Down,  200.f);
    cpt::AxisRenderer yc(cpt::Anchor::Right, 200.f, {.tick_width=1.f, .tick_length=10.f});
    cpt::AxisRenderer xc(cpt::Anchor::Up,    200.f);
    y.set_position (50.f,  50.f);
    x.set_position (50.f,  250.f);
    yc.set_position(250.f, 50.f);
    xc.set_position(50.f,  50.f);
    y.set_ticks({0.25f, 0.75f}, {cpt::Label(), cpt::Label()});
    x.set_ticks({0.25f, 0.5f, 0.75f}, {cpt::Label(), cpt::Label(), cpt::Label()});
    xc.set_ticks({0.33f, 0.66f}, {cpt::Label(), cpt::Label()});
    yc.set_ticks({0.1f, 0.9f}, {cpt::Label(), cpt::Label()});
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        y.draw(window);
        x.draw(window);
        yc.draw(window);
        xc.draw(window);
        window.display();
    }

    return 0;
}
