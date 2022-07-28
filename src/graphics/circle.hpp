#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "axis.hpp"
#include "drawable.hpp"
#include "pad.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <array>

namespace graphic {

class Circle : public Drawable {
  private:
    Pad                 pad;
    std::array<Axis, 2> axis;
    sf::CircleShape     circle;

    void create() override;

  public:
    Circle();
    Circle(Pad &pad);
    virtual ~Circle();

    void draw(sf::RenderTarget &target) override;
};

void Circle::create()
{
    for (size_t d = 0; d != axis.size(); ++d) {
        axis[d] = Axis(Coordinate(d));
    }
    circle.setRadius(110.0f);
    circle.setPosition(sf::Vector2f(200, 150));
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
    for (Axis &a : axis) {
        a.draw(target);
    }
    target.draw(circle);
}

} // namespace graphic

#endif // CIRCLE_HPP
