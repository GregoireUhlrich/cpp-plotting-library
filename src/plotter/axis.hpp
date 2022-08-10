#ifndef CPT_AXIS_H_INCLUDED
#define CPT_AXIS_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace cpt
{
    struct AxisConfiguration {
        float     line_width  = 3.f;
        float     arrow_width = 10.f;
        sf::Color color       = sf::Color::Black;
    };

    class Axis {
    public:
        enum Direction { Up, Down, Left, Right };

        Axis(Direction dir, float size, AxisConfiguration const &config = {});

        sf::Vector2f get_position()  const noexcept { return _pos; }
        float        get_size()      const noexcept { return _size; }
        Direction    get_direction() const noexcept { return _dir; }

        void set_position(float sx, float sy) noexcept { _pos = {sx, sy}; }
        void set_size(float size)             noexcept { _size = size; } 
        void set_direction(Direction dir)     noexcept { _dir = dir; }

        AxisConfiguration       &config()       noexcept { return _config; }
        AxisConfiguration const &config() const noexcept { return _config; }

        void draw(sf::RenderTarget &target) const;

    private:
        Direction         _dir;
        sf::Vector2f      _pos;
        float             _size;
        AxisConfiguration _config;
    };


} // namespace cpt


#endif