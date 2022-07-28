#ifndef AXIS_HPP
#define AXIS_HPP

#include "drawable.hpp"
#include "esthetic.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace graphic {

class Axis : public Drawable {

  private:
    sf::RectangleShape line;
    sf::CircleShape    arrow;

    int length;
    int thickness;
    int arrow_size;

    int position_x;
    int position_y;
    int position_ax;
    int position_ay;
    int orientation;

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
    arrow_size = 7;
    if (c == Coordinate::x) {
        length     = GLOBAL_WIDTH - 2 * (PAD_SHIFT + AXIS_SHIFT) - AXIS_SPACE;
        thickness  = AXIS_THICKNESS;
        position_x = PAD_SHIFT + AXIS_SHIFT;
        position_y = GLOBAL_HEIGHT - PAD_SHIFT - AXIS_SHIFT - AXIS_THICKNESS
                     - BASE_SHIFT;
        position_ax
            = GLOBAL_WIDTH - PAD_SHIFT - AXIS_SHIFT - AXIS_SPACE + arrow_size;
        position_ay = position_y - thickness - arrow_size / 2 - 1;
        orientation = 90;
    }
    else if (c == Coordinate::y) {
        length     = AXIS_THICKNESS;
        thickness  = GLOBAL_HEIGHT - 2 * (PAD_SHIFT + AXIS_SHIFT) - AXIS_SPACE;
        position_x = PAD_SHIFT + AXIS_SHIFT + BASE_SHIFT;
        position_y = PAD_SHIFT + AXIS_SHIFT + AXIS_SPACE;
        position_ax = position_x - length - arrow_size / 2 - 1;
        position_ay = position_y - arrow_size;
        orientation = 0;
    }
}

void Axis::create()
{
    arrow = sf::CircleShape(float(arrow_size), 3);
    arrow.rotate(float(orientation));
    arrow.setFillColor(sf::Color::Black);
    arrow.setPosition(sf::Vector2f(float(position_ax), float(position_ay)));

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
    target.draw(arrow);
}

} // namespace graphic

#endif // AXIS_HPP
