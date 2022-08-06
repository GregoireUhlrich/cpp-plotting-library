#ifndef CPT_ARRAYVIEW_H_INCLUDED
#define CPT_ARRAYVIEW_H_INCLUDED

#include <iostream>
#include <ranges>
#include <iterator>
#include <concepts>
#include <vector>

namespace cpt
{
    template<class T>
    concept ArrayValue = std::integral<T> || std::floating_point<T>;
    
    template<cpt::ArrayValue T>
    class Array: public std::vector<T>
    {
        using std::vector<T>::vector;
    };
    
    template<class Range>
    concept ArrayRange = 
        std::ranges::range<Range> 
        && std::is_object_v<Range> 
        && cpt::ArrayValue<std::ranges::range_value_t<Range>>;

    class ArrayViewBase {};

    template<ArrayRange Range>
    class ArrayView: private ArrayViewBase,
                     public std::ranges::ref_view<Range>
    {
    public:
        using std::ranges::ref_view<Range>::ref_view;
        using value_type = std::ranges::range_value_t<Range>;
        using output_value_type = value_type;
    };

    template<ArrayRange R>
    ArrayView(R &range) -> ArrayView<R>;

    template<ArrayRange R>
    ArrayView(R const &range) -> ArrayView<const R>;

    template<class T>
    struct is_array_view {
        constexpr static bool value = std::is_base_of_v<ArrayViewBase, std::remove_cvref_t<T>>;
    };

    template<class T>
    constexpr static bool is_array_view_v = is_array_view<T>::value;
    
} // namespace cpt


#endif