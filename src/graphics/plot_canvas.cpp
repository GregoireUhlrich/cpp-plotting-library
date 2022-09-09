#include "plot_canvas.hpp"
#include "fonts.hpp"
#include "label.hpp"
#include <numbers>

namespace cpt {
void PlotCanvas::create(unsigned int width, unsigned int height)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel
        = sf::RenderTexture::getMaximumAntialiasingLevel();
    _texture.create(width, height, settings);
}

void PlotCanvas::clear(sf::Color color)
{
    _texture.clear(color);
}

///////////////////
// Plot
///////////////////
void PlotCanvas::plot(cpt::LinePlot const &line) noexcept
{
    const sf::Vector2f target_size
        = {static_cast<float>(_texture.getSize().x),
           static_cast<float>(_texture.getSize().y)};
    const auto &x              = line.x();
    const auto &y              = line.y();
    const float lx             = _extent.xmax - _extent.xmin;
    const float ly             = _extent.ymax - _extent.ymin;
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
        point.setPosition(xi, target_size.y - yi);
        _texture.draw(point);
        if (i > 0) {
            const float        dist  = std::sqrt(std::pow(xi - x_prev, 2.f)
                                         + std::pow(yi - y_prev, 2.f));
            const float        angle = std::atan2(-yi + y_prev, xi - x_prev);
            sf::RectangleShape rect({dist, line.config.line_width});
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
        marker.setPosition(xi, target_size.y - yi);
        _texture.draw(marker);
    }

    draw_outline();
}

///////////////////
// Histogram
///////////////////
void PlotCanvas::plot(cpt::Histogram const &histo) noexcept
{

    /////////////////////////////////////////////////////////////////////
    const sf::Vector2f target_size
        = {static_cast<float>(_texture.getSize().x),
           static_cast<float>(_texture.getSize().y)};
    const auto &x              = histo.x();
    const auto &y              = histo.y();
    const float lx             = _extent.xmax - _extent.xmin;
    const float ly             = _extent.ymax - _extent.ymin;
    const float x_aspect_ratio = std::abs(target_size.x / lx);
    const float y_aspect_ratio = std::abs(target_size.y / ly);

    float bin_width = 0;
    if (histo.design.compact_bin) {
        bin_width = float(x.back() - x.front()) / float(x.size() - 1);
    }
    else {
        bin_width = float(x.back() - x.front()) / float(x.size());
    }
    /////////////////////////////////////////////////////////////////////

    // draw the histo first
    sf::RectangleShape bin_value;
    sf::RectangleShape bin_value_inner;
    bin_value.setFillColor(histo.design.bin_color);
    bin_value_inner.setFillColor(histo.design.bin_inner_color);
    for (std::size_t i = 0; i != x.size(); ++i) {
        const float xi = ((x[i] - _extent.xmin) * x_aspect_ratio);
        const float yi = ((y[i] - _extent.ymin) * y_aspect_ratio);
        bin_value.setSize(
            sf::Vector2f(bin_width * x_aspect_ratio, y[i] * y_aspect_ratio));
        bin_value.setPosition(xi - bin_value.getSize().x / 2.f,
                              target_size.y - yi);
        _texture.draw(bin_value);

        if (!histo.design.full_bin) {
            bin_value_inner.setSize(sf::Vector2f(
                bin_width * x_aspect_ratio - histo.design.border_size,
                y[i] * y_aspect_ratio - histo.design.border_size));
            bin_value_inner.setPosition(xi - bin_value.getSize().x / 2.f
                                            + histo.design.border_size / 2.f,
                                        target_size.y - yi
                                            + histo.design.border_size / 2.f);
            _texture.draw(bin_value_inner);
        }
    }

    // Uncertainty
    if (histo.has_yerr()) {
        const auto        &y_err_plus  = histo.yerr();
        const auto        &y_err_minus = histo.yerr(true);
        sf::RectangleShape bin_error;
        sf::RectangleShape bin_error_outline_up, bin_error_outline_down;
        bin_error.setFillColor(histo.design.error_bar_color);
        bin_error_outline_up.setFillColor(histo.design.error_outline_color);
        bin_error_outline_down.setFillColor(histo.design.error_outline_color);

        for (std::size_t i = 0; i != x.size(); ++i) {
            const float xi = ((x[i] - _extent.xmin) * x_aspect_ratio);
            const float yepi
                = ((y[i] + y_err_plus[i] - _extent.ymin) * y_aspect_ratio);
            const float yemi
                = ((y[i] + y_err_minus[i] - _extent.ymin) * y_aspect_ratio);

            bin_error.setSize(
                sf::Vector2f(histo.design.error_bar_size, yepi - yemi));
            bin_error_outline_up.setSize(sf::Vector2f(
                histo.design.error_outline_size, histo.design.error_bar_size));
            bin_error_outline_down.setSize(sf::Vector2f(
                histo.design.error_outline_size, histo.design.error_bar_size));

            bin_error.setPosition(xi - histo.design.error_bar_size / 2.f,
                                  target_size.y - yepi);
            bin_error_outline_up.setPosition(
                xi - histo.design.error_outline_size / 2.f,
                target_size.y - yepi - histo.design.error_bar_size);
            bin_error_outline_down.setPosition(
                xi - histo.design.error_outline_size / 2.f,
                target_size.y - yemi - histo.design.error_bar_size);

            _texture.draw(bin_error);
            _texture.draw(bin_error_outline_up);
            _texture.draw(bin_error_outline_down);
        }
    }

    // markers on top
    sf::CircleShape marker(histo.design.marker_size,
                           histo.design.marker_shape);
    marker.setFillColor(histo.design.marker_color);
    for (std::size_t i = 0; i != x.size(); ++i) {
        const float xi = ((x[i] - _extent.xmin) * x_aspect_ratio);
        const float yi = ((y[i] - _extent.ymin) * y_aspect_ratio);
        marker.setPosition(xi - histo.design.marker_size,
                           target_size.y - yi - histo.design.marker_size);
        _texture.draw(marker);
    }

    draw_outline();
}

void PlotCanvas::draw_outline()
{
    constexpr static unsigned int outline_thickness = 1;
    sf::RectangleShape            outline(
        {static_cast<float>(_texture.getSize().x - 2 * outline_thickness),
                    static_cast<float>(_texture.getSize().y - 2 * outline_thickness)});
    outline.setPosition({static_cast<float>(outline_thickness),
                         static_cast<float>(outline_thickness)});
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
