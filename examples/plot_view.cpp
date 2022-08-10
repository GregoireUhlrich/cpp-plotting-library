#include <SFML/Graphics.hpp>

#include "math_views.hpp"
#include "plotter/line_plot_data.hpp"
#include "plotter/plot_canvas.hpp"

using namespace cpt;

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(800, 600), 
        "i3Float",
        sf::Style::Titlebar | sf::Style::Close
        );

    // Define the canvas size with respect to the window size
    float ratio = 0.9f;
    sf::Vector2f window_size = {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)};
    sf::Vector2u canvas_size = {
        static_cast<unsigned int>(ratio * window_size.x),
        static_cast<unsigned int>(ratio * window_size.y)
    };

    // Define plot type
    using line_plot = LinePlotData;

    // Create plot canvas and add three plots
    PlotCanvas canvas(canvas_size.x, canvas_size.y);
    auto x = linspace(0, 10, 100);
    
    const auto line_plots = {
        line_plot(x, cos(x), 
                  {.marker_size = 1.5f, .marker_color = sf::Color::Red}),
        line_plot(x, sin(x), 
                  {.marker_size = 5.f,  .marker_color = sf::Color::Green}),
        line_plot(x, 3*exp(-(x-5)*(x-5)))
    };
    canvas.plot(line_plots);

    // Draw final sprite on window
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
