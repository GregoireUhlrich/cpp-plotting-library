#include "histogram.hpp"
#include "../graphics/plot_canvas.hpp"
#include <algorithm>

namespace cpt {

Histogram::Histogram(ScienceDataArray<float> data,
                     HistogramConfig const  &config_,
                     HistogramDesign const  &design_)
    : config(config_), design(design_)
{
    if (data.size() == 0) {
        _x = cpt::constant(1, 0.f);
        _y = _x;
        return;
    }

    auto minmax
        = std::ranges::minmax_element(data.data.begin(), data.data.end());

    float mini = *(minmax.min);
    float maxi = *(minmax.max);
    if (config.min.has_value()) {
        mini = config.min.value();
    }
    if (config.max.has_value()) {
        maxi = config.max.value();
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
                     HistogramConfig const  &config_,
                     HistogramDesign const  &design_)
    : _x(std::move(x)), _y(std::move(y)), config(config_), design(design_)
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
                                   "same dimension for y and yerr plus, ",
                                   _y.size(),
                                   " and ",
                                   _y.err_plus.value().size(),
                                   " found.");
    }
    if (_y.err_minus.has_value() && _y.size() != _y.err_minus.value().size()) {
        throw InvalidHistogramData("A line plot data must have the ",
                                   "same dimension for y and yerr minus, ",
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
    unsigned int data_size = data.size();

    cpt::Array<float> count(config.n_bins);
    for (float di : data.data) {
        size_t index = static_cast<size_t>(di / width);
        if (index && !(di < maxi)) { // extrem right of the histogram
            --index;
        }
        ++count[index];
    }

    cpt::Array<float> error_up(config.n_bins);
    cpt::Array<float> error_down(config.n_bins);

    for (size_t i = 0; i != error_up.size(); ++i) {
        error_up[i] = std::sqrt(count[i] * (1 - count[i] / float(data_size)));
        error_down[i] = -error_up[i];
    }
    //_y = cpt::view_cast<float>(count);
    _y = ScienceDataArray<float>(cpt::view_cast<float>(count),
                                 cpt::view_cast<float>(error_up),
                                 cpt::view_cast<float>(error_down));
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
