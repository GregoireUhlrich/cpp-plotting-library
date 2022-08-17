#ifndef CPT_AXIS_H_INCLUDED
#define CPT_AXIS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../math_views.hpp"

namespace cpt
{
    class Axis {
    public:
        enum Anchor { Up, Down, Left, Right };

        Axis(Anchor anchor, float size);

        sf::Vector2f get_position()  const noexcept { return _pos; }
        float        get_size()      const noexcept { return _size; }
        Anchor       get_anchor()    const noexcept { return _anchor; }

        void set_position(float sx, float sy) noexcept { _pos = {sx, sy}; }
        void set_size(float size)             noexcept { _size = size; } 
        void set_anchor(Anchor anchor)        noexcept { _anchor = anchor; }

        void set_extent(float mini, float maxi);

        template<ArrayRange Range1, ArrayRange Range2> 
        void set_ticks(Range1 const &positions, Range2 const &values);

        void draw(sf::RenderTarget &target) const;

    private:
        Anchor         _anchor;
        sf::Vector2f   _pos;
        float          _size;
        std::vector<float>    _ticks_positions;
        std::vector<sf::Text> _ticks_names;
    };

    template<ArrayRange Range1, ArrayRange Range2> 
    void Axis::set_ticks(Range1 const &positions, Range2 const &values)
    {
        _ticks_positions = cpt::collect<float>(positions);
        _ticks_names.resize(std::ranges::size(values));
         std::ranges::transform(
            values.begin(),
            values.end(),
            _ticks_names.begin(),
            [](auto val) {
                return sf::String(std::to_string(val));
            }
        );
    }

} // namespace cpt


#endif