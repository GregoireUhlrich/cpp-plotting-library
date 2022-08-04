#include <SFML/Graphics.hpp>
#include <cmath>

#include "graphics/subplot.hpp"
#include "graphics/esthetic.hpp"
#include "graphics/pad.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(cpt::GLOBAL_WIDTH, cpt::GLOBAL_HEIGHT),
        "i3Float");

    std::vector<double> x(15);
    std::vector<double> y(x.size());
    for (std::size_t i = 0; i != x.size(); ++i) {
        x[i] = 50.*(static_cast<double>(i)+2.);
        y[i] = std::cos(x[i]/50.)*100. + 250.;
    }

    cpt::SubPlot subplot;
    try {
        subplot.plot(cpt::LineData<double, double>(
            std::span<double>(x.begin(), x.end()), 
            std::span<double>(y.begin(), y.end())));
    } catch (cpt::Exception const &err) {
        std::cerr << err.what() << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        subplot.draw(window);
        window.display();
    }

    return 0;
}
