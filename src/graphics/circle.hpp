#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "axis.hpp"
#include "drawable.hpp"
#include "pad.hpp"

#include <SFML/Graphics/CircleShape.hpp>

namespace graphic {

class Circle : public Drawable {
  private:
    Pad             pad;
    Axis            axis;
    sf::CircleShape circle;

    void create() override;

  public:
    Circle();
    Circle(Pad &pad);
    virtual ~Circle();

    void draw(sf::RenderTarget &target) override;
};

void Circle::create()
{
    circle.setRadius(110.0f);
    circle.setFillColor(sf::Color::Green);
}

Circle::Circle()
{
    create();
}

Circle::Circle(Pad &pad) : pad(pad)
{
    create();
}

Circle::~Circle()
{
}

void Circle::draw(sf::RenderTarget &target)
{
    pad.draw(target);
    axis.draw(target);
    target.draw(circle);
}

} // namespace graphic

#endif // CIRCLE_HPP
