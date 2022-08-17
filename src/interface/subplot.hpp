#ifndef CPT_SUBPLOT_H_INCLUDED
#define CPT_SUBPLOT_H_INCLUDED

#include "../graphics/subplot_texture.hpp"
#include "../graphics/plot_canvas.hpp"
#include "../plots/line_plot.hpp"
#include "../utils/plot_data.hpp"
#include <vector>
#include <memory>

namespace cpt
{
    class Subplot: public SubplotTexture {

    public:
        Subplot()               = default;
        Subplot(Subplot const&) = delete;
        Subplot(Subplot &&)     = default;

        void plot_line(
            ScienceDataArray<float> x,
            ScienceDataArray<float> y,
            LinePlotConfig const &config = {}
        );

        bool has_auto_extent() const noexcept { return !_user_extent; }
        void set_auto_extent() noexcept       { _user_extent = false; }

        void set_extent(Extent<float> extent) noexcept;

        Extent<float> get_extent();

        void display();

    private:
        void compute_extent();

    private:
        bool          _user_extent = false;
        Extent<float> _extent;
        std::vector<std::shared_ptr<cpt::PlotData>> _plots;
    };
} // namespace cpt

#endif