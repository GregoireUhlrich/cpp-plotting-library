#ifndef CPT_AXIS_H_INCLUDED
#define CPT_AXIS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../math_views.hpp"
#include "../utils/direction.hpp"
#include "label.hpp"

namespace cpt
{
    class AxisRenderer {
    public:
        AxisRenderer(cpt::Anchor anchor, float size);

        sf::Vector2f get_position()  const noexcept { return _pos; }
        float        get_size()      const noexcept { return _size; }
        Anchor       get_anchor()    const noexcept { return _anchor; }

        void set_position(float sx, float sy) noexcept { _pos = {sx, sy}; }
        void set_size(float size)             noexcept { _size = size; } 
        void set_anchor(Anchor anchor)        noexcept { _anchor = anchor; }

        template<ArrayRange Range1, ArrayRange Range2> 
        void set_ticks(Range1 const &positions, Range2 const &values);

        void draw(sf::RenderTarget &target) const;

    private:
        Anchor         _anchor;
        sf::Vector2f   _pos;
        float          _size;
        std::vector<float>      _ticks_positions;
        std::vector<cpt::Label> _ticks_names;
    };
} // namespace cpt


#endif