#include "api/figure.hpp"
#include "api/session.hpp"
#include <iostream>

int main()
{
    cpt::Session session;
    cpt::Figure &fig = session.create_figure("My Fig", 15, 7);

    fig.create_subplots(1, 2);

    auto x = cpt::linspace(0, 10, 20);

    cpt::Array<float> d{
        10,  107, 107, 102, 110, 95,  112, 103, 93,  94,  107, 105, 107, 81,
        86,  88,  110, 93,  102, 117, 98,  88,  85,  94,  109, 111, 104, 115,
        96,  105, 102, 117, 85,  107, 89,  86,  101, 109, 109, 109, 84,  84,
        84,  93,  103, 118, 99,  100, 95,  110, 107, 109, 101, 85,  102, 106,
        120, 112, 87,  88,  99,  90,  110, 89,  106, 106, 93,  98,  100, 89,
        103, 76,  103, 93,  113, 113, 99,  100, 101, 97,  109, 88,  108, 99,
        87,  91,  95,  97,  92,  87,  93,  102, 102, 105, 112, 99,  104, 108,
        96,  90,  94,  80,  106, 94,  99,  100, 98,  100, 96,  110, 94,  106,
        106, 105, 106, 109, 101, 99,  101, 89,  105, 100, 85,  99,  104, 118,
        113, 98,  102, 113, 81,  80,  101, 101, 98,  83,  90,  114, 97,  110,
        111, 94,  108, 89,  94,  106, 99,  113, 102, 89,  90,  79,  99,  94,
        119, 111, 98,  112, 99,  118, 119, 88,  105, 106, 97,  104, 108, 97,
        96,  102, 101, 101, 89,  82,  98,  94,  106, 90,  95,  93,  85,  99,
        87,  111, 94,  98,  118, 101, 106, 103, 106, 100, 85,  106, 98,  112,
        111, 99,  99,  96,  94,  86,  103, 74,  100, 102, 106, 106, 82,  105,
        87,  108, 91,  91,  110, 106, 86,  85,  109, 100, 87,  92,  92,  82,
        114, 100, 87,  102, 90,  108, 90,  103, 94,  102, 92,  83,  102, 119,
        113, 100, 99,  96,  98,  97,  103, 92,  106, 91,  96,  89,  111, 107,
        96,  100, 109, 107, 96,  113, 97,  97,  92,  95,  109, 88,  99,  102,
        95,  113, 107, 99,  95,  103, 97,  104, 105, 98,  89,  116, 99,  102,
        99,  96,  99,  85,  99,  101, 115, 99,  101, 90,  117, 109, 88,  90,
        118, 83,  105, 95,  109, 108, 90,  101, 86,  99,  99,  111, 88,  102,
        96,  114, 105, 104, 92,  117, 78,  110, 98,  100, 114, 100, 96,  116,
        106, 95,  87,  98,  98,  99,  88,  102, 90,  86,  93,  95,  95,  98,
        84,  109, 98,  97,  101, 98,  92,  109, 82,  92,  91,  107, 90,  106,
        109, 102, 98,  107, 99,  86,  90,  89,  102, 104, 89,  86,  107, 116,
        93,  100, 95,  107, 102, 89,  101, 83,  110, 100, 103, 90,  109, 104,
        86,  114, 107, 119, 96,  92,  81,  109, 102, 95,  98,  99,  109, 85,
        90,  101, 93,  85,  103, 100, 104, 116, 81,  108, 116, 116, 92,  99,
        87,  90,  115, 82,  93,  100, 106, 94,  104, 86,  104, 108, 105, 93,
        88,  110, 84,  96,  111, 92,  95,  109, 109, 90,  107, 99,  96,  104,
        107, 92,  104, 98,  93,  91,  95,  106, 109, 92,  108, 78,  98,  118,
        119, 100, 107, 86,  99,  121, 103, 87,  109, 96,  103, 82,  89,  105,
        98,  99,  106, 104, 79,  102, 91,  92,  104, 116, 101, 98,  94,  114,
        99,  92,  87,  99,  92,  98,  102, 100, 99,  95,  114, 82,  104, 112,
        85,  86,  104, 92,  111, 87,  97,  91,  102, 92,  99,  94,  101, 90,
        92,  101, 108, 97,  92,  102, 98,  102, 79,  102, 97,  112, 103, 103,
        95,  100, 111, 100, 109, 99,  105, 94,  92,  101, 107, 86,  81,  90,
        114, 105, 86,  105, 97,  104, 113, 101, 88,  98,  97,  109, 112, 113,
        94,  120, 96,  105, 92,  97,  90,  87,  116, 100, 103, 95,  78,  115,
        85,  103, 102, 85,  113, 95,  88,  103, 111, 101, 83,  111, 111, 102,
        104, 107, 109, 87,  101, 93,  100, 97,  103, 86,  96,  94,  94,  102,
        94,  117, 106, 79,  103, 88,  98,  100, 104, 107, 93,  110, 101, 99,
        112, 111, 95,  104, 125, 109, 107, 90,  104, 105, 107, 93,  94,  121,
        101, 96,  96,  81,  117, 96,  93,  110, 100, 104, 105, 91,  97,  106,
        77,  107, 97,  91,  91,  132, 97,  97,  111, 83,  125, 97,  99,  120,
        81,  116, 109, 108, 90,  84,  100, 112, 125, 109, 102, 90,  112, 113,
        94,  99,  88,  114, 108, 104, 92,  105, 74,  87,  111, 100, 131, 98,
        100, 94,  90,  94,  102, 104, 111, 106, 103, 122, 118, 107, 100, 83,
        118, 81,  112, 97,  99,  89,  102, 98,  90,  109, 111, 126, 104, 113,
        98,  101, 90,  103, 98,  105, 123, 89,  97,  109, 95,  95,  93,  106,
        105, 112, 119, 102, 97,  102, 80,  117, 105, 88,  115, 98,  86,  108,
        107, 94,  98,  100, 110, 107, 100, 108, 91,  97,  99,  96,  101, 96,
        94,  110, 95,  106, 119, 113, 91,  99,  91,  96,  99,  98,  99,  98,
        81,  99,  112, 87,  99,  100, 87,  96,  92,  88,  100, 102, 103, 113,
        113, 106, 106, 103, 102, 94,  93,  101, 91,  96,  79,  105, 95,  107,
        90,  119, 102, 94,  94,  86,  89,  93,  107, 97,  91,  113, 96,  94,
        103, 107, 98,  86,  107, 101, 101, 107, 96,  91,  95,  107, 75,  89,
        99,  110, 89,  101, 82,  121, 114, 84,  87,  105, 105, 120, 111, 105,
        106, 114, 103, 102, 92,  111, 93,  119, 98,  82,  101, 102, 115, 116,
        94,  103, 87,  91,  102, 99,  97,  99,  93,  100, 95,  97,  84,  101,
        104, 103, 98,  100, 116, 95,  113, 111, 112, 87,  110, 86,  79,  97,
        77,  102, 100, 90,  97,  89,  94,  91,  100, 104, 116, 103, 111, 87,
        106, 88,  112, 118, 113, 96,  106, 107, 130, 93,  112, 117, 115, 87,
        108, 92,  100, 91,  114, 108, 99,  96,  105, 100, 103, 84,  114, 103,
        80,  99,  109, 112, 119, 83,  91,  98,  88,  88,  104, 94,  97,  113,
        106, 101, 113, 91,  106, 112, 107, 99,  100, 104, 100, 109, 108, 100,
        108, 98,  117, 110, 83,  101, 112, 107, 93,  103, 100, 100, 99,  93,
        89,  113, 115, 124, 104, 89,  87,  100, 89,  109, 105, 94,  82,  93,
        106, 114, 99,  99,  100, 98,  111, 102, 111, 107, 106, 90,  91,  102,
        88,  105, 106, 108, 113, 100, 81,  103, 125, 116, 103, 100, 96,  109,
        105, 83,  87,  88,  98,  107, 99,  98,  99,  97,  97};
    cpt::ScienceDataArray<float> data;
    data.data = d;

    ////////////////////////////////////////////////////
    cpt::HistogramConfig config_plot{.marker_size  = 4.f,
                                     .marker_color = sf::Color::Red};

    cpt::Subplot &top_left = fig.get_subplot(0, 0);
    top_left.histogram(
        x, 5 * cpt::exp(1 - (x - 5) * (x - 5)) + 1, config_plot);

    ////////////////////////////////////////////////////
    cpt::HistogramConfig config{
        .n_bins = 20, .marker_size = 4.f, .marker_color = sf::Color::Red};
    cpt::HistogramDesign design{.marker_color        = sf::Color(255, 0, 139),
                                .error_bar_color     = sf::Color(209, 0, 255),
                                .error_outline_color = sf::Color(209, 0, 255)};

    cpt::Subplot &top_right = fig.get_subplot(0, 1);
    top_right.histogram(data, config, design);

    fig.show();

    return 0;
}
