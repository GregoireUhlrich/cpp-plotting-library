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

    void fill_variables(Coordinate c);
    void create() override;

  public:
    Axis();
    Axis(Coordinate coordinate);
    ~Axis();

    void draw(sf::RenderTarget &target) override;
};

void Axis::fill_variables(Coordinate c)
{
    if (c == Coordinate::x) {
        length     = GLOBAL_WIDTH - 2 * (PAD_SHIFT + AXIS_SHIFT) - AXIS_SPACE;
        thickness  = AXIS_THICKNESS;
        position_x = PAD_SHIFT + AXIS_SHIFT;
        position_y = GLOBAL_HEIGHT - PAD_SHIFT - AXIS_SHIFT - AXIS_THICKNESS
                     - BASE_SHIFT;
    }
    else if (c == Coordinate::y) {
        length     = AXIS_THICKNESS;
        thickness  = GLOBAL_HEIGHT - 2 * (PAD_SHIFT + AXIS_SHIFT) - AXIS_SPACE;
        position_x = PAD_SHIFT + AXIS_SHIFT + BASE_SHIFT;
        position_y = PAD_SHIFT + AXIS_SHIFT + AXIS_SPACE;
    }
}

void Axis::create()
{
    line.setFillColor(sf::Color::Black);
    line.setSize(sf::Vector2f(float(length), float(thickness)));
    line.setPosition(sf::Vector2f(float(position_x), float(position_y)));
}

Axis::Axis()
{
}

Axis::Axis(Coordinate variable)
{
    fill_variables(variable);
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
