#ifndef PAD_HPP
#define PAD_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace graphic {

class Pad {
  private:
    sf::RectangleShape rectangle;

    int width;
    int height;

    int border;

    void create();

  public:
    Pad(/* args */);
    ~Pad();

    void draw(sf::RenderTarget &target);
};

void Pad::create()
{
    rectangle.setPosition(float(border), float(border));
    rectangle.setSize(
        sf::Vector2f(float(width - 2 * border), float(height - 2 * border)));
    rectangle.setOutlineThickness(float(border));

    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Transparent);
}

Pad::Pad(/* args */)
    : width(GLOBAL_WIDTH), height(GLOBAL_HEIGHT), border(THICKNESS)
{
    create();
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
