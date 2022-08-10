#ifndef CPT_PLOT_DATA_H_INCLUDED
#define CPT_PLOT_DATA_H_INCLUDED

#include "extent.hpp"

namespace cpt
{
    class PlotCanvas;

    class PlotData {
    public:
        virtual ~PlotData() {}

        virtual cpt::Extent<float> get_extent()         const = 0;
        virtual void draw_plot(cpt::PlotCanvas &canvas) const = 0;
    };
} // namespace cpt


#endif