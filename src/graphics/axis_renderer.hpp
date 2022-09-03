#ifndef CPT_AXIS_RENDERER_H_INCLUDED
#define CPT_AXIS_RENDERER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../math_views.hpp"
#include "../utils/direction.hpp"
#include "../utils/error.hpp"
#include "label.hpp"
#include "color.hpp"

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

    class InvalidAxisRendererError: public cpt::Exception {
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

        bool is_x_axis() const {
            return _anchor == Anchor::Top || _anchor == Anchor::Bottom;
        }

        sf::Vector2f get_position()  const noexcept { return _pos; }
        float        get_size()      const noexcept { return _size; }
        Anchor       get_anchor()    const noexcept { return _anchor; }

        sf::FloatRect const &get_bounds() const;

        void set_font(cpt::Font const &font);
        void set_config(AxisRendererConfig const &config);
        void set_position(float sx, float sy);
        void set_size(float size);
        void set_anchor(Anchor anchor);
        void set_ticks(
            std::vector<float>      ticks_positions,
            std::vector<cpt::Label> ticks_labels
            );

        void update();
        void draw(sf::RenderTarget &target) const;

    private:

        void acknowledge_change();
        void update_ticks_labels();
        void update_bounds();
        void assert_up_to_date() const;

        void draw_ticks(sf::RenderTarget &target) const;
        void draw_labels(sf::RenderTarget &target) const;

    private:
        bool _up_to_date = false;

        Anchor         _anchor;
        sf::Vector2f   _pos;
        float          _size;

        sf::FloatRect           _bounds;
        std::vector<float>      _ticks_positions;
        std::vector<cpt::Label> _ticks_labels;

        AxisRendererConfig _config;
    };

} // namespace cpt


#endif
