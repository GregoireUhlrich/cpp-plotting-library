#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics/Drawable.hpp>

namespace cpt {

class Drawable : public sf::Drawable {
  private:
    virtual void init() = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  public:
    Drawable();
    virtual ~Drawable();
};

Drawable::Drawable()
{
}

Drawable::~Drawable()
{
}

} // namespace cpt

#endif // DRAWABLE_HPP
