#ifndef CPT_VIEW_H_INCLUDED
#define CPT_VIEW_H_INCLUDED

#include "array_view.hpp"
#include "math_view.hpp"

namespace cpt
{
    template<ArrayRange Range>
        requires (!std::ranges::view<Range>)
    constexpr auto view(Range &range)
    {
        return MathView{ArrayView{range}, identity<std::ranges::range_value_t<Range>>};
    }

    template<ArrayRange Range>
        requires (std::ranges::view<Range> && !cpt::is_math_view_v<Range>)
    constexpr auto view(Range const &range)
    {
        return MathView{range, identity<std::ranges::range_value_t<Range>>};
    }


    template<ArrayRange Range>
        requires (std::ranges::view<Range> && cpt::is_math_view_v<Range>)
    constexpr auto view(Range const &range)
    {
        return range;
    }

} // namespace cpt


#endif