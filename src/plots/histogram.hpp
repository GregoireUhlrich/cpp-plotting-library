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

class HistogramStatistics {
  private:
    float mean;
    float error;
};

struct HistogramConfig {
    std::optional<float> min;
    std::optional<float> max;
    unsigned int         n_bins       = 0;
    float                marker_size  = 3.5f;
    sf::Color            marker_color = sf::Color(0, 64, 128);
    float                line_width   = 2.f;
    sf::Color            line_color   = sf::Color(0, 64, 128);
};

class Histogram : public cpt::PlotData {
  public:
    friend class HistogramStatistics;

    Histogram(ScienceDataArray<float> x, HistogramConfig const &config_ = {});

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

    cpt::Array<float> get_error(unsigned int bin);

    void draw_plot(cpt::PlotCanvas &canvas) const override;

  protected:
    void check_bounds() const;

    void compute_extent() noexcept;
    void
    compute_data(const ScienceDataArray<float> &data, float width, float maxi);

  private:
    ScienceDataArray<float> _x;
    ScienceDataArray<float> _y;

    cpt::Extent<float> _extent;

    void create_y_data(const cpt::ScienceDataArray<float> &y);

  public:
    HistogramConfig config;
};

} // namespace cpt

#endif