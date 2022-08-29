#include "axis.hpp"

namespace cpt
{
    Axis::Axis(
        Anchor anchor,
        float  size,
        AxisRendererConfig const &config
      )
      : _renderer(anchor, size, config)
    {
        set_extent(-1.f, +1.f);
    }

    static std::vector<cpt::Label> create_labels(
        std::vector<float> const &ticks
        )
    {
        std::vector<cpt::Label> labels(ticks.size());
        for (size_t i = 0; i != labels.size(); ++i) {

        }
        return labels;
    }

    void Axis::set_extent(
        float mini, 
        float maxi,
        AutoTicksConfiguration const &config
        )
    {
        _min = mini;
        _max = maxi;
        std::vector<float> ticks = calculate_ticks(_min, _max, config);
        std::vector<cpt::Label> labels = create_labels(ticks);
        _renderer.set_ticks(
            std::move(ticks),
            std::move(labels)
        );
    }

    void Axis::set_font(sf::Font const &font)
    {
      _renderer.set_font(font);
    }
} // namespace cpt
