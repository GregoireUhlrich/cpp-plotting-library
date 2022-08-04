#ifndef CPT_ARRAYVALUE_H_INCLUDED
#define CPT_ARRAYVALUE_H_INCLUDED

#include <concepts>
#include <numeric>

namespace cpt
{
    template<class T>
    concept ArrayValue = std::integral<T> || std::floating_point<T>;
    
} // namespace cpt


#endif