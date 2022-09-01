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
        acknowledge_change();
    }

    void SubplotTexture::set_size(float sx, float sy)
    {
        _size = {sx, sy};
        acknowledge_change();
    }

    void SubplotTexture::set_font(sf::Font const &font)
    {
        _font = &font;
        for (auto &ax : _axis) {
            ax.second.set_font(*_font);
        }
        acknowledge_change();
    }

    void SubplotTexture::set_ticks(
        cpt::Anchor             anchor,
        std::vector<float>      positions, 
        std::vector<cpt::Label> values)
    {
        int size = (anchor == Anchor::Top || anchor == Anchor::Bottom) ?
            _canvas_bounds.width : _canvas_bounds.height;
        auto &ax = (
            _axis[anchor] = cpt::AxisRenderer(
                anchor, 
                static_cast<float>(size))
        );
        ax.set_ticks(std::move(positions), std::move(values));
        acknowledge_change();
    }

    void SubplotTexture::acknowledge_change()
    {
        _up_to_date = false;
    }

    void SubplotTexture::update()
    {
        if (!_up_to_date) {
            update_axis(); // calculate a first time axis bounds 
            update_canvas_bounds(); // setup the canvas from axis bounds
            update_textures();
            update_axis(); // recalculate axis pos and size from axis bounds
            _up_to_date = true;
        }
    }

    void SubplotTexture::update_canvas_bounds()
    {
        AxisRenderer const *left_axis   = get_axis(Anchor::Left);
        AxisRenderer const *right_axis  = get_axis(Anchor::Right);
        AxisRenderer const *top_axis    = get_axis(Anchor::Top);
        AxisRenderer const *bottom_axis = get_axis(Anchor::Bottom);
        float left_space   = left_axis   ?   left_axis->get_bounds().width  : 0.f;
        float right_space  = right_axis  ?  right_axis->get_bounds().width  : 0.f;
        float top_space    = top_axis    ?    top_axis->get_bounds().height : 0.f;
        float bottom_space = bottom_axis ? bottom_axis->get_bounds().height : 0.f;

        _canvas_bounds = sf::IntRect(
            static_cast<int>(left_space), 
            static_cast<int>(top_space), 
            static_cast<int>(std::floor(_size.x - (left_space + right_space))), 
            static_cast<int>(std::floor(_size.y - (top_space + bottom_space)))
        );
    }

    void SubplotTexture::update_textures()
    {
        _texture.create(
            static_cast<unsigned int>(_size.x),
            static_cast<unsigned int>(_size.y)
            );
        _canvas.create(
            _canvas_bounds.width,
            _canvas_bounds.height
        );
        _texture.clear(sf::Color::White);
        _canvas.clear(sf::Color::White);
    }

    void SubplotTexture::update_axis()
    {
        for (auto &p : _axis) {
            AxisRenderer &ax = p.second;
            bool horizontal = ax.get_anchor() == Anchor::Top || ax.get_anchor() == Anchor::Bottom;
            int size = horizontal ? _canvas_bounds.width : _canvas_bounds.height;
            ax.set_size(static_cast<float>(size));
            ax.set_font(get_font());
            switch (ax.get_anchor()) {
                case Anchor::Left:
                case Anchor::Top:
                    ax.set_position(
                        static_cast<float>(_canvas_bounds.left), 
                        static_cast<float>(_canvas_bounds.top));
                    break;
                case Anchor::Bottom:
                    ax.set_position(
                        static_cast<float>(_canvas_bounds.left), 
                        static_cast<float>(_canvas_bounds.top + _canvas_bounds.height));
                    break;
                case Anchor::Right:
                    ax.set_position(
                        static_cast<float>(_canvas_bounds.left + _canvas_bounds.width), 
                        static_cast<float>(_canvas_bounds.top));
                    break;
                default:
                    throw InvalidAnchorError(
                        "Anchor of value ",
                        static_cast<int>(ax.get_anchor()),
                        " is inknown."
                    );
            }
            ax.update();
        }
    }

    void SubplotTexture::assert_up_to_date() const 
    {
        if (!_up_to_date) {
            throw InvalidSubplotTextureError(
                "Invalid use of a modified SubplotTexture.",
                "Please call .update() before."
            );
        }
    }

    void SubplotTexture::display()
    {
        assert_up_to_date();
        _canvas.display();
        sf::Sprite canvas_sprite = _canvas.get_sprite();
        canvas_sprite.setPosition(
            static_cast<float>(_canvas_bounds.left), 
            static_cast<float>(_canvas_bounds.top));
        _texture.draw(canvas_sprite);
        for (const auto &[_, axis] : _axis) {
            axis.draw(_texture);
        }
        _texture.display();
        _final_texture = _texture.getTexture();
        _sprite.setTexture(_final_texture);
        _sprite.setPosition(_pos.x, _pos.y);
    }
} // namespace cpt
