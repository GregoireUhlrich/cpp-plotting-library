#ifndef CPT_MATH_H_INCLUDED
#define CPT_MATH_H_INCLUDED

#include <cmath>

#include "array_view.hpp"
#include "math_view.hpp"

namespace cpt
{    
    template<class View, MathApplication<View> Func>
        requires cpt::is_math_view_v<View>
    auto apply_on_view(View x, Func func)
    {
        return MathView{std::move(x), std::move(func)};
    }    

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    auto pow(View x, T n)
    {
        return cpt::apply_on_view(std::move(x), [n=n](auto xi) { return std::pow(xi, n); });
    }

    template<class View>
        requires cpt::is_math_view_v<View>
    auto cos(View x)
    {
        return cpt::apply_on_view(std::move(x), [](auto xi) { return std::cos(xi); });
    }

    template<class View>
        requires cpt::is_math_view_v<View>
    auto sin(View x)
    {
        return cpt::apply_on_view(std::move(x), [](auto xi) { return std::sin(xi); });
    }

    template<class View>
        requires cpt::is_math_view_v<View>
    auto tan(View x)
    {
        return cpt::apply_on_view(std::move(x), [](auto xi) { return std::tan(xi); });
    }
} // namespace cpt


#endif