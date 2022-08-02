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

    float        size_arrow;
    sf::Vector2f size_line;
    sf::Vector2f position_line;
    sf::Vector2f position_arrow;
    int          orientation;

    void fill_variables(Coordinate c);
    void init() override;

  public:
    Axis();
    Axis(Coordinate coordinate);
    ~Axis();

    void draw(sf::RenderTarget &target) override;
};

void Axis::fill_variables(Coordinate c)
{
    size_arrow = 7;
    if (c == Coordinate::x) {
        size_line.x = GLOBAL_WIDTH - 2 * (PAD_SHIFT + AXIS_SHIFT) - AXIS_SPACE;
        size_line.y = AXIS_THICKNESS;
        position_line.x = PAD_SHIFT + AXIS_SHIFT;
        position_line.y = GLOBAL_HEIGHT - PAD_SHIFT - AXIS_SHIFT
                          - AXIS_THICKNESS - BASE_SHIFT;
        position_arrow.x
            = GLOBAL_WIDTH - PAD_SHIFT - AXIS_SHIFT - AXIS_SPACE + size_arrow;
        position_arrow.y = position_line.y - size_line.y - size_arrow / 2 - 1;
        orientation      = 90;
    }
    else if (c == Coordinate::y) {
        size_line.x = AXIS_THICKNESS;
        size_line.y
            = GLOBAL_HEIGHT - 2 * (PAD_SHIFT + AXIS_SHIFT) - AXIS_SPACE;
        position_line.x  = PAD_SHIFT + AXIS_SHIFT + BASE_SHIFT;
        position_line.y  = PAD_SHIFT + AXIS_SHIFT + AXIS_SPACE;
        position_arrow.x = position_line.x - size_line.x - size_arrow / 2 - 1;
        position_arrow.y = position_line.y - size_arrow;
        orientation      = 0;
    }
}

void Axis::init()
{
    arrow = sf::CircleShape(size_arrow, 3);
    arrow.rotate(float(orientation));
    arrow.setFillColor(sf::Color::Black);
    arrow.setPosition(position_arrow);

    line.setFillColor(sf::Color::Black);
    line.setSize(size_line);
    line.setPosition(position_line);
}

Axis::Axis()
{
}

Axis::Axis(Coordinate variable)
{
    fill_variables(variable);
    init();
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
