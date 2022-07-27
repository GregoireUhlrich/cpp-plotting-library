#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <array>
#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "pad.hpp"

namespace graphic {

class Drawable {
  private:
    Pad             pad;
    sf::CircleShape circle;

    void create();

  public:
    Drawable();
    Drawable(Pad &pad);
    virtual ~Drawable();

    void draw(sf::RenderTarget &target);
};

void Drawable::create()
{
    circle.setRadius(110.0f);
    circle.setFillColor(sf::Color::Green);
}

Drawable::Drawable() : pad(Pad())
{
    create();
}

Drawable::Drawable(Pad &pad) : pad(pad)
{
    create();
}

Drawable::~Drawable()
{
}

void Drawable::draw(sf::RenderTarget &target)
{
    pad.draw(target);
    target.draw(circle);
}

} // namespace graphic

#endif // DRAWABLE_HPP
