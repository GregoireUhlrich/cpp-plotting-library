#include "style.hpp"
#include "../utils/extent.hpp"
#include <SFML/Graphics.hpp>
#include <numbers>

namespace cpt {

    std::pair<float, float> AbstractStyle::apply_extent(
        float                     x,
        float                     y,
        sf::Vector2f       const &target_size,
        cpt::Extent<float> const &extent
        )
    {
        void apply = [](float x, float min, float max, float scale) -> float {
            return scale * (x - min) / (max - min);
        };
        x = apply(x, extent.xmin, extent.xmax, target_size.x);
        y = target_size.y - apply(y, extent.ymin, extent.ymax, target_size.y);
        return {x, y};
    }

    void LinePlot::render_data_points(
        std::span<float>          x,
        std::span<float>          y,
        sf::RenderTarget         &target,
        cpt::Extent<float> const &target_extent
        ) const override
    {
        const sf::Vector2f target_size
            = {static_cast<float>(_texture.getSize().x),
               static_cast<float>(_texture.getSize().y)};

        // draw the line first
        sf::CircleShape point(config.line_width / 2.f);
        point.setFillColor(config.line_color);
        point.setOrigin(config.line_width / 2.f,
                        config.line_width / 2.f);
        float x_prev, y_prev;
        for (std::size_t i = 0; i != x.size(); ++i) {
            auto [xi, yi] = apply_extent(x[i], y[i], target_size, target_extent);
            point.setPosition(xi, target_size.y - yi);
            target.draw(point);
            if (i > 0) {
                const float        dist  = std::sqrt(std::pow(xi - x_prev, 2.f)
                                             + std::pow(yi - y_prev, 2.f));
                const float        angle = std::atan2(-yi + y_prev, xi - x_prev);
                sf::RectangleShape rect({dist, config.line_width});
                rect.setOrigin({0.f, config.line_width / 2.f});
                rect.setPosition(x_prev, target_size.y - y_prev);
                rect.setRotation(180.f * angle / std::numbers::pi_v<float>);
                rect.setFillColor(config.line_color);
                target.draw(rect);
            }
            x_prev = xi;
            y_prev = yi;
        }

        // markers on top
        sf::CircleShape marker(config.marker_size / 2.f);
        marker.setFillColor(config.marker_color);
        marker.setOrigin(config.marker_size / 2.f,
                         config.marker_size / 2.f);
        for (std::size_t i = 0; i != x.size(); ++i) {
            auto [xi, yi] = apply_extent(x[i], y[i], target_size, target_extent);
            marker.setPosition(xi, target_size.y - yi);
            target.draw(marker);
        }
    }

} // namespace cpt
