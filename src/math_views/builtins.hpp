#ifndef CPT_BUILTINS_H_INCLUDED
#define CPT_BUILTINS_H_INCLUDED

#include <algorithm>

#include "../utils/error.hpp"
#include "array_view.hpp"
#include "generator_view.hpp"

namespace cpt
{
    class InvalidRangeError: public cpt::Exception {
        using Exception::Exception;
    };

    template<std::integral T>
    auto range(
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
        const auto n_points = (end - start) / step;
        return GeneratorView{
            static_cast<std::size_t>(n_points), 
            [start=start, step=step](std::size_t i) {
                return start + static_cast<T>(i)*step;
            }
        };
    }

    template<cpt::ArrayValue T>
    auto range(T end) {
        return range<T>(T{0}, end);
    } 

    template<cpt::ArrayValue T>
    auto constant(
        std::size_t n,
        T           value
    )
    {
        if (n == 0) {
            throw InvalidRangeError("Cannot create 0-size view.");
        }
        return GeneratorView{
            n, [value=value](std::size_t) { return value; }
        };
    }

    struct LinspaceConfig {
        bool end_point = true;
    };

    template<std::floating_point T = double>
    auto linspace(
        cpt::ArrayValue  auto start,
        cpt::ArrayValue  auto end,
        std::integral    auto n_points,
        LinspaceConfig const &config = {}
        )
    {
        if (n_points <= 0) {
            throw InvalidRangeError(
                "Cannot create linear space with 0 or less points (n = ", 
                n_points, 
                ").");
        }
        if (n_points == 1 && config.end_point) {
            throw InvalidRangeError(
                "Cannot create linspace with end point "
                "using only one point."
                );
        }
        const auto n_intervals = config.end_point ? n_points - 1 : n_points;
        const auto step = (static_cast<T>(end) - static_cast<T>(start)) 
                         / static_cast<T>(n_intervals);
        return GeneratorView{
            static_cast<std::size_t>(n_points),
            [start=static_cast<T>(start), step=step](std::size_t i) {
                return start + step * static_cast<T>(i);
            }
        };
    }

    struct LogspaceConfig {
        unsigned int base = 10;
        bool         end_point = true;
    };

    template<std::floating_point T = double>
    auto logspace(
        cpt::ArrayValue  auto start,
        cpt::ArrayValue  auto end,
        std::integral    auto n_points,
        LogspaceConfig const &config = {}
        )
    {
        if (n_points <= 0) {
            throw InvalidRangeError(
                "Cannot create logarithmic space with 0 or less points (n = ", 
                n_points, 
                ").");
        }
        if (n_points == 1 && config.end_point) {
            throw InvalidRangeError(
                "Cannot create logspace with end point "
                "using only one point."
                );
        }
        const auto n_intervals = config.end_point ? n_points - 1 : n_points;
        const auto step = (static_cast<T>(end) - static_cast<T>(start)) 
                         / static_cast<T>(n_intervals);
        return GeneratorView{
            static_cast<std::size_t>(n_intervals),
            [start=static_cast<T>(start), step=step, base=static_cast<T>(config.base)](std::size_t i) {
                return std::pow(base, start + step*static_cast<T>(i));
            }
        };
    }

} // namespace cpt


#endif