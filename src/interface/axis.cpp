#include "axis.hpp"
#include "ticks.hpp"

namespace cpt
{
    Axis::Axis(Anchor anchor, float size)
        : _anchor(anchor),
          _size(size)
    {

    }

    void Axis::draw(sf::RenderTarget &target) const 
    {
        
    }

    void Axis::set_extent(float mini, float maxi)
    {
       auto ticks = calculate_ticks(mini, maxi); 
       //set_ticks(ticks, ticks);
    }

} // namespace cpt
