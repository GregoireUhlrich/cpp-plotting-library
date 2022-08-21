#ifndef CPT_SUBPLOT_TEXTURE_H_INCLUDED
#define CPT_SUBPLOT_TEXTURE_H_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>
#include "plot_canvas.hpp"
#include "../api/axis.hpp"

namespace cpt
{
    class SubplotTexture {
    public:
        SubplotTexture();
        SubplotTexture(SubplotTexture const &) = delete;

        sf::Vector2f get_position() const noexcept;
        sf::Vector2f get_size() const noexcept;

        void set_position(float x, float y) noexcept;
        void set_size(float sx, float sy);
        
        void draw(sf::RenderTarget &target) const;
        
        template<ArrayRange Range1, ArrayRange Range2> 
        void set_ticks(
            cpt::AxisRenderer::Anchor anchor,
            Range1     const &positions, 
            Range2     const &values);
    
    protected:
        sf::Vector2f _pos;
        sf::Vector2f _size;
        mutable sf::RenderTexture _texture;
        std::map<cpt::AxisRenderer::Anchor, cpt::AxisRenderer> _axis;

        PlotCanvas _canvas;
    };

    template<ArrayRange Range1, ArrayRange Range2> 
    void SubplotTexture::set_ticks(
        cpt::AxisRenderer::Anchor anchor,
        Range1     const &positions, 
        Range2     const &values)
    {
        auto &ax = (_axis[anchor] = cpt::AxisRenderer(anchor));
        ax.set_ticks(positions, values);
    }

} // namespace cpt

#endif