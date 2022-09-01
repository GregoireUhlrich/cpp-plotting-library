#ifndef CPT_PLOT_DATA_H_INCLUDED
#define CPT_PLOT_DATA_H_INCLUDED

#include "extent.hpp"

namespace cpt {
class PlotCanvas;

class PlotData {
  public:
    virtual ~PlotData()
    {
    }

    virtual cpt::Extent<float> get_extent() const                       = 0;
    virtual void               draw_plot(cpt::PlotCanvas &canvas) const = 0;
};

inline auto compute_extent(cpt::Array<float> const &arr) noexcept
{
    struct MinMax {
        float min, max;
    };
    MinMax res{.min = std::numeric_limits<float>::max(),
               .max = std::numeric_limits<float>::lowest()};
    for (float val : arr) {
        if (val < res.min)
            res.min = val;
        if (val > res.max)
            res.max = val;
    }
    return res;
}

} // namespace cpt

#endif