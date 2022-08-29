#include "subplot_texture.hpp"
#include <iostream>

namespace cpt
{
    SubplotTexture::SubplotTexture()
    {
        set_size(50.f, 50.f);
    }

    sf::Vector2f SubplotTexture::get_position() const noexcept
    {
        return _pos;
    }

    sf::Vector2f SubplotTexture::get_size() const noexcept
    {
        return _size;
    }

    void SubplotTexture::set_position(float x, float y) noexcept
    {
        _pos = {x, y};
    }

    void SubplotTexture::set_size(float sx, float sy)
    {
        _size = {sx, sy};
        _texture.create(
            static_cast<unsigned int>(sx),
            static_cast<unsigned int>(sy)
            );
        _canvas.create(
            static_cast<unsigned int>(sx),
            static_cast<unsigned int>(sy)
        );
    }

    void SubplotTexture::draw(sf::RenderTarget &target) const
    {
        sf::Sprite sprite;
        _texture.clear(sf::Color::Green);
        _texture.draw(_canvas.get_sprite());
        for (const auto &[_, axis] : _axis) {
            axis.draw(_texture);
        }
        _texture.display();

        sprite.setTexture(_texture.getTexture());
        sprite.setPosition(get_position());
        target.draw(sprite);
    }
} // namespace cpt