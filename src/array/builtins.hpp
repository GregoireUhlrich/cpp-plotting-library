#ifndef CPT_BUILTINS_H_INCLUDED
#define CPT_BUILTINS_H_INCLUDED

#include <algorithm>

#include "array.hpp"
#include "../utils/error.hpp"

namespace cpt
{
    class InvalidRangeError: public cpt::Exception {
        using Exception::Exception;
    };

    template<std::integral T>
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

    struct LinspaceConfig {
        bool end_point = true;
    };

    template<std::floating_point T = double>
    cpt::Array<T> linspace(
        cpt::ArrayValue auto start,
        cpt::ArrayValue auto end,
        std::integral auto n_points,
        LinspaceConfig const &config = {}
        )
    {
        if (n_points <= 0) {
            throw InvalidRangeError(
                "Cannot create linear space with 0 or less points (n = ", 
                n_points, 
                ").");
        }
        if (n_points == 1) {
            if (config.end_point) {
                throw InvalidRangeError(
                    "Cannot create linspace with end point "
                    "using only one point."
                    );
            }
            return {start};
        }
        const auto n_intervals = config.end_point ? n_points - 1 : n_points;
        cpt::Array<T> res(n_points);
        const auto step = (static_cast<T>(end) - static_cast<T>(start)) 
                         / static_cast<T>(n_intervals);
        std::ranges::generate(res, [val=start, step=step]() mutable {
            const T x = val;
            val += step;
            return x;
        });
        return res;
    }

} // namespace cpt


#endif