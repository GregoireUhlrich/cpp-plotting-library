#ifndef CPT_MATHVIEW_H_INCLUDED
#define CPT_MATHVIEW_H_INCLUDED

#include <ranges>
#include <functional>
#include "array_view.hpp"

namespace cpt
{
    class MathViewBase {};


    template<class T, class Range>
    concept MathApplication = std::invocable<T, std::ranges::range_value_t<Range>>
        && ArrayValue<std::ranges::range_value_t<Range>>
        && ArrayValue<std::invoke_result_t<T, std::ranges::range_value_t<Range>>>;

    template<ArrayValue T>
    constexpr static auto identity = [](T x) { return x; };

    template <ArrayRange Range, MathApplication<Range> Func>
        requires std::ranges::view<Range>
    class MathView;

    template <ArrayRange Range, MathApplication<Range> Func>
    class MathViewIterator {
    public:
        using range_t = Range;
        using func_t = Func;
        using iterator = std::ranges::iterator_t<Range>;
        using input_value_type = std::ranges::range_value_t<Range>;
        using value_type = std::invoke_result_t<Func, input_value_type>;
        using difference_type = decltype(std::declval<iterator>()-std::declval<iterator>());
        using reference = value_type&;
        using pointer   = value_type*;

        constexpr MathViewIterator() = default;

        template<class FuncImpl>
        explicit
        constexpr MathViewIterator(iterator it, FuncImpl func) noexcept
            : _it(it), _func(std::move(func))
        {

        }

        constexpr auto operator*() const { return _func(*_it); }

        constexpr auto operator-(MathViewIterator const &o) const {
            return _it - o._it;
        }
        constexpr MathViewIterator operator+(difference_type diff) const {
            return MathViewIterator<Range, Func>{_it + diff, _func};
        }

        constexpr MathViewIterator &operator++() noexcept
        {
            ++_it;
            return *this;
        }
        constexpr MathViewIterator operator++(int) noexcept
        {
            MathViewIterator<Range, Func> cpy{*this};
            ++(*this);
            return cpy;
        }
             
        constexpr MathViewIterator &operator--() noexcept
        {
            --_it;
            return *this;
        }
        constexpr MathViewIterator operator--(int) noexcept
        {
            MathViewIterator<Range, Func> cpy{*this};
            --(*this);
            return cpy;
        }

        constexpr bool operator==(MathViewIterator const &o) const noexcept {
            return o._it == _it;
        }
        constexpr bool operator!=(MathViewIterator const &o) const noexcept {
            return !(*this == o);
        }

    private:
        iterator _it;
        std::function<value_type(input_value_type)> _func;
    };


    template <ArrayRange Range, MathApplication<Range> Func>
        requires std::ranges::view<Range>
    class MathView : private MathViewBase, 
                     public  std::ranges::view_interface<MathView<Range, Func>> {
    public:

        using iterator       = MathViewIterator<Range, Func>;
        using const_iterator = MathViewIterator<Range, Func>;
        using input_value_type  = std::ranges::range_value_t<Range>;
        using output_value_type = std::invoke_result_t<Func, input_value_type>;

        constexpr MathView() = default;

        constexpr MathView(Range range) noexcept
            : _range(std::move(range)), _func(identity<input_value_type>)
        {
        }

        constexpr MathView(Range range, Func func) noexcept
            : _range(std::move(range)), _func(std::move(func))
        {
        }

        constexpr auto size()  const noexcept { return std::ranges::size(_range);  }
        constexpr auto empty() const noexcept { return std::ranges::empty(_range); }
        constexpr auto begin() const noexcept { return MathViewIterator<Range, Func>(std::ranges::begin(_range), _func); }
        constexpr auto end()   const noexcept { return MathViewIterator<Range, Func>(std::ranges::end(_range), _func);   }

    private:
        Range _range;
        std::function<output_value_type(input_value_type)> _func;
    };

    template<ArrayRange Range>
    MathView(Range) -> MathView<Range, decltype(identity<std::ranges::range_value_t<Range>>)>;

    template<class T>
    struct is_math_view {
        constexpr static bool value = std::is_base_of_v<MathViewBase, T>;
    };

    template<class T>
    constexpr static bool is_math_view_v = is_math_view<T>::value;

} // namespace cpt


#endif