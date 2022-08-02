#ifndef PAD_HPP
#define PAD_HPP

#include "drawable.hpp"
#include "esthetic.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace graphic {

class Pad : public Drawable {
  private:
    sf::RectangleShape rectangle;

    int width;
    int height;

    int border;

    void init() override;

  public:
    Pad();
    Pad(int width, int height, int border);
    virtual ~Pad();

    sf::RectangleShape &area()
    {
        return rectangle;
    }

    void draw(sf::RenderTarget &target) override;
};

void Pad::init()
{
    rectangle.setPosition(float(border), float(border));
    rectangle.setSize(
        sf::Vector2f(float(width - 2 * border), float(height - 2 * border)));
    rectangle.setOutlineThickness(float(border));

    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Transparent);
}

Pad::Pad() : width(GLOBAL_WIDTH), height(GLOBAL_HEIGHT), border(PAD_SHIFT)
{
    init();
}

Pad::Pad(int width, int height, int border)
    : width(width), height(height), border(border)
{
    init();
}

Pad::~Pad()
{
}

void Pad::draw(sf::RenderTarget &target)
{
    target.draw(rectangle);
}

} // namespace graphic

#endif // PAD_HPP
