#ifndef CPT_NUMERIC_H_INCLUDED
#define CPT_NUMERIC_H_INCLUDED

#include <numeric>

namespace cpt
{
    template<class T>
    concept Numeric = std::integral<T> || std::floating_point<T>;

} // namespace cpt


#endif