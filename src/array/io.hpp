#ifndef CPT_IO_H_INCLUDED
#define CPT_IO_H_INCLUDED

#include "array_view.hpp"
#include "math_view.hpp"
#include "view.hpp"

namespace cpt
{
    template<class View>
        requires cpt::is_math_view_v<View>  
    void print(
        View   const &view,
        std::ostream &out = std::cout)
    {
        out << "[";
        std::copy(
            std::ranges::cbegin(view),
            std::ranges::cend(view),
            std::ostream_iterator<typename View::output_value_type>(out, ", "));
        out << "]\n";
    }

    template<ArrayRange Range>
        requires (!cpt::is_math_view_v<Range>)
    void print(
        Range  const &arr,
        std::ostream &out = std::cout)
    {
        cpt::print(cpt::view(arr), out);
    }
} // namespace cpt


#endif