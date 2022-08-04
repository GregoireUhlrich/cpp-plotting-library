#ifndef CPT_FUNCTION_H_INCLUDED
#define CPT_FUNCTION_H_INCLUDED

#include <cmath>
#include <ranges>
#include "../utils/numeric.hpp"
#include "../collections/numview.hpp"
#include "../collections/numcollection.hpp"

namespace cpt
{
    template<cpt::NumRange Range, std::invocable<std::ranges::range_value_t<Range>> Callable>
    auto apply_on_view(
        cpt::NumView<Range> const &view,
        Callable                    &&f
        )
    {
        return NumView{
             view | std::views::transform(
                [f=std::forward<Callable>(f)](auto value) { 
                    return f(value);
                }
            )
        };
    }

    template<std::ranges::range Range>
    auto cos(Range const &range)
    {
        return apply_on_view(cpt::view(range), [](auto value) {
            return std::cos(value);
        });
    }    
    
    template<std::ranges::range Range>
    auto sin(Range const &range)
    {
        return apply_on_view(cpt::view(range), [](auto value) {
            return std::sin(value);
        });
    }
} // namespace cpt

#endif