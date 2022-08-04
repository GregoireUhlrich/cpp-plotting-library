#ifndef CPT_VIEW_H_INCLUDED
#define CPT_VIEW_H_INCLUDED

#include <ranges>
#include "../utils/numeric.hpp"

namespace cpt
{    
    template<cpt::NumRange Range>
    class NumView: public std::ranges::view_interface<NumView<Range>> {
        public:

        using value_t = std::ranges::range_value_t<Range>;
        using range_t = Range;

        NumView() = default;
        NumView(Range range_)
            : range(std::move(range_))
        {

        }

        auto begin() const noexcept { return std::ranges::begin(range); }
        auto end()   const noexcept { return std::ranges::end(range);   }

        auto size() const {
            return std::ranges::size(range);
        }

        private:
        
        mutable range_t range;
    };

    template<std::ranges::range Range>
    NumView(Range const &range) -> NumView<Range>;

    template<NumRange Range>
    auto view(NumView<Range> const &view) {
        return view;
    }

    template<NumRange Range>
    auto view(Range const &view) {
        return NumView{std::views::all(view)};
    }

} // namespace cpt

#endif