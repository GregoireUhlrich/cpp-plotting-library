#include "label.hpp"
#include "../utils/printable.hpp"

namespace cpt {

    Label::Label(std::string const &text, sf::Font const &font)
    {
        set_font(font);
        set_text(text);
        set_font_size(10);
        set_fill_color(sf::Color::Black);
    }

    void Label::set_font(sf::Font const &font)
    {
        _text.setFont(font);
    }

    void Label::set_text(std::string const &text)
    {
        _text.setString(sf::String(text));
    }

    template<class AxisType>
    [[noreturn]] static void _throw_invalid_axis_error(AxisType axis) 
        requires (std::same_as<AxisType, cpt::Axis> && cpt::Printable<AxisType>)
    {
        throw InvalidAxisError("Axis ", axis, " not recognized");
    }

    template<class AxisType>
    [[noreturn]] static void _throw_invalid_axis_error(AxisType axis) 
        requires (std::same_as<AxisType, cpt::Axis> && !cpt::Printable<AxisType>)
    {
        throw InvalidAxisError("Axis ", static_cast<int>(axis), " not recognized");
    }

    sf::Color Label::get_fill_color() const 
    {
        return _text.getFillColor();
    }

    void Label::set_fill_color(sf::Color color)
    {
        _text.setFillColor(color);
    } 

    float Label::get_size(cpt::Axis axis) const noexcept
    {
        switch (axis) {
            case cpt::Axis::X: 
                return _text.getLocalBounds().width;
            case cpt::Axis::Y: 
                return _text.getLocalBounds().height;
            default:
                _throw_invalid_axis_error(axis);
        }
    }

    sf::Vector2f Label::get_size() const noexcept 
    {
        return sf::Vector2f{ 
            get_size(cpt::Axis::X), 
            get_size(cpt::Axis::Y)
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

    void Label::draw(sf::RenderTarget &target) const
    {
        target.draw(_text);
    }

    } // namespace cpt