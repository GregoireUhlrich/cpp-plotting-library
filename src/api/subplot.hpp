#ifndef CPT_SUBPLOT_H_INCLUDED
#define CPT_SUBPLOT_H_INCLUDED

#include "../graphics/plot_canvas.hpp"
#include "../graphics/subplot_texture.hpp"
#include "../plots/histogram.hpp"
#include "../plots/line_plot.hpp"
#include "../utils/plot_data.hpp"
#include <map>
#include <vector>

namespace cpt {
class Subplot : public SubplotTexture {

  public:
    Subplot();
    Subplot(Subplot const &) = delete;

    void plot_line(ScienceDataArray<float> x,
                   ScienceDataArray<float> y,
                   LinePlotConfig const   &config = {});

    void histogram(ScienceDataArray<float> x,
                   ScienceDataArray<float> y,
                   HistogramConfig const  &config = {});

    bool has_auto_extent() const noexcept
    {
        return !_user_extent;
    }
    void set_auto_extent() noexcept
    {
        _user_extent = false;
    }

    Extent<float> get_extent();
    void          set_extent(Extent<float> extent) noexcept;

    void display();

  private:
    void compute_extent();
    void setup_default_axis(cpt::Extent<float> const &extent);

  private:
    bool                                        _user_extent = false;
    Extent<float>                               _extent;
    std::vector<std::shared_ptr<cpt::PlotData>> _plots;
};
} // namespace cpt

#endif
