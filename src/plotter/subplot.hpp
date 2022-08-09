#ifndef CPT_SUBPLOT_H_INCLUDED
#define CPT_SUBPLOT_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace cpt
{
    class Subplot {
    public:
        Subplot() = default;
        Subplot(Subplot const &) = delete;
        Subplot(Subplot &&) noexcept = default;

        sf::Vector2f get_position() const noexcept;
        sf::Vector2f get_size() const noexcept;

        void set_position(float x, float y) noexcept;
        void set_size(float sx, float sy) noexcept;
    
    private:
        sf::Vector2f _pos;
        sf::Vector2f _size;
    };
} // namespace cpt

#endif