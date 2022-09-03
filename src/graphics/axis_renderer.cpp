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

    sf::FloatRect const &AxisRenderer::get_bounds() const 
    {
        assert_up_to_date();
        return _bounds;
    }
    
    void AxisRenderer::set_font(cpt::Font const &font)
    {
        for (auto &label : _ticks_labels) {
            label.set_font(font);
        }
        acknowledge_change();
    }

    void AxisRenderer::set_position(float x, float y)
    {
        _pos = {x, y};
        acknowledge_change();
    }

    void AxisRenderer::set_size(float size)
    {
        _size = size;
        acknowledge_change();
    }

    void AxisRenderer::set_anchor(Anchor anchor)
    {
        _anchor = anchor;
        acknowledge_change();
    }
    
    void AxisRenderer::set_config(AxisRendererConfig const &config)
    {
        _config = config;
        acknowledge_change();
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

    void AxisRenderer::acknowledge_change()
    {
        _up_to_date = false;
    }

    void AxisRenderer::update()
    {
        if (!_up_to_date) {
            update_ticks_labels();
            update_bounds();
            _up_to_date = true;
        }
    }

    void AxisRenderer::update_ticks_labels()
    {
        const float spacing = _config.tick_length + _config.spacing;
        const float sign = 
            (_anchor == Anchor::Bottom || _anchor == Anchor::Right) ? 
            +1.f : -1.f;
        Label::Alignement alignement;
        switch (_anchor) {
            case Anchor::Left: 
                alignement = Label::Right;
                break;
            case Anchor::Right: 
                alignement = Label::Left;
                break;
            case Anchor::Top: 
                alignement = Label::Bottom;
                break;
            case Anchor::Bottom: 
                alignement = Label::Top;
                break;
            default:
                throw InvalidAnchorError(
                    "Anchor of value ", static_cast<int>(_anchor),
                    " is unknown."
                );
        }
        for (size_t i = 0; i != _ticks_labels.size(); ++i) {
            _ticks_labels[i].set_alignement(alignement);
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

    void AxisRenderer::update_bounds()
    {
        float line_width = 1.f;
        float length = _size;
        float rwidth = line_width / 2.f;
        float lwidth = line_width / 2.f + _config.tick_length + _config.spacing;
        float max_label_length = 0.f;
        for (const auto &label : _ticks_labels) {
            sf::Vector2f label_size = label.get_graphics_size();
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
                _bounds = sf::FloatRect(_pos.x - lwidth, _pos.y, total_width, length);
                break;
            case Anchor::Right:
                _bounds = sf::FloatRect(_pos.x - rwidth, _pos.y, total_width, length);
                break;
            case Anchor::Top:
                _bounds = sf::FloatRect(_pos.x, _pos.y - lwidth, length, total_width);
                break;
            case Anchor::Bottom:
                _bounds = sf::FloatRect(_pos.x, _pos.y - rwidth, length, total_width);
                break;
            default:
                throw InvalidAnchorError(
                    "Anchor with value ", 
                    static_cast<int>(_anchor), 
                    " is unknown.");
        }
    }

    void AxisRenderer::assert_up_to_date() const 
    {
        if (!_up_to_date) {
            throw InvalidAxisRendererError(
                "Invalid use of a modified AxisRenderer.",
                "Please call .update() before."
            );
        }
    }

    void AxisRenderer::draw(sf::RenderTarget &target) const
    {
        assert_up_to_date();
        draw_ticks(target);
        draw_labels(target);
    }

    void AxisRenderer::draw_ticks(
            sf::RenderTarget &target
            ) const 
    {
        const float displacement 
            = (_anchor == Anchor::Left || _anchor == Anchor::Top) ? -1.f: 0.f;
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

    void AxisRenderer::draw_labels(
            sf::RenderTarget &target
        ) const
    {
        const bool horizontal = is_x_axis();
        auto get = [&](sf::Vector2f vec) {
            return horizontal ? vec.x : vec.y;
        };
        auto label_in_box = [&](Label const &label) {
            float pos_label  = get(label.get_position()) - get(_pos);
            float size_label = get(label.get_graphics_size());
            float mini = pos_label - size_label / 2.f;
            float maxi = pos_label + size_label / 2.f;
            return mini >= 0.f && maxi <= _size;
        };
        for (auto const &label : _ticks_labels) {
            if (label_in_box(label)) {
                label.draw(target);
            }
        }
    }

} // namespace cpt
