#ifndef CPT_PLOTLINE_H_INCLUDED
#define CPT_PLOTLINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <span>
#include "linedata.hpp"

namespace cpt
{
    struct PlotLineConfig {
        float markersize = 5;
        int linewidth  = 1;
    };

    class PlotLine: public sf::Drawable {

    public:

        explicit
        PlotLine(PlotLineConfig config = {}) noexcept
            :config(std::move(config))
        {}

        template<class T, class U>
        explicit
        PlotLine(LineData<T, U> const &line, PlotLineConfig config = {}) noexcept
            :config(std::move(config))
        {
            load_data(line);
        }

        template<class T, class U>
        void load_data(LineData<T, U> const &data);

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    public:
        PlotLineConfig config;

    private:
        std::vector<sf::RectangleShape> lines;
        std::vector<sf::CircleShape> markers;
    };

    template<class T, class U>
    void PlotLine::load_data(LineData<T, U> const &data)
    {
        if (data.empty()) {
            return;
        }
        const std::size_t n_markers = data.size();
        // const std::size_t n_lines   = n_markers - 1; 
        markers = std::vector<sf::CircleShape>(n_markers);
        for (std::size_t i = 0; i != n_markers; ++i) {
            markers[i].setRadius(config.markersize);
            markers[i].setPosition(sf::Vector2f(
                static_cast<float>(data.x()[i]), 
                static_cast<float>(data.y()[i]))
                );
            markers[i].setFillColor(sf::Color::Blue);
        }
    }

    void PlotLine::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (const auto &line : lines)
            target.draw(line, states);
        for (const auto &marker : markers)
            target.draw(marker, states);
    }

} // namespace cpt


#endif