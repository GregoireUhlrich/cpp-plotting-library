#ifndef PAD_HPP
#define PAD_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace graphics {

class Pad {
  private:
    sf::RectangleShape box;

  public:
    Pad(/* args */);
    ~Pad();

    void draw(sf::RenderTarget &target);
};

Pad::Pad(/* args */)
{
    box.setFillColor(sf::Color::Blue);
}

Pad::~Pad()
{
}

void Pad::draw(sf::RenderTarget &target)
{
    target.draw(box);
}

} // namespace graphics

#endif // PAD_HPP
