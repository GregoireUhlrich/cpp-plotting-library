#ifndef CPT_IO_H_INCLUDED
#define CPT_IO_H_INCLUDED

#include "view.hpp"

namespace cpt
{
    template<View ViewType>
    void print(
        ViewType const &view,
        std::ostream   &out = std::cout)
    {
        out << "[";
        std::copy(
            std::ranges::cbegin(view),
            std::ranges::cend(view),
            std::ostream_iterator<typename ViewType::output_value_type>(out, ", "));
        out << "]\n";
    }

    template<ArrayRange Range>
        requires (!View<Range>)
    void print(
        Range  const &arr,
        std::ostream &out = std::cout)
    {
        cpt::print(cpt::view(arr), out);
    }
} // namespace cpt


#endif