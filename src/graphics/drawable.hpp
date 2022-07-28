#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

namespace graphic {

class Drawable {
  private:
    virtual void create() = 0;

  public:
    Drawable();
    virtual ~Drawable();

    virtual void draw(sf::RenderTarget &target) = 0;
};

Drawable::Drawable()
{
}

Drawable::~Drawable()
{
}

} // namespace graphic

#endif // DRAWABLE_HPP
