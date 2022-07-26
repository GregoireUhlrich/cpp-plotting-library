#include "histogram.hpp"
#include "../graphics/plot_canvas.hpp"

namespace cpt {

Histogram::Histogram(ScienceDataArray<float> x,
                     ScienceDataArray<float> y,
                     HistogramConfig const  &config_)
    : _x(std::move(x)), _y(std::move(y)), config(config_)
{
    check_bounds();
    compute_extent();
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