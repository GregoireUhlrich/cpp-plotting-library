#ifndef CPT_IO_H_INCLUDED
#define CPT_IO_H_INCLUDED

#include "array_view.hpp"
#include "math_view.hpp"

namespace cpt
{
    template<ArrayRange R>
    void print(
        MathView<R> const &view,
        std::ostream       &out = std::cout)
    {
        out << "[";
        std::copy(
            std::ranges::cbegin(view),
            std::ranges::cend(view),
            std::ostream_iterator<typename ArrayView<R>::value_type>(out, ", "));
        out << "]\n";
    }

    template<ArrayRange Range>
    void print(
        ArrayView<Range> const &arr,
        std::ostream           &out = std::cout)
    {
        cpt::print(MathView{arr}, out);
    }

    template<ArrayRange Range>
    void print(
        Range  const &arr,
        std::ostream &out = std::cout)
    {
        cpt::print(ArrayView{arr}, out);
    }
} // namespace cpt


#endif