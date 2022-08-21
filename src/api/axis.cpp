#include "axis.hpp"
#include "ticks.hpp"

namespace cpt
{
    AxisRenderer::AxisRenderer(Anchor anchor, float size)
        : _anchor(anchor),
          _size(size)
    {

    }

    void AxisRenderer::draw(sf::RenderTarget &target) const 
    {
        
    }

    void AxisRenderer::set_extent(float mini, float maxi)
    {
       auto ticks = calculate_ticks(mini, maxi); 
       //set_ticks(ticks, ticks);
    }

} // namespace cpt
