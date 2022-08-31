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
        update_ticks_labels();
    }

    void AxisRenderer::update_ticks_labels()
    {
        const float spacing = _config.tick_length + _config.spacing;
        const float sign = 
            (_anchor == Anchor::Down || _anchor == Anchor::Right) ? 
            +1.f : -1.f;
        const Label::Alignement alignement = 
            (_anchor == Anchor::Left || _anchor == Anchor::Down) ? 
            Label::Right : Label::Left;
        for (size_t i = 0; i != _ticks_labels.size(); ++i) {
            _ticks_labels[i].set_alignement(alignement);
            if (is_x_axis()) {
                _ticks_labels[i].set_rotation(-90.f);
            }
            float scaled_pos = _size * _ticks_positions[i];
            if (is_x_axis()) {
                _ticks_labels[i].set_position(
                    _pos.x + scaled_pos,
                    _pos.y + sign * spacing
                    );
            }
            else {
                _ticks_labels[i].set_position(
                    _pos.x + sign * spacing,
                    _pos.y + scaled_pos
                    );
            }
        }
    }

    sf::FloatRect AxisRenderer::get_bounds() const
    {
        float line_width = 1.f;
        float length = _size;
        float rwidth = line_width / 2.f;
        float lwidth = line_width / 2.f + _config.tick_length + _config.spacing;
        float max_label_length = 0.f;
        for (const auto &label : _ticks_labels) {
            sf::Vector2f label_size = label.get_size();
            float label_length = (std::abs(label.get_rotation()) > 45.f) ?
                label_size.y : label_size.x;
            if (label_length > max_label_length) {
                max_label_length = label_length;
            }
        }
        lwidth += max_label_length;
        float total_width = lwidth + rwidth;
        switch (_anchor) {
            case Anchor::Left:
                return sf::FloatRect(_pos.x - lwidth, _pos.y, total_width, length);
            case Anchor::Right:
                return sf::FloatRect(_pos.x - rwidth, _pos.y, total_width, length);
            case Anchor::Up:
                return sf::FloatRect(_pos.x, _pos.y - lwidth, length, total_width);
            case Anchor::Down:
                return sf::FloatRect(_pos.x, _pos.y - rwidth, length, total_width);
            default:
                throw InvalidAnchorError(
                    "Anchor with value ", 
                    static_cast<int>(_anchor), 
                    " is unknown.");
        }
    }

    void AxisRenderer::set_font(sf::Font const &font)
    {
        for (auto &label : _ticks_labels) {
            label.set_font(font);
        }
    }

    void AxisRenderer::draw(sf::RenderTarget &target) const
    {
        draw_ticks(target);
        draw_witness_line(target);
        draw_labels(target);
    }

    void AxisRenderer::draw_ticks(
            sf::RenderTarget &target
            ) const 
    {
        const float displacement 
            = (_anchor == Anchor::Left || _anchor == Anchor::Up) ? -1.f: 0.f;
        sf::RectangleShape tick({_config.tick_length, _config.tick_width});
        tick.setFillColor(sf::Color::Black);
        tick.rotate(90.f * static_cast<float>(is_x_axis()));
        for (std::size_t i = 0; i != _ticks_positions.size(); ++i) {
            float x_rel, y_rel;
            float pos = _ticks_positions[i] * _size;
            if (is_x_axis()) {
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
    }

    void AxisRenderer::draw_witness_line(
            sf::RenderTarget &target
            ) const
    {
        sf::RectangleShape witness({_size, 1.f});
        witness.setFillColor(sf::Color::Black);
        witness.rotate(90.f * static_cast<float>(!is_x_axis()));
        witness.setPosition({
            _pos.x,
            _pos.y
        });
        target.draw(witness);
    }

    void AxisRenderer::draw_labels(
            sf::RenderTarget &target
        ) const
    {
        for (size_t i = 0; i != _ticks_labels.size(); ++i) {
            _ticks_labels[i].draw(target);
        }
    }

} // namespace cpt
