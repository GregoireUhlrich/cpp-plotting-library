#ifndef CPP_PLOT_PRINTABLE_H_INCLUDED
#define CPP_PLOT_PRINTABLE_H_INCLUDED

#include <iostream>

template<class T>
concept Printable = requires(T el, std::ostream &out)
{
    out << el;
};

#endif