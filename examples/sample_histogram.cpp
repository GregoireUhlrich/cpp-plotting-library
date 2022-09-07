#include "api/figure.hpp"
#include "api/session.hpp"
#include <iostream>

int main()
{
    cpt::Session session;
    cpt::Figure &fig = session.create_figure("My Fig", 10, 5);

    fig.create_subplots(1, 2);

    auto x = cpt::linspace(0, 10, 20);

    cpt::Array<float> d{0,   0,   1.1, 1,   1.2, 2, 2.4, 2.5, 2, 3, 3.1,
                        3.8, 3.7, 4,   4.2, 4.5, 5, 5,   6,   7, 8, 9};
    cpt::ScienceDataArray<float> data;
    data.data = d;

    ////////////////////////////////////////////////////
    cpt::HistogramConfig config_plot{.marker_size  = 4.f,
                                     .marker_color = sf::Color::Red};

    cpt::Subplot &top_left = fig.get_subplot(0, 0);
    top_left.histogram(
        x, 5 * cpt::exp(1 - (x - 5) * (x - 5)) + 1, config_plot);

    ////////////////////////////////////////////////////
    cpt::HistogramConfig config{.min          = 0,
                                .max          = 10,
                                .n_bins       = 5,
                                .marker_size  = 4.f,
                                .marker_color = sf::Color::Red};

    cpt::Subplot &top_right = fig.get_subplot(0, 1);
    top_right.histogram(data, config);

    fig.show();

    return 0;
}
