#include "subplot.hpp"
#include <iostream>
namespace cpt
{
    Subplot::Subplot()
    {
        set_size(50.f, 50.f);
    }

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

    void Subplot::set_size(float sx, float sy)
    {
        _size = {sx, sy};
        _texture.create(
            static_cast<unsigned int>(sx),
            static_cast<unsigned int>(sy)
            );
        _texture.clear(sf::Color::Green);
        _texture.display();
    }

    void Subplot::draw(sf::RenderTarget &target) const
    {
        sf::Sprite sprite;
        _texture.clear(sf::Color::Green);
        _texture.display();
        sprite.setTexture(_texture.getTexture());
        sprite.setPosition(get_position());
        target.draw(sprite);
    }
} // namespace cpt
