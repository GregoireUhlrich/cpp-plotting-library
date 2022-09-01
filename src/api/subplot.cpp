#include "subplot.hpp"
#include "ticks.hpp"
#include <algorithm>
#include <iomanip>
#include <sstream>

namespace cpt {

Subplot::Subplot()
{
}

void Subplot::plot_line(ScienceDataArray<float> x,
                        ScienceDataArray<float> y,
                        LinePlotConfig const   &config)
{
    _plots.push_back(
        std::make_shared<LinePlot>(std::move(x), std::move(y), config));
}

void Subplot::histogram(ScienceDataArray<float> x,
                        ScienceDataArray<float> y,
                        HistogramConfig const  &config)
{
    _plots.push_back(
        std::make_shared<Histogram>(std::move(x), std::move(y), config));
}

Extent<float> Subplot::get_extent()
{
    if (_user_extent) {
        return _extent;
    }
    compute_extent();
    return _extent;
}

void Subplot::set_extent(Extent<float> extent) noexcept
{
    _extent      = std::move(extent);
    _user_extent = true;
}

template <std::floating_point T>
static void ensure_non_zero_extent(T &min, T &max) noexcept
{
    if (max - min < std::numeric_limits<T>::min()) {
        min -= static_cast<T>(1.);
        max += static_cast<T>(1.);
    }
}

void Subplot::compute_extent()
{
    if (_plots.empty()) {
        _extent = {-1.f, 1.f, -1.f, 1.f};
        return;
    }
    auto iter = _plots.begin();
    _extent   = (**iter).get_extent();
    while (++iter != _plots.end()) {
        _extent = combine(_extent, (**iter).get_extent());
    }
    ensure_non_zero_extent(_extent.xmin, _extent.xmax);
    ensure_non_zero_extent(_extent.ymin, _extent.ymax);
    auto dx = _extent.xmax - _extent.xmin;
    auto dy = _extent.ymax - _extent.ymin;
    _extent.xmin -= 0.1f * dx;
    _extent.xmax += 0.1f * dx;
    _extent.ymin -= 0.1f * dy;
    _extent.ymax += 0.1f * dy;
}

static std::vector<cpt::Label> create_labels(std::vector<float> const &ticks,
                                             sf::Font const           &font,
                                             unsigned int font_size)
{
    if (ticks.empty()) {
        return {};
    }
    std::vector<cpt::Label> ticks_labels(ticks.size());
    int                     n_digits = 0;
    if (ticks.size() > 1) {
        auto log = -std::log10(std::abs(ticks[1] - ticks[0]));
        n_digits = static_cast<int>(std::max(0.f, 1.f + std::ceil(log)));
    }
    else {
        n_digits = static_cast<int>(
            std::max(0.f, -std::floor(std::log10(ticks[0]))));
    }
    for (size_t i = 0; i != ticks.size(); ++i) {
        std::ostringstream sout;
        sout.precision(n_digits);
        sout << std::fixed << ticks[i];
        ticks_labels[i].set_text(sout.str());
        ticks_labels[i].set_font(font);
        ticks_labels[i].set_font_size(font_size);
        ticks_labels[i].set_fill_color(sf::Color::Black);
    }
    return ticks_labels;
}

static void set_relative_position(std::vector<float> &x,
                                  float               xmin,
                                  float               xmax,
                                  bool                reverse)
{
    for (float &xi : x) {
        xi = (xi - xmin) / (xmax - xmin);
        if (reverse) {
            xi = 1.f - xi;
        }
    }
}

void Subplot::setup_default_axis(cpt::Extent<float> const &extent)
{
    std::vector<float> x_ticks = calculate_ticks(extent.xmin, extent.xmax);
    std::vector<float> y_ticks = calculate_ticks(extent.ymin, extent.ymax);
    std::vector<cpt::Label> x_ticks_labels
        = create_labels(x_ticks, get_font(), 15);
    std::vector<cpt::Label> y_ticks_labels
        = create_labels(y_ticks, get_font(), 15);
    set_relative_position(x_ticks, extent.xmin, extent.xmax, false);
    set_relative_position(y_ticks, extent.ymin, extent.ymax, true);
    set_ticks(Anchor::Bottom, std::move(x_ticks), std::move(x_ticks_labels));
    set_ticks(Anchor::Left, std::move(y_ticks), std::move(y_ticks_labels));
}

void Subplot::display()
{
    cpt::Extent<float> extent = get_extent();
    setup_default_axis(extent);

    SubplotTexture::update();
    _canvas.set_extent(extent);
    for (const auto &plot : _plots) {
        plot->draw_plot(_canvas);
    }
    SubplotTexture::display();
}

} // namespace cpt
