#ifndef CPT_PRINTABLE_H_INCLUDED
#define CPT_PRINTABLE_H_INCLUDED

#include <iostream>

namespace cpt
{
    
template<class T>
concept Printable = requires(T el, std::ostream &out)
{
    out << el;
};
} // namespace cpt


#endif