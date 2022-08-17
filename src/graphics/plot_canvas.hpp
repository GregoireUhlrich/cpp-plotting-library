#ifndef CPT_PLOT_CANVAS_H_INCLUDED
#define CPT_PLOT_CANVAS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <numeric>
#include "../plots/line_plot.hpp"

namespace cpt
{
    class PlotCanvas {
    public:

        void create(
            unsigned int width,
            unsigned int height);

        Extent<float> get_extent() const noexcept {
            return _extent;
        }

        void set_extent(Extent<float> extent) noexcept {
            _extent = std::move(extent);
        }

        void clear(sf::Color color = sf::Color::White);

        void plot(cpt::LinePlot const &line) noexcept;

        void display();

        sf::Sprite const &get_sprite() const { 
            return _sprite;
        }

    protected:
        void draw_outline();

    private:
        sf::RenderTexture _texture;
        sf::Texture       _final_texture;
        sf::Sprite        _sprite;
        Extent<float>     _extent;
    };

} // namespace cpt


#endif
