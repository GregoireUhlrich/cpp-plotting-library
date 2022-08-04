#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

namespace cpt {

class Drawable {
  private:
    virtual void init() = 0;

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

} // namespace cpt

#endif // DRAWABLE_HPP
