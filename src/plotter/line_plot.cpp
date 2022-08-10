#include "line_plot.hpp"

namespace cpt {

    LinePlot::LinePlot(
        ScienceDataArray<float> x,
        ScienceDataArray<float> y,
        LinePlotConfig const &config_)
        : _x(std::move(x)),
            _y(std::move(y)),
            config(config_)
    {
        check_bounds();
        compute_extent();
    }

    cpt::Array<float> const &LinePlot::xerr(bool lower) const {
        if (!_x.err_plus) {
            throw InvalidLinePlotData("No error for x has been defined.");
        }
        return (lower ? _x.err_minus : _x.err_plus).value();
    }

    cpt::Array<float> const &LinePlot::yerr(bool lower) const {
        if (!_y.err_plus) {
            throw InvalidLinePlotData("No error for y has been defined.");
        }
        return (lower ? _y.err_minus : _y.err_plus).value();
    }

    cpt::Extent<float> LinePlot::extent() const noexcept {
        return _extent;
    }

    void LinePlot::check_bounds() const 
    {
        if (_x.data.size() != _y.data.size()) {
            throw InvalidLinePlotData(
                "A line plot data must have the ",
                "same dimension for x and y, ",
                _x.data.size(), " and ", _y.data.size(), " found.");
        }
        if (_x.err_plus.has_value() && _x.size() != _x.err_plus.value().size()) {
            throw InvalidLinePlotData(
                "A line plot data must have the ",
                "same dimension for x and xerr, ",
                _x.size(), " and ", _x.err_plus.value().size(), " found.");
        }
        if (_x.err_minus.has_value() && _x.size() != _x.err_minus.value().size()) {
            throw InvalidLinePlotData(
                "A line plot data must have the ",
                "same dimension for x and xerr, ",
                _x.size(), " and ", _x.err_minus.value().size(), " found.");
        }
        if (_y.err_plus.has_value() && _y.size() != _y.err_plus.value().size()) {
            throw InvalidLinePlotData(
                "A line plot data must have the ",
                "same dimension for y and yerr, ",
                _y.size(), " and ", _y.err_plus.value().size(), " found.");
        }
        if (_y.err_minus.has_value() && _y.size() != _y.err_minus.value().size()) {
            throw InvalidLinePlotData(
                "A line plot data must have the ",
                "same dimension for y and yerr, ",
                _y.size(), " and ", _y.err_minus.value().size(), " found.");
        }
    }

    auto compute_extent(cpt::Array<float> const &arr) noexcept 
    {
        struct MinMax { float min, max; };
        MinMax res {
            .min = std::numeric_limits<float>::max(),
            .max = std::numeric_limits<float>::lowest()
        };
        for (float val : arr) {
            if (val < res.min) res.min = val;
            if (val > res.max) res.max = val;
        }
        return res;
    }

    void LinePlot::compute_extent() noexcept 
    {
        auto x_extent = cpt::compute_extent(_x.data);
        auto y_extent = cpt::compute_extent(_y.data);
        _extent = {
            .xmin = x_extent.min,
            .xmax = x_extent.max,
            .ymin = y_extent.min,
            .ymax = y_extent.max
        };
    }
} // namespace cpt