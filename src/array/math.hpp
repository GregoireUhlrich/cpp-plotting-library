#ifndef CPT_MATH_H_INCLUDED
#define CPT_MATH_H_INCLUDED

#include <cmath>

#include "array_view.hpp"
#include "math_view.hpp"

namespace cpt
{
    template<ArrayRange R, std::invocable<std::ranges::range_value_t<R>> Func>
        requires (!std::same_as<void, std::invoke_result_t<Func, std::ranges::range_value_t<R>>>)
    auto apply(MathView<R> const &x, Func &&f)
    {
        using T = std::ranges::range_value_t<R>;
        return MathView{
            x | std::views::transform(
                [f=std::forward<Func>(f)](T xi) { 
                    return f(xi);
                })
        };
    }    

    template<ArrayRange R>
    auto cos(MathView<R> const &x)
    {
        using T = std::ranges::range_value_t<R>;
        return apply(x, [](T xi) { return std::cos(xi); });
    }

    template<ArrayRange R>
    auto sin(MathView<R> const &x)
    {
        using T = std::ranges::range_value_t<R>;
        return apply(x, [](T xi) { return std::sin(xi); });
    }
} // namespace cpt


#endif