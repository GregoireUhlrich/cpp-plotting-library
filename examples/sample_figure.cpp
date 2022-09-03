#include "api/figure.hpp"
#include "api/session.hpp"
#include <iostream>

int main()
{
    cpt::Session session;
    cpt::Figure &fig = session.create_figure("First plots :)", 10, 5);

    fig.create_subplots(2, 2);

    auto x = cpt::linspace(0, 10, 100);

    cpt::Subplot &top_left = fig.get_subplot(0, 0);
    top_left.plot_line(x, cpt::cos(x));
    top_left.plot_line(x, 5*cpt::exp(-(x-5)*(x-5)), 
                      {
                        .marker_size = 4.f,
                        .marker_color = sf::Color::Red
                      });

    cpt::Subplot &top_right = fig.get_subplot(0, 1);
    top_right.plot_line(x, cpt::sin(x)*cpt::sin(x),
                       {.marker_size = 1.f, 
                        .marker_color = sf::Color::Red});
    top_right.set_extent({
        .xmin = -10.f, .xmax = 20.f,
        .ymin = -5.f,  .ymax = 5.f
    });

    cpt::Subplot &bottom_left = fig.get_subplot(1, 0);
    bottom_left.plot_line(x, cpt::atan(x),
                          {.marker_color = sf::Color::Blue});

    cpt::Subplot &bottom_right = fig.get_subplot(1, 1);
    bottom_right.plot_line(x, cpt::exp(x));

    fig.show();

    return 0;
}
