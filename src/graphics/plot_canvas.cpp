#include "plot_canvas.hpp"
#include <numbers>
#include "label.hpp"
#include "fonts.hpp"

namespace cpt
{
    void PlotCanvas::create(
        unsigned int width,
        unsigned int height)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        _texture.create(width, height, settings);
    }

    void PlotCanvas::clear(sf::Color color)
    {
        _texture.clear(color);
    }

    void PlotCanvas::plot(
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

        // draw the line first
        sf::CircleShape point(line.config.line_width / 2.f);
        point.setFillColor(line.config.line_color);
        point.setOrigin(line.config.line_width / 2.f,
                        line.config.line_width / 2.f);
        float x_prev, y_prev;
        for (std::size_t i = 0; i != x.size(); ++i) {
            const float xi = ((x[i] - _extent.xmin) * x_aspect_ratio);
            const float yi = ((y[i] - _extent.ymin) * y_aspect_ratio);
            point.setPosition(
                xi, 
                target_size.y - yi
            );
            _texture.draw(point);  
            if (i > 0) {
                const float dist = std::sqrt(
                    std::pow(xi - x_prev, 2.f)
                    + std::pow(yi - y_prev, 2.f));
                const float angle = std::atan2(-yi + y_prev, xi - x_prev);
                sf::RectangleShape rect({
                    dist,
                    line.config.line_width});
                rect.setOrigin({0.f, line.config.line_width / 2.f});
                rect.setPosition(x_prev, target_size.y - y_prev);
                rect.setRotation(180.f * angle / std::numbers::pi_v<float>);
                rect.setFillColor(line.config.line_color);
                _texture.draw(rect);
            }
            x_prev = xi;
            y_prev = yi;
        }

        // markers on top
        sf::CircleShape marker(line.config.marker_size / 2.f);
        marker.setFillColor(line.config.marker_color);
        marker.setOrigin(line.config.marker_size / 2.f,
                         line.config.marker_size / 2.f);
        for (std::size_t i = 0; i != x.size(); ++i) {
            const float xi = ((x[i] - _extent.xmin) * x_aspect_ratio);
            const float yi = ((y[i] - _extent.ymin) * y_aspect_ratio);
            marker.setPosition(
                xi, 
                target_size.y - yi
            );
            _texture.draw(marker);
        }

        // Text labels
        cpt::Label label("Hello World!", cpt::font::arial.get_font(cpt::font::ItalicBold));
        label.set_position(10.f, 50.f);
        label.set_font_size(30);
        label.draw(_texture);

        draw_outline();
    }

    void PlotCanvas::draw_outline()
    {
        constexpr static unsigned int outline_thickness = 1;
        sf::RectangleShape outline({
            static_cast<float>(_texture.getSize().x - 2*outline_thickness),
            static_cast<float>(_texture.getSize().y - 2*outline_thickness)}
            );
        outline.setPosition({
            static_cast<float>(outline_thickness),
            static_cast<float>(outline_thickness)
        });
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineThickness(1);
        outline.setOutlineColor(sf::Color::Black);
        _texture.draw(outline);
    }

    void PlotCanvas::display()
    {
        _sprite = sf::Sprite(); 
        _texture.display();
        _final_texture = _texture.getTexture();
        _sprite.setTexture(_final_texture);
    }

} // namespace cpt
