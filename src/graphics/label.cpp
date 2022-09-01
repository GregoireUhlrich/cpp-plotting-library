#include "label.hpp"
#include "../utils/printable.hpp"
#include "../utils/error.hpp"

namespace cpt {

    Label::Label(std::string const &text, sf::Font const &font)
    {
        set_font(font);
        set_text(text);
        set_font_size(10);
        set_fill_color(sf::Color::Black);
        set_alignement(Alignement::Centered);
    }

    void Label::set_font(sf::Font const &font)
    {
        _font = &font;
        _text.setFont(*_font);
    }

    void Label::set_text(std::string const &text)
    {
        _text.setString(sf::String(text));
    }

    sf::Color Label::get_fill_color() const 
    {
        return _text.getFillColor();
    }

    void Label::set_fill_color(sf::Color color)
    {
        _text.setFillColor(color);
    } 

    sf::Vector2f Label::get_text_size() const
    {
        sf::Text cpy = _text;
        cpy.setRotation(0.f);
        auto bounds = cpy.getGlobalBounds();
        return {
            bounds.width,
            bounds.height
        };
    }

    sf::Vector2f Label::get_graphics_size() const
    {
        auto bounds = _text.getGlobalBounds();
        return {
            bounds.width,
            bounds.height
        };
    }

    sf::Vector2f Label::get_text_offset() const 
    {
        sf::Text cpy = _text;
        cpy.setRotation(0.f);
        auto bounds = cpy.getGlobalBounds();
        auto pos    = cpy.getPosition();
        auto origin = cpy.getOrigin();
        return {
            bounds.left - (pos.x - origin.x),
            bounds.top  - (pos.y - origin.y)
        };
    }

    sf::Vector2f Label::get_position() const 
    {
        return _text.getPosition();
    }

    void Label::set_position(float x, float y)
    {
        _text.setPosition(x, y);
    }

    unsigned int Label::get_font_size() const noexcept 
    {
        return _font_size;
    }

    void Label::set_font_size(unsigned int font_size) 
    {
        _font_size = font_size;
        _text.setCharacterSize(font_size);
    }

    float Label::get_rotation() const
    {
        return _text.getRotation();
    }

    void Label::set_rotation(float angle)
    {
        _text.setRotation(angle);
    }

    void Label::rotate(float angle)
    {
        _text.rotate(angle);
    }

    Label::Alignement Label::get_alignement() const noexcept
    {
        return _alignement;
    }

    static float relative_position(Label::Alignement align, bool x_axis)
    {
        if (x_axis) {
            switch(align) {
                case Label::Centered:
                case Label::Top:
                case Label::Bottom:
                    return 0.5f;
                case Label::Left:
                case Label::TopLeft:
                case Label::BottomLeft:
                    return 0.f;
                case Label::Right:
                case Label::TopRight:
                case Label::BottomRight:
                    return 1.f;
            }
        }
        else {
            switch(align) {
                case Label::Centered:
                case Label::Left:
                case Label::Right:
                    return 0.5f;
                case Label::Top:
                case Label::TopLeft:
                case Label::TopRight:
                    return 0.f;
                case Label::Bottom:
                case Label::BottomLeft:
                case Label::BottomRight:
                    return 1.f;
            }
        }
        class AlignementError: public cpt::Exception {
            using cpt::Exception::Exception;
        }; 
        throw AlignementError("Alignement of value ", align, " is invalid.");
    }

    void Label::set_alignement(Label::Alignement alignement)
    {
        sf::Vector2f origin = get_text_offset();
        sf::Vector2f size   = get_text_size();
        sf::Vector2f new_origin = {
            origin.x + relative_position(alignement, 1) * size.x,
            origin.y + relative_position(alignement, 0) * size.y
        };
        _text.setOrigin(new_origin);
        _alignement = alignement;
    }

    void Label::draw(sf::RenderTarget &target) const
    {
        target.draw(_text);
    }

    } // namespace cpt
