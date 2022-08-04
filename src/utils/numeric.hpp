#ifndef CPT_NUMERIC_H_INCLUDED
#define CPT_NUMERIC_H_INCLUDED

#include <numeric>

namespace cpt
{
    template<class T>
    concept Numeric = std::integral<T> || std::floating_point<T>;

    template<class R>
    concept NumRange = 
        std::ranges::range<R> 
        && Numeric<std::ranges::range_value_t<R>>;

} // namespace cpt


#endif