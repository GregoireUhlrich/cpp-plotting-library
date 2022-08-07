#ifndef LINE_PLOT_DATA_H_INCLUDED
#define LINE_PLOT_DATA_H_INCLUDED

#include "../utils/error.hpp"
#include "../math_views.hpp"
#include "extent.hpp"

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

    template<std::floating_point T = float>
    class LinePlotData {
    public:

        LinePlotData(
            cpt::View auto const &x, 
            cpt::View auto const &y,
            cpt::View auto const &xerr,
            cpt::View auto const &yerr,
            LinePlotDataConfig const &config_ = {})
            : _x(cpt::collect<T>(x)),
              _y(cpt::collect<T>(y)),
              _xerr(cpt::collect<T>(xerr)),
              _yerr(cpt::collect<T>(yerr)),
              config(config_)
        {
            check_bounds();
            compute_extent();
        }

        LinePlotData(
            cpt::View auto const &x, 
            cpt::View auto const &y,
            LinePlotDataConfig const &config_ = {}
        )
            : _x(std::move(cpt::collect<T>(x))),
              _y(std::move(cpt::collect<T>(y))),
              _xerr(std::nullopt),
              _yerr(std::nullopt),
              config(config_)
        {
            check_bounds();
            compute_extent();
        }

        LinePlotData(
            cpt::View auto const &x, 
            cpt::View auto const &y,
            cpt::View auto const &yerr,
            LinePlotDataConfig const &config_ = {}
        )
            : _x(cpt::collect<T>(x)),
              _y(cpt::collect<T>(y)),
              _xerr(std::nullopt),
              _yerr(cpt::collect<T>(yerr)),
              config(config_)
        {
            check_bounds();
            compute_extent();
        }

        // Delete copy constructor to enable only move of the underlying data
        LinePlotData(LinePlotData const &) = delete;

        LinePlotData(LinePlotData &&)            noexcept = default;
        LinePlotData &operator=(LinePlotData &&) noexcept = default;

        bool has_xerr() const noexcept { return _xerr.has_value(); }
        bool has_yerr() const noexcept { return _yerr.has_value(); }

        auto const &x() const noexcept { return _x; }
        auto const &y() const noexcept { return _y; }

        auto const &xerr() const {
            if (!_xerr) {
                throw InvalidLinePlotData("No error for x has been defined.");
            }
            return _xerr.value();
        }
        auto const &yerr() const {
            if (!_yerr) {
                throw InvalidLinePlotData("No error for y has been defined.");
            }
            return _yerr.value();
        }

        auto const &extent() const noexcept {
            return _extent;
        }

    protected:

        void check_bounds() const 
        {
            if (_x.size() != _y.size()) {
                throw InvalidLinePlotData(
                    "A line plot data must have the ",
                    "same dimension for x and y, ",
                    _x.size(), " and ", _y.size(), " found.");
            }
            if (_xerr.has_value() && _x.size() != _xerr.value().size()) {
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
            }
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
            auto x_extent = compute_extent(_x);
            auto y_extent = compute_extent(_y);
            _extent = {
                .xmin = x_extent.min,
                .xmax = x_extent.max,
                .ymin = y_extent.min,
                .ymax = y_extent.max
            };
        }

    private:
        cpt::Array<T> _x;
        cpt::Array<T> _y;
        std::optional<cpt::Array<T>> _xerr;
        std::optional<cpt::Array<T>> _yerr;

        cpt::Extent<T> _extent;

    public:
        LinePlotDataConfig config;
    };

} // namespace cpt

#endif