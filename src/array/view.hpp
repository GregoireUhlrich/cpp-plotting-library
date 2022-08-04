#ifndef CPT_VIEW_H_INCLUDED
#define CPT_VIEW_H_INCLUDED

#include "array_view.hpp"
#include "math_view.hpp"

namespace cpt
{
    template<ArrayRange Range>
        requires (!std::ranges::view<Range>)
    auto view(Range range)
    {
        return MathView{ArrayView{range}};
    }

    template<ArrayRange Range>
        requires (std::ranges::view<Range> && !cpt::is_math_view_v<Range>)
    auto view(Range range)
    {
        return MathView{std::move(range)};
    }


    template<ArrayRange Range>
        requires (std::ranges::view<Range> && cpt::is_math_view_v<Range>)
    auto view(Range range)
    {
        return std::move(range);
    }

} // namespace cpt


#endif