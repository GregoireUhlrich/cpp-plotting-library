#ifndef CPT_FUNCTION_H_INCLUDED
#define CPT_FUNCTION_H_INCLUDED

#include <cmath>
#include <ranges>
#include "../utils/numeric.hpp"

namespace cpt
{
    template<
        std::ranges::range Range, 
        std::invocable<std::ranges::range_value_t<Range>> Callable
        >
    auto apply_on_range(
        Range    &&range,
        Callable &&f
        )
    {
        return range
            | std::views::transform([f=std::forward<Callable>(f)](auto value) { 
                return f(value);
            });
    }

    template<std::ranges::range Range>
        requires cpt::Numeric<std::ranges::range_value_t<Range>>
    auto cos(Range &&range)
    {
        using Value = std::ranges::range_value_t<Range>;
        return apply_on_range(std::forward<Range>(range), [](Value value) {
            return std::cos(value);
        });
    }
} // namespace cpt

#endif