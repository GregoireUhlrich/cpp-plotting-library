#ifndef CPT_VIEW_H_INCLUDED
#define CPT_VIEW_H_INCLUDED

#include "array_view.hpp"
#include "math_view.hpp"
#include "generator_view.hpp"
#include "zip_view.hpp"

namespace cpt
{
    template<class T> 
    concept View = cpt::is_array_view_v<T> 
                || cpt::is_math_view_v<T>
                || cpt::is_zip_view_v<T>
                || cpt::is_generator_view_v<T>;

    template<View ViewType>
    using view_value_type = typename ViewType::output_value_type;

    template<ArrayRange Range>
        requires (!View<Range>)
    constexpr auto view(Range &range) noexcept
    {
        return ArrayView{range};
    }

    constexpr auto view(View auto view) noexcept
    {
        return view;
    }

    template<cpt::View ViewType, MathApplication<ViewType> FuncType>
    constexpr auto apply_on_view(ViewType x, FuncType func) noexcept
    {
        return MathView{std::move(x), std::move(func)};
    }    

    template<ArrayValue T, View ViewType>
    auto to(ViewType view)
    {
        if constexpr (std::is_same_v<T, view_value_type<ViewType>>) {
            return view;
        }
        else {
            return MathView{
                std::move(view),
                [](auto x) {
                    return static_cast<T>(x);
                }
            };
        }
    }
    
    template<ArrayValue T, View ViewType>
    Array<T> collect(ViewType const &view)
    {
        if constexpr (std::is_same_v<T, typename ViewType::output_value_type>) {
            return Array<T>(std::ranges::begin(view), std::ranges::end(view));
        }
        else {
            return collect<T>(to<T>(view));
        }
    }

    template<View ViewType>
    auto collect(ViewType const &view)
    {
        return collect<typename ViewType::output_value_type>(view);
    }

} // namespace cpt


#endif