#include "histogram.hpp"
#include "../graphics/plot_canvas.hpp"
#include <algorithm>

namespace cpt {

Histogram::Histogram(ScienceDataArray<float> data,
                     HistogramConfig const  &config_)
    : config(config_)
{
    if (data.size() == 0) {
        _x = cpt::constant(1, 0.f);
        _y = _x;
        return;
    }

    auto minmax
        = std::ranges::minmax_element(data.data.begin(), data.data.end());
    float mini = config.min.value();
    float maxi = config.max.value();
    if (!config.min.has_value()) {
        mini = *(minmax.min);
    }
    if (!config.max.has_value()) {
        maxi = *(minmax.max);
    }

    float width = (maxi - mini) / static_cast<float>(config.n_bins);
    if (!(width > 0)) {
        width = 1.f;
    }

    _x = width / 2.f
         + cpt::linspace(mini, maxi, config.n_bins, {.end_point = false}
                         // last bin position is not equal to maxi
         );

    compute_data(data, width, maxi);
    check_bounds();
    compute_extent();
    for (int i = 0; i != config.n_bins; ++i) {
        std::cout << get_error(i)[0] << " : " << get_error(i)[1] << std::endl;
    }
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

void Histogram::compute_data(const ScienceDataArray<float> &data,
                             float                          width,
                             float                          maxi)
{
    cpt::Array<float> count(config.n_bins);
    for (float di : data.data) {
        size_t index = static_cast<size_t>(di / width);
        if (index && !(di < maxi)) { // extrem right of the histogram
            --index;
        }
        ++count[index];
    }
    cpt::Array<float> error_up(_y.size());
    cpt::Array<float> error_down(_y.size());
    for (size_t i = 0; i != error_up.size(); ++i) {
        error_up[i]
            = std::sqrt(_y.data[i] * (1 - float(_y.data[i]) / float()));
        error_down[i] = -error_up[i];
    }
    //_y = cpt::view_cast<float>(count);
    _y = ScienceDataArray(cpt::view_cast<float>(count), error_up, error_down);
}

cpt::Array<float> Histogram::get_error(unsigned int bin)
{
    return {_y.err_plus.value()[bin], _y.err_minus.value()[bin]};
}

void Histogram::draw_plot(cpt::PlotCanvas &canvas) const
{
    canvas.plot(*this);
}
} // namespace cpt
