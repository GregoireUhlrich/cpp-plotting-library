#ifndef CPT_STYLE_H_INCLUDED
#define CPT_STYLE_H_INCLUDED

#include <span>

namespace sf {
  class RenderTarget;
}

namespace cpt {

    template<std::floating_point T>
    struct Extent;

    class AbstractStyle {
        virtual void render_data_points(
            std::span<float>          x,
            std::span<float>          y,
            sf::RenderTarget         &target,
            cpt::Extent<float> const &target_extent
            ) const = 0;

        void apply_extent(
            cpt::Extent<float> const &extent,
            sf::Vector2f       const &target_size,
            float &x,
            float &y
        ) const;
    };

    struct LineStyleConfig {

    };

    class LineStyle: public AbstractStyle {
    public:
        LineStyle(LineStyleConfig const &config_ = {})
            :config(config_)
        {

        }

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
