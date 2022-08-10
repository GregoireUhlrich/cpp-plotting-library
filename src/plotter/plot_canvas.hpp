#ifndef CPT_PLOT_CANVAS_H_INCLUDED
#define CPT_PLOT_CANVAS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <numeric>
#include "line_plot.hpp"

namespace cpt
{
    struct PlotCanvasConfig {
        sf::Color background_color = sf::Color(186, 186, 186);
        float     offset_ratio = 0.1f;
    };

    class PlotCanvas {
    public:
        explicit
        PlotCanvas(
            unsigned int width,
            unsigned int height,
            PlotCanvasConfig const &config_ = {}) noexcept
            :config(config_)
        {
            sf::ContextSettings settings;
            settings.antialiasingLevel = 4;
            _texture.create(width, height, settings);
        }

        template<std::ranges::range Lines>
            requires std::same_as<cpt::LinePlot, std::ranges::range_value_t<Lines>>
        void plot(Lines const &lines)
        {
            _texture.clear(config.background_color);
            if (!std::ranges::empty(lines)) {
                auto extent = get_extent(lines);
                for (const auto &line : lines) {
                    plot(line, extent);
                }
            }
            _texture.display();
        }

        sf::Texture const &get_texture() const noexcept
        {
            return _texture.getTexture();
        }

    private:

        template<std::floating_point T>
        static void ensure_non_zero_extent(T &min, T &max) noexcept {
            if (max - min < std::numeric_limits<T>::min()) {
                min -= static_cast<T>(1.);
                max += static_cast<T>(1.);
            }
        }

        template<std::ranges::range Lines>
            requires std::same_as<cpt::LinePlot, std::ranges::range_value_t<Lines>>
        static cpt::Extent<float> get_extent(Lines const &lines) noexcept
        {
            auto iter = std::ranges::begin(lines);
            cpt::Extent<float> extent = (*iter++).extent();
            for (; iter != std::ranges::end(lines); ++iter) {
                extent = combine(extent, iter->extent());
            }
            ensure_non_zero_extent(extent.xmin, extent.xmax);
            ensure_non_zero_extent(extent.ymin, extent.ymax);
            return extent;
        }

        void plot(
            cpt::LinePlot const &line, 
            Extent<float> const &extent) noexcept 
        {
            const sf::Vector2f target_size = {
                static_cast<float>(_texture.getSize().x), 
                static_cast<float>(_texture.getSize().y)
            };
            const auto &x = line.x();
            const auto &y = line.y();
            const float lx = extent.xmax - extent.xmin;
            const float ly = extent.ymax - extent.ymin;
            const float offset_x = target_size.x * config.offset_ratio;
            const float offset_y = target_size.y * config.offset_ratio;
            const float x_aspect_ratio = std::abs((1 - 2*config.offset_ratio)*target_size.x / lx);
            const float y_aspect_ratio = std::abs((1 - 2*config.offset_ratio)*target_size.y / ly);

            for (std::size_t i = 0; i != x.size(); ++i) {
                sf::CircleShape circle(line.config.marker_size);
                circle.setFillColor(line.config.marker_color);
                const float xi = ((x[i] - extent.xmin) * x_aspect_ratio) + offset_x;
                const float yi = ((y[i] - extent.ymin) * y_aspect_ratio) + offset_y;
                circle.setPosition(
                    xi - line.config.marker_size/2.f, 
                    target_size.y - (yi - line.config.marker_size/2.f)
                );
                _texture.draw(circle);
            }
        }

    public:
        PlotCanvasConfig config;

    private:
        sf::RenderTexture _texture;
    };

} // namespace cpt


#endif
