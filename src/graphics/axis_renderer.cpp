#include "axis_renderer.hpp"

namespace cpt
{
    AxisRenderer::AxisRenderer(
        Anchor                    anchor, 
        float                     size,
        AxisRendererConfig const &config)
        : _anchor(anchor),
          _size(size),
          _config(config)
    {

    }

    void AxisRenderer::set_ticks(
        std::vector<float>      ticks_position,
        std::vector<cpt::Label> ticks_labels
        )
    {
        if (_ticks_positions.size() != _ticks_labels.size()) {
            throw InvalidTicksError(
                "There should the same number of ticks' positions and labels,",
                " found ", ticks_position.size(), " and ", ticks_labels.size(),
                " respectively."
            );
        }
        for (float f : ticks_position) {
            if (f < 0.f || f > 1.f) {
                throw InvalidTicksError(
                    "Tick positions should be floating-point numbers "
                    "between 0. and 1. (relative postion)."
                );
            }
        }
        _ticks_positions = std::move(ticks_position);
        _ticks_labels    = std::move(ticks_labels);
    }

    void AxisRenderer::draw(sf::RenderTarget &target) const 
    {
        const bool is_x_axis = (_anchor == Anchor::Down || _anchor == Anchor::Up);
        const float displacement 
            = (_anchor == Anchor::Left || _anchor == Anchor::Up) ? -1.f: 0.f;
        sf::RectangleShape tick({_config.tick_length, _config.tick_width});
        tick.setFillColor(sf::Color::Black);
        tick.rotate(90.f * static_cast<float>(is_x_axis));
        for (std::size_t i = 0; i != _ticks_positions.size(); ++i) {
            float x_rel, y_rel;
            float pos = _ticks_positions[i] * _size;
            if (is_x_axis) {
                x_rel = pos + _config.tick_width / 2.f;
                y_rel = _config.tick_length * displacement;
            }
            else {
                x_rel = _config.tick_length * displacement;
                y_rel = pos - _config.tick_width / 2.f;
            }
            tick.setPosition(_pos.x + x_rel, _pos.y + y_rel);
            target.draw(tick);
        }
        sf::RectangleShape witness({_size, 1.f});
        witness.setFillColor(sf::Color::Black);
        witness.rotate(90.f * static_cast<float>(!is_x_axis));
        witness.setPosition({
            _pos.x,
            _pos.y
        });
        target.draw(witness);
    }

} // namespace cpt
