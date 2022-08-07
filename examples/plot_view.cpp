#include <SFML/Graphics.hpp>

#include "math_views.hpp"
#include "graphics/line_plot_data.hpp"
#include "graphics/plot_canvas.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(800, 600), 
        "i3Float",
        sf::Style::Titlebar | sf::Style::Close
        );

    float ratio = 0.9f;
    sf::Vector2f window_size = {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)};
    sf::Vector2u canvas_size = {
        static_cast<unsigned int>(ratio * window_size.x),
        static_cast<unsigned int>(ratio * window_size.y)
    };
    cpt::PlotCanvas canvas(canvas_size.x, canvas_size.y);

    auto x = cpt::linspace(0, 10, 100);
    auto y = cpt::exp(x);
    std::vector<cpt::LinePlotData<float>> line_plots;
    line_plots.reserve(3);
    line_plots.emplace_back(x, cpt::cos(x), cpt::LinePlotDataConfig{.marker_size=1.5f,  .marker_color=sf::Color::Red});
    line_plots.emplace_back(x, cpt::sin(x), cpt::LinePlotDataConfig{.marker_size=5.f, .marker_color=sf::Color::Green});
    line_plots.emplace_back(x, 3*cpt::exp(-cpt::pow(x-5, 2)));
    canvas.plot(line_plots);
    window.clear();

    sf::Sprite plot;
    plot.setTexture(canvas.get_texture());
    plot.setPosition(
        (1.f - ratio)*window_size.x/2.f,
        (1.f - ratio)*window_size.y/2.f);
    window.draw(plot);
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.waitEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    }

    return 0;
}
