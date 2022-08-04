#ifndef CPT_COLLECTION_H_INCLUDED
#define CPT_COLLECTION_H_INCLUDED

#include <vector>
#include <algorithm>
#include "numview.hpp"
#include "../utils/numeric.hpp"

namespace cpt
{
    template<cpt::Numeric T>
    using NumCollection = std::vector<T>;

    template<std::ranges::range Range>
        requires cpt::Numeric<std::ranges::range_value_t<Range>>
    NumCollection<std::ranges::range_value_t<Range>> collect(Range &&range)
    {
        NumCollection<std::ranges::range_value_t<Range>> res(std::ranges::size(range));
        std::ranges::generate(res, std::forward<Range>(range));
        return res;
    }
} // namespace cpt

#endif