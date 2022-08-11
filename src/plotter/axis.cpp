#include "axis.hpp"

namespace cpt
{
    Axis::Axis(Direction dir, float size, AxisConfiguration const &config)
        : _dir(dir),
          _size(size),
          _config(config)
    {

    }

    void Axis::draw(sf::RenderTarget &target) const 
    {
        const float rect_length  = _size - _config.arrow_width / 2.f;
        const float rect_width   = _config.line_width;
        const float arrow_radius = _config.arrow_width / 2.f;
        sf::RectangleShape line(sf::Vector2f{rect_length, rect_width});
        sf::CircleShape    arrow(arrow_radius, 3);
        line.setOrigin(0.f, rect_width / 2.f);
        arrow.setOrigin(arrow_radius, arrow_radius);
        line.setFillColor(_config.color);
        arrow.setFillColor(_config.color);

        line.setPosition(_pos);
        arrow.setPosition(_pos.x + rect_length, _pos.y);
        arrow.rotate(90.f);
        switch (_dir) {
            case Up:
            line.rotate(-90.f);
            arrow.rotate(-90.f);
            arrow.setPosition(_pos.x, _pos.y - rect_length);
            break;
            
            case Down:
            line.rotate(90.f);
            arrow.rotate(90.f);
            arrow.setPosition(_pos.x, _pos.y + rect_length);
            break;

            case Left:
            arrow.rotate(180.f);
            line.rotate(180.f);
            arrow.setPosition(_pos.x - rect_length, _pos.y);
            break;

            case Right:
            arrow.setPosition(_pos.x + rect_length, _pos.y);
            break;
        }
        target.draw(line);
        target.draw(arrow);
    }

} // namespace cpt
