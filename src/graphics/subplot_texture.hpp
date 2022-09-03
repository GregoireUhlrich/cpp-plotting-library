#ifndef CPT_SUBPLOT_TEXTURE_H_INCLUDED
#define CPT_SUBPLOT_TEXTURE_H_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>
#include "plot_canvas.hpp"
#include "axis_renderer.hpp"
#include "color.hpp"
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

        cpt::Font const &get_font() const;
        sf::Vector2f get_position() const noexcept;
        sf::Vector2f get_size() const noexcept;

        sf::Sprite const &get_sprite() const noexcept {
            return _sprite;
        }

        void set_position(float x, float y) noexcept;
        void set_size(float sx, float sy);

        void set_font(cpt::Font const &font); 
        void set_ticks(
            cpt::Anchor             anchor,
            std::vector<float>      positions, 
            std::vector<cpt::Label> labels);
        
        void update();
        void display();
       
    private:
        void update_axis();
        void update_canvas_bounds();
        void update_textures();

        void acknowledge_change();
        void assert_up_to_date() const;
    
    protected:
        bool _up_to_date = false;

        sf::Vector2f _pos;
        sf::Vector2f _size;
        cpt::Font           const *_font = nullptr;
        sf::RenderTexture _texture;
        sf::Texture       _final_texture;
        sf::Sprite        _sprite;
        std::map<cpt::Anchor, cpt::AxisRenderer> _axis;

        sf::IntRect _canvas_bounds;
        PlotCanvas  _canvas;
    };

} // namespace cpt

#endif
