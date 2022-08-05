#ifndef CPT_COLLECT_H_INCLUDED
#define CPT_COLLECT_H_INCLUDED

#include "math_view.hpp"
#include "array.hpp"
#include <span>

namespace cpt
{
    template<class Collection, class View>
        requires cpt::is_math_view_v<View>
    auto _collect_impl(View const &view)
    {
        return Collection {
            std::ranges::begin(view),
            std::ranges::end(view)
        };
    }

    template<class View>
        requires cpt::is_math_view_v<View>
    auto collect(View const &view)
    {
        return _collect_impl<cpt::Array<typename View::output_value_type>>(view);
    }
} // namespace cpt


#endif