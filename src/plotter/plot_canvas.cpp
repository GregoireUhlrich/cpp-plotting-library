#include "plot_canvas.hpp"

namespace cpt
{
    void PlotCanvas::create(
        unsigned int width,
        unsigned int height)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 4;
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
