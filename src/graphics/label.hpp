#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include "../utils/direction.hpp"
#include "fonts.hpp"

namespace cpt
{
    class Label {
    public:

        enum Alignement {
            Centered,
            Left,
            Right,
            Top,
            Bottom,
            TopLeft,
            TopRight, 
            BottomLeft,
            BottomRight
        };

        Label() = default;

        Label(
            std::string const &text,
            sf::Font    const &font
        );

        void set_font(sf::Font const &font);

        void set_text(std::string const &text);

        sf::Color get_fill_color() const;
        void set_fill_color(sf::Color color);

        sf::Vector2f get_size() const;

        sf::Vector2f get_text_offset() const;

        sf::Vector2f get_position() const;
        void set_position(float x, float y);

        unsigned int get_font_size() const noexcept;
        void set_font_size(unsigned int size);
        
        float get_rotation() const;
        void set_rotation(float angle);
        void rotate(float angle);

        Alignement get_alignement() const noexcept;
        void set_alignement(Alignement alignement);

        void draw(sf::RenderTarget &target) const;

    private:

        unsigned int    _font_size;
        Alignement      _alignement;
        sf::Font const *_font;
        sf::Text        _text;
    };

    // PS: For some reason fonts are unusable on Windows.
    // Thx, back to Linux :)

} // namespace cpt


#endif
