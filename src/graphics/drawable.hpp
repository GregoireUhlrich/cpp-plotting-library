#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics/Drawable.hpp>

namespace cpt {

class Drawable : public sf::Drawable {
  private:
    virtual void init() = 0;
};

} // namespace cpt

#endif // DRAWABLE_HPP
