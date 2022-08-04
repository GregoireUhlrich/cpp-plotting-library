#ifndef CPT_ARRAYVIEW_H_INCLUDED
#define CPT_ARRAYVIEW_H_INCLUDED

#include <iostream>
#include <ranges>
#include <iterator>
#include "array_value.hpp"

namespace cpt
{
    template<class Range>
    concept ArrayRange = 
        std::ranges::range<Range> 
        && std::is_object_v<Range> 
        && cpt::ArrayValue<std::ranges::range_value_t<Range>>;

    template<ArrayRange Range>
    class ArrayView: public std::ranges::ref_view<Range>
    {
    public:
        using std::ranges::ref_view<Range>::ref_view;
        using value_type = std::ranges::range_value_t<Range>;
    };

    template<ArrayRange R>
    ArrayView(R &range) -> ArrayView<R>;

    template<ArrayRange R>
    ArrayView(R const &range) -> ArrayView<const R>;
    
} // namespace cpt


#endif