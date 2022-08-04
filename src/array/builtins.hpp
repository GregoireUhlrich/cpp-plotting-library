#ifndef CPT_BUILTINS_H_INCLUDED
#define CPT_BUILTINS_H_INCLUDED

#include <algorithm>

#include "array.hpp"
#include "../utils/error.h"

namespace cpt
{
    class InvalidRangeError: public cpt::Exception {
        using Exception::Exception;
    };

    template<cpt::ArrayValue T>
    cpt::Array<T> range(
        T start, 
        T end,
        T step = T{1})    
    {
        if (step == 0) {
            throw InvalidRangeError("Cannot create range with step 0.");
        }
        if ((end - start) * step < 0) {
            throw InvalidRangeError(
                "Invalid step sign (step = ", step, ") for a range ",
                "(start = ", start, ", end = ", end, "). Consider ",
                "flipping the step sign."
            );
        }
        cpt::Array<T> res((end - start) / step);
        std::ranges::generate(res, [val=start, step=step]() mutable {
            const T new_val = val;
            val += step;
            return new_val;
        });
        return res;
    }

    template<cpt::ArrayValue T>
    cpt::Array<T> range(T end) {
        return range<T>(T{0}, end);
    } 

} // namespace cpt


#endif