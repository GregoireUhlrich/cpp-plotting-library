#ifndef CPT_PLOT_CANVAS_H_INCLUDED
#define CPT_PLOT_CANVAS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <numeric>
#include "line_plot.hpp"

namespace cpt
{
    class PlotCanvas {
    public:

        void create(
            unsigned int width,
            unsigned int height)
        {
            sf::ContextSettings settings;
            settings.antialiasingLevel = 4;
            _texture.create(width, height, settings);
        }

        Extent<float> get_extent() const noexcept {
            return _extent;
        }

        void set_extent(Extent<float> extent) noexcept {
            _extent = std::move(extent);
        }

        void clear(sf::Color color = sf::Color::White)
        {
            _texture.clear(color);
        }

        void plot(
            cpt::LinePlot const &line) noexcept 
        {
            const sf::Vector2f target_size = {
                static_cast<float>(_texture.getSize().x), 
                static_cast<float>(_texture.getSize().y)
            };
            const auto &x = line.x();
            const auto &y = line.y();
            const float lx = _extent.xmax - _extent.xmin;
            const float ly = _extent.ymax - _extent.ymin;
            const float x_aspect_ratio = std::abs(target_size.x / lx);
            const float y_aspect_ratio = std::abs(target_size.y / ly);

            for (std::size_t i = 0; i != x.size(); ++i) {
                sf::CircleShape circle(line.config.marker_size);
                circle.setFillColor(line.config.marker_color);
                const float xi = ((x[i] - _extent.xmin) * x_aspect_ratio);
                const float yi = ((y[i] - _extent.ymin) * y_aspect_ratio);
                circle.setPosition(
                    xi - line.config.marker_size/2.f, 
                    target_size.y - (yi - line.config.marker_size/2.f)
                );
                _texture.draw(circle);
            }
        }

        void display()
        {
            _sprite = sf::Sprite();
            _texture.display();
            _final_texture = _texture.getTexture();
            _sprite.setTexture(_final_texture);
        }

        sf::Sprite const &get_sprite() const { 
            return _sprite;
        }

    private:
        sf::RenderTexture _texture;
        sf::Texture       _final_texture;
        sf::Sprite        _sprite;
        Extent<float>     _extent;
    };

} // namespace cpt


#endif
