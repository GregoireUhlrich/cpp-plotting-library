#ifndef CPT_SUBPLOT_TEXTURE_H_INCLUDED
#define CPT_SUBPLOT_TEXTURE_H_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>
#include "plot_canvas.hpp"
#include "axis_renderer.hpp"
#include "../utils/error.hpp"

namespace cpt
{
    class InvalidSubplotTextureError: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    class SubplotTexture {
    public:
        SubplotTexture();
        SubplotTexture(SubplotTexture const &) = delete;

        cpt::AxisRenderer const *get_axis(cpt::Anchor anchor) const;

        sf::Font const &get_font() const;
        sf::Vector2f get_position() const noexcept;
        sf::Vector2f get_size() const noexcept;

        void set_position(float x, float y) noexcept;
        void set_size(float sx, float sy);

        void set_font(sf::Font const &font);
        
        void create();

        void draw(sf::RenderTarget &target) const;
        
        void set_ticks(
            cpt::Anchor             anchor,
            std::vector<float>      positions, 
            std::vector<cpt::Label> labels);

    private:

        sf::FloatRect calculate_canvas_bounds();
    
    protected:
        sf::Vector2f _pos;
        sf::Vector2f _size;
        sf::Font           const *_font = nullptr;
        mutable sf::RenderTexture _texture;
        std::map<cpt::Anchor, cpt::AxisRenderer> _axis;

        sf::FloatRect _canvas_bounds;
        PlotCanvas    _canvas;
    };

} // namespace cpt

#endif
