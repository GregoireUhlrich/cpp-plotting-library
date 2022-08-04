#ifndef CPT_RANGE_H_INCLUDED
#define CPT_RANGE_H_INCLUDED

#include "numcollection.hpp"
#include "../utils/error.hpp"
#include <numeric>
#include <algorithm>

namespace cpt
{
    class InvalidRangeError: public Exception {
        using Exception::Exception;
    };

    template<std::integral T = int>
    NumCollection<T> range(
        T start,
        T end,
        T step)   
    {
        if (step == 0) {
            throw InvalidRangeError("Cannot create a range with a 0 step.");
        }
        if ((end - start)*step < 0) {
            throw InvalidRangeError(
                "Step ", step, 
                " is invalid (wrong sign) for range [", 
                start, ", ", end, ").");
        }
        NumCollection<T> range((end - start) / step);
        std::ranges::generate(range, [value = start, step=step]() mutable  { 
            const auto res = value;
            value += step;
            return res;
        });
        return range; 
    }

    template<std::integral T = int>
    NumCollection<T> range(
        T start,
        T end)
    {
        return range<T>(start, end, 1);
    }   

    template<std::integral T = int>
    NumCollection<T> range(T end)
    {
        return range<T>(0, end);
    }   
} // namespace cpt

#endif