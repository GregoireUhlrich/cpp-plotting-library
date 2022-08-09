#include "subplot.hpp"

namespace cpt
{
    sf::Vector2f Subplot::get_position() const noexcept
    {
        return _pos;
    }

    sf::Vector2f Subplot::get_size() const noexcept
    {
        return _size;
    }

    void Subplot::set_position(float x, float y) noexcept
    {
        _pos = {x, y};
    }

    void Subplot::set_size(float sx, float sy) noexcept
    {
        _size = {sx, sy};
    }
} // namespace cpt
