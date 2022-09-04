#include "histogram.hpp"
#include "../graphics/plot_canvas.hpp"
#include <algorithm>

namespace cpt {

Histogram::Histogram(ScienceDataArray<float> x, HistogramConfig const &config_)
    : _x(std::move(x)), config(config_)
{
    auto min_value = std::ranges::min_element(_x.data.begin(), _x.data.end());
    auto max_value = std::ranges::max_element(_x.data.begin(), _x.data.end());

    float width = (*max_value - *min_value) / float(config.n_bins);
    if (width == 0) {
        exit(0);
    }
    auto xx = cpt::linspace(*min_value, *max_value, config.n_bins);
    _x      = ScienceDataArray<float>(std::move(xx));

    cpt::Array<float> yy(config.n_bins);
    for (size_t i = 0; i != _x.size(); ++i) {
        if (not(_x.data[i] < *max_value)) {
            if (--yy[_x.data[i] / width] != 0)
                --yy[_x.data[i] / width];
        }
        else {
            ++yy[_x.data[i] / width];
        }
    }

    _y = ScienceDataArray<float>(std::move(cpt::linspace(0, 10, _x.size())));
    _y.data = yy;

    check_bounds();
    compute_extent();
}

Histogram::Histogram(ScienceDataArray<float> x,
                     ScienceDataArray<float> y,
                     HistogramConfig const  &config_)
    : _x(std::move(x)), _y(std::move(y)), config(config_)
{
    check_bounds();
    compute_extent();
}

void Histogram::create_y_data(const cpt::ScienceDataArray<float> &y)
{
    cpt::Array<float> binned_data;
    _y = ScienceDataArray<float>(std::move(y));
}

cpt::Array<float> const &Histogram::xerr(bool lower) const
{
    if (!_x.err_plus) {
        throw InvalidHistogramData("No error for x has been defined.");
    }
    return (lower ? _x.err_minus : _x.err_plus).value();
}

cpt::Array<float> const &Histogram::yerr(bool lower) const
{
    if (!_y.err_plus) {
        throw InvalidHistogramData("No error for y has been defined.");
    }
    return (lower ? _y.err_minus : _y.err_plus).value();
}

cpt::Extent<float> Histogram::get_extent() const
{
    return _extent;
}

void Histogram::check_bounds() const
{
    if (_x.data.size() != _y.data.size()) {
        throw InvalidHistogramData("A line plot data must have the ",
                                   "same dimension for x and y, ",
                                   _x.data.size(),
                                   " and ",
                                   _y.data.size(),
                                   " found.");
    }
    if (_x.err_plus.has_value() && _x.size() != _x.err_plus.value().size()) {
        throw InvalidHistogramData("A line plot data must have the ",
                                   "same dimension for x and xerr, ",
                                   _x.size(),
                                   " and ",
                                   _x.err_plus.value().size(),
                                   " found.");
    }
    if (_x.err_minus.has_value() && _x.size() != _x.err_minus.value().size()) {
        throw InvalidHistogramData("A line plot data must have the ",
                                   "same dimension for x and xerr, ",
                                   _x.size(),
                                   " and ",
                                   _x.err_minus.value().size(),
                                   " found.");
    }
    if (_y.err_plus.has_value() && _y.size() != _y.err_plus.value().size()) {
        throw InvalidHistogramData("A line plot data must have the ",
                                   "same dimension for y and yerr, ",
                                   _y.size(),
                                   " and ",
                                   _y.err_plus.value().size(),
                                   " found.");
    }
    if (_y.err_minus.has_value() && _y.size() != _y.err_minus.value().size()) {
        throw InvalidHistogramData("A line plot data must have the ",
                                   "same dimension for y and yerr, ",
                                   _y.size(),
                                   " and ",
                                   _y.err_minus.value().size(),
                                   " found.");
    }
}

void Histogram::compute_extent() noexcept
{
    auto x_extent = cpt::compute_extent(_x.data);
    auto y_extent = cpt::compute_extent(_y.data);
    _extent       = {.xmin = x_extent.min,
                     .xmax = x_extent.max,
                     .ymin = y_extent.min,
                     .ymax = y_extent.max};
}

void Histogram::draw_plot(cpt::PlotCanvas &canvas) const
{
    canvas.plot(*this);
}
} // namespace cpt