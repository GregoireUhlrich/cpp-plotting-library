#include "graphics/axis_renderer.hpp"
#include "graphics/label.hpp"
#include "graphics/font_manager.hpp"
#include "api/ticks.hpp"
#include "math_views.hpp"


void test_ticks(float xmin, float xmax)
{
    auto res = cpt::calculate_ticks(xmin, xmax);
    std::cout << res.size() << " ticks for [" << xmin << ", " << xmax << "] : \t";
    cpt::print(res);
}

auto axis_label(std::string str, cpt::FontManager &manager)
{
    cpt::Label label;
    label.set_text(std::move(str));
    label.set_font(manager.get_font(cpt::font::arial, cpt::font::Italic));
    label.set_font_size(15);
    label.set_fill_color(sf::Color::Red);
    return label;
}

int main() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    cpt::FontManager manager;
    sf::RenderWindow window(sf::VideoMode(300, 300), "i3float", sf::Style::Close | sf::Style::Resize, settings);
    cpt::AxisRenderer y (cpt::Anchor::Left,  200.f);
    cpt::AxisRenderer x (cpt::Anchor::Bottom,  200.f);
    cpt::AxisRenderer yc(
            cpt::Anchor::Right, 
            200.f, 
            {.tick_width=1.f, 
            .tick_length=10.f});
    cpt::AxisRenderer xc(cpt::Anchor::Top,    200.f);
    y.set_position (50.f,  50.f);
    x.set_position (50.f,  250.f);
    yc.set_position(250.f, 50.f);
    xc.set_position(50.f,  50.f);

    y.set_ticks({0.25f, 0.5f, 0.75f}, 
            {
            axis_label("0.25", manager), 
            axis_label("0.5", manager), 
            axis_label("0.75", manager)
            });
    x.set_ticks(
            {0.25f, 0.5f, 0.75f}, 
            {
            axis_label("0.25", manager), 
            axis_label("0.5", manager), 
            axis_label("0.75", manager)
            });
    xc.set_ticks({0.33f, 0.66f}, 
            {
            axis_label("0.33", manager),
            axis_label("0.66", manager)
            });
    yc.set_ticks({0.1f, 0.9f}, {
            axis_label("0.1", manager),
            axis_label("0.9", manager)
            });
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
