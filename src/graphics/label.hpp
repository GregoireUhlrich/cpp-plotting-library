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
        Label() = default;

        Label(
            std::string const &text,
            sf::Font    const &font
        );

        void set_font(sf::Font const &font);

        void set_text(std::string const &text);

        sf::Color get_fill_color() const;
        void set_fill_color(sf::Color color);

        sf::FloatRect get_bounds() const noexcept;

        sf::Vector2f get_position() const;
        void set_position(float x, float y);

        unsigned int get_font_size() const noexcept;
        void set_font_size(unsigned int size);

        void draw(sf::RenderTarget &target) const;

    private:

        unsigned int    _font_size;
        sf::Font const *_font;
        sf::Text        _text;
    };

    // PS: For some reason fonts are unusable on Windows.
    // Thx, back to Linux :)

} // namespace cpt


#endif
