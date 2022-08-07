#ifndef LINE_PLOT_DATA_H_INCLUDED
#define LINE_PLOT_DATA_H_INCLUDED

#include "../utils/error.hpp"
#include "../math_views.hpp"
#include "extent.hpp"
#include "plot_data.hpp"

#include <concepts>
#include <numeric>
#include <optional>

namespace cpt
{
    class InvalidLinePlotData: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    struct LinePlotDataConfig {
        float     marker_size = 3.5f;
        sf::Color marker_color = sf::Color(0, 64, 128);
    };

    template<std::floating_point T>
    class LinePlotData {
    public:

        LinePlotData(
            PlotData<T> x,
            PlotData<T> y,
            LinePlotDataConfig const &config_ = {})
            : _x(std::move(x)),
              _y(std::move(y)),
              config(config_)
        {
            check_bounds();
            compute_extent();
        }

        // Delete copy constructor to enable only move of the underlying data
        LinePlotData(LinePlotData const &) = delete;

        LinePlotData(LinePlotData &&)            noexcept = default;
        LinePlotData &operator=(LinePlotData &&) noexcept = default;

        bool has_xerr() const noexcept { return _x.err_plus.has_value(); }
        bool has_yerr() const noexcept { return _y.err_plus.has_value(); }

        auto const &x() const noexcept { return _x.data; }
        auto const &y() const noexcept { return _y.data; }

        auto const &xerr(bool lower = false) const {
            if (!_x.err_plus) {
                throw InvalidLinePlotData("No error for x has been defined.");
            }
            return lower ? _x.err_minus : _x.err_plus;
        }
        auto const &yerr(bool lower = false) const {
            if (!_y.err_plus) {
                throw InvalidLinePlotData("No error for y has been defined.");
            }
            return lower ? _y.err_minus : _y.err_plus;
        }

        auto const &extent() const noexcept {
            return _extent;
        }

    protected:

        void check_bounds() const 
        {
            if (_x.data.size() != _y.data.size()) {
                throw InvalidLinePlotData(
                    "A line plot data must have the ",
                    "same dimension for x and y, ",
                    _x.data.size(), " and ", _y.data.size(), " found.");
            }
            /*if (_xerr.has_value() && _x.size() != _xerr.value().size()) {
                throw InvalidLinePlotData(
                    "A line plot data must have the ",
                    "same dimension for x and xerr, ",
                    _x.size(), " and ", _xerr.value().size(), " found.");
            }
            if (_yerr.has_value() && _y.size() != _yerr.value().size()) {
                throw InvalidLinePlotData(
                    "A line plot data must have the ",
                    "same dimension for y and yerr, ",
                    _y.size(), " and ", _yerr.value().size(), " found.");
            }*/
        }

        static auto compute_extent(cpt::Array<T> const &arr) noexcept 
        {
            struct MinMax { T min, max; };
            MinMax res {
                .min = std::numeric_limits<T>::max(),
                .max = std::numeric_limits<T>::lowest()
            };
            for (T val : arr) {
                if (val < res.min) res.min = val;
                if (val > res.max) res.max = val;
            }
            return res;
        }

        void compute_extent() noexcept 
        {
            auto x_extent = compute_extent(_x.data);
            auto y_extent = compute_extent(_y.data);
            _extent = {
                .xmin = x_extent.min,
                .xmax = x_extent.max,
                .ymin = y_extent.min,
                .ymax = y_extent.max
            };
        }

    private:
        PlotData<T> _x;
        PlotData<T> _y;

        cpt::Extent<T> _extent;

    public:
        LinePlotDataConfig config;
    };
    
} // namespace cpt

#endif