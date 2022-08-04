#ifndef CPT_MATHVIEW_H_INCLUDED
#define CPT_MATHVIEW_H_INCLUDED

#include <ranges>
#include "array_view.hpp"

namespace cpt
{
    class MathViewBase {};

    template <ArrayRange Range>
        requires std::ranges::view<Range>
    class MathView : private MathViewBase, 
                     public  std::ranges::view_interface<MathView<Range>> {
    public:

        MathView() = default;

        MathView(Range range)
            : _range(std::move(range))
        {

        }

        auto size()  const { return std::ranges::size(_range);  }
        auto empty() const { return std::ranges::empty(_range); }
        auto begin() const { return std::ranges::begin(_range); }
        auto end()   const { return std::ranges::end(_range);   }
    private:
        Range _range;
    };

    template<class T>
    struct is_math_view {
        constexpr static bool value = std::derived_from<T, MathViewBase>;
    };

    template<class T>
    constexpr static bool is_math_view_v = is_math_view<T>::value;

} // namespace cpt


#endif