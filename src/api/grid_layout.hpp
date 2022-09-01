#ifndef CPT_GRIDLAYOUT_H_INCLUDED
#define CPT_GRIDLAYOUT_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace cpt
{
    inline constexpr std::size_t min_subplot_n_pix = 25;

    struct GridLayoutConfig {
        float offset_left   = 0.05f;
        float offset_right  = 0.05f;
        float offset_top    = 0.05f;
        float offset_bottom = 0.05f;

        float hspace = 0.05f;
        float vspace = 0.05f;
    };

    class Figure;

    void apply_grid_layout(
        sf::FloatRect           bounds,
        cpt::Figure            &figure,
        GridLayoutConfig const &config = {}
    );

} // namespace cpt

#endif