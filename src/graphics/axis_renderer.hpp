#ifndef CPT_AXIS_H_INCLUDED
#define CPT_AXIS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../math_views.hpp"
#include "../utils/direction.hpp"
#include "../utils/error.hpp"
#include "label.hpp"

namespace cpt
{
    struct AxisRendererConfig {
        float spacing     = 5.f;
        float tick_width  = 3.f;
        float tick_length = 7.f;
    };

    class InvalidTicksError: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    class AxisRenderer {

    public:
        AxisRenderer() = default;

        AxisRenderer(
            cpt::Anchor               anchor, 
            float                     size,
            AxisRendererConfig const &config = {});

        AxisRendererConfig get_config() const noexcept {
            return _config;
        }

        void set_config(AxisRendererConfig const &config) noexcept {
            _config = config;
        }

        sf::Vector2f get_position()  const noexcept { return _pos; }
        float        get_size()      const noexcept { return _size; }
        Anchor       get_anchor()    const noexcept { return _anchor; }

        void set_position(float sx, float sy) noexcept { _pos = {sx, sy}; }
        void set_size(float size)             noexcept { _size = size; } 
        void set_anchor(Anchor anchor)        noexcept { _anchor = anchor; }

        bool is_x_axis() const {
            return _anchor == Anchor::Up || _anchor == Anchor::Down;
        }

        void set_ticks(
            std::vector<float>      ticks_positions,
            std::vector<cpt::Label> ticks_labels
            );

        void draw(sf::RenderTarget &target) const;

    private:

        void update_ticks_labels();

        void draw_ticks(sf::RenderTarget &target) const;
        void draw_witness_line(sf::RenderTarget &target) const;
        void draw_labels(sf::RenderTarget &target) const;

    private:
        Anchor         _anchor;
        sf::Vector2f   _pos;
        float          _size;
        std::vector<float>      _ticks_positions;
        std::vector<cpt::Label> _ticks_labels;
        AxisRendererConfig      _config;
    };
} // namespace cpt


#endif
