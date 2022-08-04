#ifndef CPT_PLOTLINE_H_INCLUDED
#define CPT_PLOTLINE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <span>

namespace cpt
{
    class PlotLine: public sf::Drawable {

    public:

        template<class T>
        void load_data(
            std::span<T> const &x,
            std::span<T> const &y);

        void draw(sf::RenderTarget &target, sf::RenderStates) const override;
        
    private:
        std::vector<sf::RectangleShape> lines;
        std::vector<sf::CircleShape> markers;
    };

    template<class T>
    void PlotLine::load_data(
        std::span<T> const &x,
        std::span<T> const &y)
    {
        if (x.size() != y.size())
            
        if (x.empty())
            return;
    }

    void PlotLine::draw(sf::RenderTarget &target, sf::RenderStates) const
    {
        for (const auto &line : lines)
            target.draw(line);
        for (const auto &marker : markers)
            target.draw(marker);
    }

} // namespace cpt


#endif