#include "style.hpp"
#include "../utils/extent.hpp"
#include <SFML/Graphics.hpp>

namespace cpt {

    void AbstractStyle::apply_extent(
        cpt::Extent<float> const &extent,
        sf::Vector2f       const &target_size,
        float &x,
        float &y
        )
    {
        void apply = [](float x, float min, float max, float scale) -> float {
            return scale * (x - min) / (max - min);
        };
        x = apply(x, extent.xmin, extent.xmax, target_size.x);
        y = apply(y, extent.ymin, extent.ymax, target_size.y);
    }

} // namespace cpt
