#ifndef CPT_STYLE_H_INCLUDED
#define CPT_STYLE_H_INCLUDED

#include <span>
#include "color.hpp"

namespace cpt {

    template<std::floating_point T>
    struct Extent;

    class AbstractStyle {

    public:
        virtual 
        void render_data_points(
            std::span<float>          x,
            std::span<float>          y,
            sf::RenderTarget         &target,
            cpt::Extent<float> const &target_extent
            ) const = 0;

        std::pair<float, float> apply_extent(
            float                     x,
            float                     y,
            sf::Vector2f       const &target_size,
            cpt::Extent<float> const &extent,
        ) const;
    };

    struct LineStyleConfig {
        float      marker_size  = 3.5f;
        cpt::Color marker_color = cpt::Color(0, 64, 128);
        float      line_width   = 2.f;
        cpt::Color line_color   = cpt::Color(0, 64, 128);
    };

    class LineStyle: public AbstractStyle {
    public:
        LineStyle(LineStyleConfig const &config_ = {})
            :config(config_)
        {

        }

        virtual 
        void render_data_points(
            std::span<float>          x,
            std::span<float>          y,
            sf::RenderTarget         &target,
            cpt::Extent<float> const &target_extent
            ) const override;

        LineStyleConfig config;
    };
} // namespace cpt

#endif
