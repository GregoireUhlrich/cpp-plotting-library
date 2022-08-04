#ifndef CPT_ARITHMETICS_H_INCLUDED
#define CPT_ARITHMETICS_H_INCLUDED

#include <ranges>
#include "math_view.hpp"
#include "zip_view.hpp"

namespace cpt
{
    //////////////////////////////////////
    // Scalar Operators
    //////////////////////////////////////

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator+(View view, T val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x + val;
            }
        };
    }   

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator+(T val, View view)
    {
        return (std::move(view) + val);
    }   

    template<class View>
        requires cpt::is_math_view_v<View>
    constexpr auto operator-(View view)
    {
        return MathView {
            std::move(view),
            [](auto x) {
                return -x;
            }
        };
    }   

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator-(View view, T val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x - val;
            }
        };
    }   

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator-(T val, View view)
    {
        return ((-std::move(view)) + val);
    }   

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator*(View view, T val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x * val;
            }
        };
    }   

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator*(T val, View view)
    {
        return (std::move(view) * val);
    }   

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator/(View view, T val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x / val;
            }
        };
    }   

    template<class View, ArrayValue T>
        requires cpt::is_math_view_v<View>
    constexpr auto operator/(T val, View view)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return val / x;
            }
        };
    }   

    //////////////////////////////////////
    // Vector Operators
    //////////////////////////////////////
    
    template<class LView, class RView>
        requires(cpt::is_math_view_v<LView> && cpt::is_math_view_v<RView>)
    constexpr auto operator+(LView lview, RView rview)
    {
        return MathView{ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { return x + y; }
            }
        };
    }    
    
    template<class LView, class RView>
        requires(cpt::is_math_view_v<LView> && cpt::is_math_view_v<RView>)
    constexpr auto operator*(LView lview, RView rview)
    {
        return MathView{ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { return x * y; }
            }
        };
    }

    template<class LView, class RView>
        requires(cpt::is_math_view_v<LView> && cpt::is_math_view_v<RView>)
    constexpr auto operator-(LView lview, RView rview)
    {
        return MathView{ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { return x - y; }
            }
        };
    }

    template<class LView, class RView>
        requires(cpt::is_math_view_v<LView> && cpt::is_math_view_v<RView>)
    constexpr auto operator/(LView lview, RView rview)
    {
        return MathView{ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { return x / y; }
            }
        };
    }

} // namespace cpt

#endif