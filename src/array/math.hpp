#ifndef CPT_MATH_H_INCLUDED
#define CPT_MATH_H_INCLUDED

#include <cmath>

#include "array_view.hpp"
#include "math_view.hpp"
#include "zip_view.hpp"

namespace cpt
{    
    template<class View, MathApplication<View> Func>
        requires cpt::is_math_view_v<View>
    constexpr auto apply_on_view(View x, Func func) noexcept
    {
        return MathView{std::move(x), std::move(func)};
    }    

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto pow(View x, T n) noexcept
    {
        return cpt::apply_on_view(std::move(x), [n=n](auto xi) { 
            return std::pow(xi, n); 
        });
    }

    template<class YView, class XView, ArrayValue T>
        requires (cpt::is_math_view_v<XView> && cpt::is_math_view_v<YView>)
    constexpr auto atan2(YView y, XView x) noexcept
    {
        return MathView{ZipView{y, x, [](auto yi, auto xi) {
            return std::atan2(yi, xi);
        }}};
    }

    #define DEFINE_CPT_FUNCTION(func)                             \
        template<class View>                                      \
            requires cpt::is_math_view_v<View>                    \
        constexpr auto func(View x) noexcept                      \
        {                                                         \
            return cpt::apply_on_view(std::move(x), [](auto xi) { \
                return std::func(xi);                             \
            });                                                   \
        }

    DEFINE_CPT_FUNCTION(exp)
    DEFINE_CPT_FUNCTION(exp2)
    DEFINE_CPT_FUNCTION(log)
    DEFINE_CPT_FUNCTION(log2)
    DEFINE_CPT_FUNCTION(log10)
    DEFINE_CPT_FUNCTION(sqrt)
    DEFINE_CPT_FUNCTION(cbrt)
    DEFINE_CPT_FUNCTION(cos)
    DEFINE_CPT_FUNCTION(sin)
    DEFINE_CPT_FUNCTION(tan)
    DEFINE_CPT_FUNCTION(acos)
    DEFINE_CPT_FUNCTION(asin)
    DEFINE_CPT_FUNCTION(atan)
    DEFINE_CPT_FUNCTION(cosh)
    DEFINE_CPT_FUNCTION(sinh)
    DEFINE_CPT_FUNCTION(tanh)
    DEFINE_CPT_FUNCTION(acosh)
    DEFINE_CPT_FUNCTION(asinh)
    DEFINE_CPT_FUNCTION(atanh)

    #undef DEFINE_CPT_FUNCTION

} // namespace cpt


#endif