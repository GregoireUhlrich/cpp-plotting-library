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

        static inline sf::Font const &default_font 
            =  cpt::font::arial.get_font(cpt::font::Regular);
    
        Label(
            std::string const &text = "",
            sf::Font    const &font = default_font
        );

        void set_font(sf::Font const &font);

        void set_text(std::string const &text);

        sf::Vector2f get_size()               const noexcept;
        float        get_size(cpt::Axis axis) const noexcept;

        sf::Vector2f get_position() const;
        void set_position(float x, float y);

        unsigned int get_font_size() const noexcept;
        void set_font_size(unsigned int size);

        void draw(sf::RenderTarget &target) const;

    private:

        unsigned int _font_size;
        sf::Text     _text;
    };
} // namespace cpt


#endif