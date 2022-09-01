#include "api/figure.hpp"
#include "api/session.hpp"
#include <iostream>

int main()
{
    cpt::Session session;
    cpt::Figure &fig = session.create_figure("My Fig", 10, 5);

    fig.create_subplots(1, 1);

    auto x = cpt::linspace(0, 10, 20);

    cpt::Subplot &top_left = fig.get_subplot(0, 0);
    top_left.histogram(x,
                       5 * cpt::exp(-(x - 5) * (x - 5)),
                       {.marker_size = 4.f, .marker_color = sf::Color::Red});

    fig.show();

    return 0;
}
