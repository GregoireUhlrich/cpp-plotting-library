#ifndef CPT_ARRAY_H_INCLUDED
#define CPT_ARRAY_H_INCLUDED

#include <vector>
#include "array_value.hpp"

namespace cpt
{
    template<cpt::ArrayValue T>
    class Array: public std::vector<T>
    {
        using std::vector<T>::vector;
    };

} // namespace cpt


#endif