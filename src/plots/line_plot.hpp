/*!
 * @file line_plot.hpp
 *
 * @brief Classes and configurations for line plots.
 */
#ifndef LINE_PLOT_DATA_H_INCLUDED
#define LINE_PLOT_DATA_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../utils/error.hpp"
#include "../math_views.hpp"
#include "../utils/extent.hpp"
#include "../utils/science_data_array.hpp"
#include "../utils/plot_data.hpp"

#include <concepts>
#include <numeric>
#include <optional>

namespace cpt
{
    /*!
     * @brief Exception raised when the user-defined line plot 
     * data is invalid.
     */
    class InvalidLinePlotData: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    /*!
     * @brief Configuration for a line plot.
     */
    struct LinePlotConfig {
        /*!
         * @brief Marker size in pixels. 
         *
         * @details A marker is a point drawn at a given (x, y) location.
         */
        float     marker_size  = 3.5f;

        /*!
         * @brief Marker color.
         *
         * @details A marker is a point drawn at a given (x, y) location.
         */
        cpt::Color marker_color = cpt::Color(0, 64, 128);

        /*!
         * @brief Line width in pixels. 
         *
         * @details The lines connect the different points (markers) in 
         * the plot.
         */
        float     line_width   = 2.f;

        /*!
         * @brief Line color.
         *
         * @details The lines connect the different points (markers) in 
         * the plot.
         */
        cpt::Color line_color   = cpt::Color(0, 64, 128);
    };

    /*!
     * @brief Represents a line plot object containing the data.
     *
     * @details It contains the x and y data (including possible uncertainties)
     * but is not responsible to plot itself. Final plotting is the role of 
     * the `cpt::PlotCanvas` class.
     */
    class LinePlot: public cpt::PlotData {

    public:
        LinePlot(
            ScienceDataArray<float> x,
            ScienceDataArray<float> y,
            LinePlotConfig const &config_ = {});

        // Delete copy constructor to enable only move of the underlying data
        LinePlot(LinePlot const &) = delete;

        LinePlot(LinePlot &&)            noexcept = default;
        LinePlot &operator=(LinePlot &&) noexcept = default;

        bool has_xerr() const noexcept { return _x.err_plus.has_value(); }
        bool has_yerr() const noexcept { return _y.err_plus.has_value(); }

        auto const &x() const noexcept { return _x.data; }
        auto const &y() const noexcept { return _y.data; }

        cpt::Array<float> const &xerr(bool lower = false) const;
        cpt::Array<float> const &yerr(bool lower = false) const;

        cpt::Extent<float> get_extent() const override;

        void draw_plot(cpt::PlotCanvas &canvas) const override;

    protected:

        void check_bounds() const;

        void compute_extent() noexcept;

    private:
        ScienceDataArray<float> _x;
        ScienceDataArray<float> _y;

        cpt::Extent<float> _extent;

    public:
        /*!
         * @brief Plot configuration.
         *
         * @details This parameter is public to allow direct modifications.
         */
        LinePlotConfig config;
    };
    
} // namespace cpt

#endif
