#ifndef CPT_MATH_H_INCLUDED
#define CPT_MATH_H_INCLUDED

#include <cmath>

#include "array_view.hpp"
#include "math_view.hpp"
#include "zip_view.hpp"
#include "view.hpp"

namespace cpt
{    
    template<cpt::View ViewType, MathApplication<ViewType> FuncType>
    constexpr auto apply_on_view(ViewType x, FuncType func) noexcept
    {
        return MathView{std::move(x), std::move(func)};
    }    

    constexpr auto pow(cpt::View auto x, cpt::ArrayValue auto n) noexcept
    {
        return cpt::apply_on_view(
            std::move(x), 
            [n=n](auto xi) { 
                return std::pow(xi, n); 
            }
        );
    }

    constexpr auto atan2(cpt::View auto y, cpt::View auto x) noexcept
    {
        return ZipView{
            std::move(y), 
            std::move(x), 
            [](auto yi, auto xi) {
                return std::atan2(yi, xi);
            }
        };
    }

    #define DEFINE_CPT_FUNCTION(func)                  \
        constexpr auto func(cpt::View auto x) noexcept \
        {                                              \
            return cpt::apply_on_view(                 \
                std::move(x),                          \
                [](auto xi) {                          \
                    return std::func(xi);              \
                }                                      \
            );                                         \
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