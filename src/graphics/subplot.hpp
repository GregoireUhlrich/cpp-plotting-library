#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "axis.hpp"
#include "drawable.hpp"
#include "pad.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <array>

namespace cpt {

class SubPlot : public Drawable {
  private:
    Pad                 pad;
    std::array<Axis, 2> axis;
    sf::CircleShape     circle;

    void init() override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  public:
    SubPlot();
    SubPlot(Pad &pad);
    virtual ~SubPlot();
};

void SubPlot::init()
{
    for (size_t d = 0; d != axis.size(); ++d) {
        axis[d] = Axis(Coordinate(d));
    }
    circle.setRadius(110.0f);
    circle.setPosition(sf::Vector2f(200, 150));
    circle.setFillColor(sf::Color::Green);
}

SubPlot::SubPlot()
{
    init();
}

SubPlot::SubPlot(Pad &pad) : pad(pad)
{
    init();
}

SubPlot::~SubPlot()
{
}

void SubPlot::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(pad, states);
    for (const Axis &a : axis) {
        target.draw(a, states);
    }
    target.draw(circle, states);
}

} // namespace cpt

#endif // CIRCLE_HPP
