#include "subplot_texture.hpp"
#include <iostream>

namespace cpt
{
    SubplotTexture::SubplotTexture()
    {
        set_size(50.f, 50.f);
    }

    cpt::AxisRenderer const *SubplotTexture::get_axis(
        cpt::Anchor anchor
        ) const 
    {
        auto pos = _axis.find(anchor);
        if (pos == _axis.end()) {
            return nullptr;
        }
        return &pos->second;
    }

    sf::Font const &SubplotTexture::get_font() const
    {
        if (!_font) {
            throw InvalidSubplotTextureError(
                "Getting the font of a SubplotTexture for which none",
                " has been defined yet."
                );
        }
        return *_font;
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
    }

    void SubplotTexture::set_font(sf::Font const &font)
    {
        _font = &font;
        for (auto &ax : _axis) {
            ax.second.set_font(*_font);
        }
    }

    sf::FloatRect SubplotTexture::calculate_canvas_bounds()
    {
        AxisRenderer const *left_axis   = get_axis(Anchor::Left);
        AxisRenderer const *right_axis  = get_axis(Anchor::Right);
        AxisRenderer const *top_axis    = get_axis(Anchor::Up);
        AxisRenderer const *bottom_axis = get_axis(Anchor::Down);
        float left_space   = left_axis   ?   left_axis->get_bounds().width  : 0.f;
        float right_space  = right_axis  ?  right_axis->get_bounds().width  : 0.f;
        float top_space    = top_axis    ?    top_axis->get_bounds().height : 0.f;
        float bottom_space = bottom_axis ? bottom_axis->get_bounds().height : 0.f;

        return sf::FloatRect(
            left_space, 
            top_space, 
            _size.x - (left_space + right_space), 
            _size.y - (top_space + bottom_space)
        );
    }

    void SubplotTexture::set_ticks(
        cpt::Anchor             anchor,
        std::vector<float>      positions, 
        std::vector<cpt::Label> values)
    {
        float size = (anchor == Anchor::Up || anchor == Anchor::Down) ?
            _canvas_bounds.width : _canvas_bounds.height;
        auto &ax = (_axis[anchor] = cpt::AxisRenderer(anchor, size));
        ax.set_font(get_font());
        switch (anchor) {
            case Anchor::Left:
            case Anchor::Up:
                ax.set_position(_canvas_bounds.left, _canvas_bounds.top);
                break;
            case Anchor::Down:
                ax.set_position(_canvas_bounds.left, _canvas_bounds.top + _canvas_bounds.height);
                break;
            case Anchor::Right:
                ax.set_position(_canvas_bounds.left + _canvas_bounds.width, _canvas_bounds.top);
                break;
            default:
                throw InvalidAnchorError(
                    "Anchor of value ",
                    static_cast<int>(anchor),
                    " is inknown."
                );
        }
        ax.set_ticks(std::move(positions), std::move(values));
    }

    void SubplotTexture::create()
    {
        _texture.create(
            static_cast<unsigned int>(_size.x),
            static_cast<unsigned int>(_size.y)
            );
        _canvas_bounds = calculate_canvas_bounds();
        _canvas.create(
            static_cast<unsigned int>(_canvas_bounds.width),
            static_cast<unsigned int>(_canvas_bounds.height)
        );
    }

    void SubplotTexture::draw(sf::RenderTarget &target) const
    {
        sf::Sprite sprite;

        _texture.clear(sf::Color::White);
        sf::Sprite canvas_sprite = _canvas.get_sprite();
        canvas_sprite.setPosition(_canvas_bounds.left, _canvas_bounds.top);
        _texture.draw(canvas_sprite);
        for (const auto &[_, axis] : _axis) {
            axis.draw(_texture);
        }
        _texture.display();

        sprite.setTexture(_texture.getTexture());
        sprite.setPosition(get_position());
        target.draw(sprite);
    }
} // namespace cpt
