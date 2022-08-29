#ifndef CPT_AXIS_H_INCLUDED
#define CPT_AXIS_H_INCLUDED

#include "../graphics/axis_renderer.hpp"
#include "ticks.hpp"

namespace cpt
{
    class Axis {
    public:
        Axis(
            cpt::Anchor anchor,
            float       size,
            AxisRendererConfig const &config = {}
            );

        void set_extent(
            float mini, 
            float maxi,
            AutoTicksConfiguration const &config = {}
            );

        void set_font(sf::Font const &font);

    private:

        float _min;
        float _max;
        AxisRenderer _renderer;
    };

} // namespace cpt

#endif
