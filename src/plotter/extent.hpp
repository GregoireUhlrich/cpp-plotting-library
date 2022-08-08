#ifndef CPT_EXTENT_H_INCLUDED
#define CPT_EXTENT_H_INCLUDED

#include <concepts>

namespace cpt
{
    template<std::floating_point T = float>
    struct Extent {
        T xmin;
        T xmax;
        T ymin;
        T ymax;
    };

    template<std::floating_point T>
    Extent<T> combine(Extent<T> const &l, Extent<T> const &r)
    {
        return {
            .xmin = std::min(l.xmin, r.xmin),
            .xmax = std::max(l.xmax, r.xmax),
            .ymin = std::min(l.ymin, r.ymin),
            .ymax = std::max(l.ymax, r.ymax)
        };
    }
} // namespace cpt

#endif