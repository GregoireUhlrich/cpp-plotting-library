#ifndef AXIS_HPP
#define AXIS_HPP

#include "drawable.hpp"
#include "esthetic.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace graphic {

class Axis : public Drawable {

  private:
    sf::RectangleShape line;

    int length;
    int thickness;

    int position_x;
    int position_y;

    void create() override;

  public:
    Axis();
    Axis(int length, int thickness);
    ~Axis();

    void draw(sf::RenderTarget &target) override;
};

void Axis::create()
{
    line.setFillColor(sf::Color::Black);
    line.setSize(sf::Vector2f(float(length), float(thickness)));
    line.setPosition(sf::Vector2f(float(position_x), float(position_y)));
}

Axis::Axis()
    : length(GLOBAL_WIDTH - 2 * (PAD_SHIFT + AXIS_SHIFT)),
      thickness(AXIS_THICKNESS),
      position_x(PAD_SHIFT + AXIS_SHIFT),
      position_y(GLOBAL_HEIGHT - PAD_SHIFT - AXIS_SHIFT - AXIS_THICKNESS)
{
    create();
}

Axis::Axis(int length, int thickness)
    : length(length), thickness(thickness), position_x(0), position_y(0)
{
    create();
}

Axis::~Axis()
{
}

void Axis::draw(sf::RenderTarget &target)
{
    target.draw(line);
}

} // namespace graphic

#endif // AXIS_HPP
