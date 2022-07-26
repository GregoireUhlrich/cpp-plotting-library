#ifndef HISTOGRAM_DATA_H_INCLUDED
#define HISTOGRAM_DATA_H_INCLUDED

#include "../math_views.hpp"
#include "../utils/error.hpp"
#include "../utils/extent.hpp"
#include "../utils/plot_data.hpp"
#include "../utils/science_data_array.hpp"
#include <SFML/Graphics.hpp>

#include <concepts>
#include <numeric>
#include <optional>

namespace cpt {
class InvalidHistogramData : public cpt::Exception {
    using cpt::Exception::Exception;
};

struct HistogramConfig {
    float     marker_size  = 3.5f;
    sf::Color marker_color = sf::Color(0, 64, 128);
    float     line_width   = 2.f;
    sf::Color line_color   = sf::Color(0, 64, 128);
};

class Histogram : public cpt::PlotData {
  public:
    Histogram(ScienceDataArray<float> x,
              ScienceDataArray<float> y,
              HistogramConfig const  &config_ = {});

    // Delete copy constructor to enable only move of the underlying data
    Histogram(Histogram const &) = delete;

    Histogram(Histogram &&) noexcept            = default;
    Histogram &operator=(Histogram &&) noexcept = default;

    bool has_xerr() const noexcept
    {
        return _x.err_plus.has_value();
    }
    bool has_yerr() const noexcept
    {
        return _y.err_plus.has_value();
    }

    auto const &x() const noexcept
    {
        return _x.data;
    }
    auto const &y() const noexcept
    {
        return _y.data;
    }

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
    HistogramConfig config;
};

} // namespace cpt

#endif