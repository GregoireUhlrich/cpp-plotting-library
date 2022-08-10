#ifndef CPT_SUBPLOT_TEXTURE_H_INCLUDED
#define CPT_SUBPLOT_TEXTURE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "plot_canvas.hpp"

namespace cpt
{
    class SubplotTexture {
    public:
        SubplotTexture();
        SubplotTexture(SubplotTexture const &) = delete;
        SubplotTexture(SubplotTexture &&) noexcept = default;

        sf::Vector2f get_position() const noexcept;
        sf::Vector2f get_size() const noexcept;

        void set_position(float x, float y) noexcept;
        void set_size(float sx, float sy);
        
        void draw(sf::RenderTarget &target) const;
    
    protected:
        sf::Vector2f _pos;
        sf::Vector2f _size;
        mutable sf::RenderTexture _texture;

        PlotCanvas _canvas;
    };
} // namespace cpt

#endif