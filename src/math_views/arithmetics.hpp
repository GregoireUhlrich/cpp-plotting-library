#ifndef CPT_ARITHMETICS_H_INCLUDED
#define CPT_ARITHMETICS_H_INCLUDED

#include <ranges>
#include "view.hpp"

namespace cpt
{
    //////////////////////////////////////
    // Scalar Operators
    //////////////////////////////////////

    constexpr auto operator+(View auto view, ArrayValue auto val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x + val;
            }
        };
    }   

    constexpr auto operator+(ArrayValue auto val, View auto view)
    {
        return (std::move(view) + val);
    }   

    constexpr auto operator-(View auto view)
    {
        return MathView {
            std::move(view),
            [](auto x) {
                return -x;
            }
        };
    }   

    constexpr auto operator-(View auto view, ArrayValue auto val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x - val;
            }
        };
    }   

    constexpr auto operator-(ArrayValue auto val, View auto view)
    {
        return ((-std::move(view)) + val);
    }   

    constexpr auto operator*(View auto view, ArrayValue auto val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x * val;
            }
        };
    }   

    constexpr auto operator*(ArrayValue auto val, View auto view)
    {
        return (std::move(view) * val);
    }   

    constexpr auto operator/(View auto view, ArrayValue auto val)
    {
        return MathView {
            std::move(view),
            [val=val](auto x) {
                return x / val;
            }
        };
    }   

    constexpr auto operator/(ArrayValue auto val, View auto view)
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
    
    constexpr auto operator+(View auto lview, View auto rview)
    {
        return ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { 
                return x + y; 
            }
        };
    }    
    
    constexpr auto operator*(View auto lview, View auto rview)
    {
        return ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { 
                return x * y; 
            }
        };
    }

    constexpr auto operator-(View auto lview, View auto rview)
    {
        return ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { 
                return x - y; 
            }
        };
    }

    constexpr auto operator/(View auto lview, View auto rview)
    {
        return ZipView{
            std::move(lview), 
            std::move(rview), 
            [](auto x, auto y) { 
                return x / y; 
            }
        };
    }

} // namespace cpt

#endif