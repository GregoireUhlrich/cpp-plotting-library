#ifndef CPT_ZIPVIEW_H_INCLUDED
#define CPT_ZIPVIEW_H_INCLUDED

#include <ranges>
#include <functional>
#include "array_view.hpp"
#include "iterator.hpp"

namespace cpt
{
    template<class T, class LRange, class RRange>
    concept ZipApplication = 
        std::invocable<T, std::ranges::range_value_t<LRange>, std::ranges::range_value_t<RRange>>
        && ArrayValue<std::ranges::range_value_t<LRange>>
        && ArrayValue<std::ranges::range_value_t<RRange>>
        && ArrayValue<std::invoke_result_t<T, std::ranges::range_value_t<LRange>, std::ranges::range_value_t<RRange>>>;

    template <ArrayRange LRange, ArrayRange RRange, ZipApplication<LRange, RRange> Func>
        requires (std::ranges::view<LRange> && std::ranges::view<RRange>)
    class ZipView;

    template <ArrayRange LRange, ArrayRange RRange, ZipApplication<LRange, RRange> Func>
    struct ZipViewIteratorBase {
        using iterator_category = std::random_access_iterator_tag;
        using value_type = std::invoke_result_t<Func, std::ranges::range_value_t<LRange>, std::ranges::range_value_t<RRange>>;
        using reference  = value_type&;
        using pointer    = value_type*;
        using difference_type = std::ranges::range_difference_t<LRange>;
    };
    
    template <ArrayRange LRange, ArrayRange RRange, ZipApplication<LRange, RRange> Func>
    class ZipViewIterator: private IteratorImpl,
                           public ZipViewIteratorBase<LRange, RRange, Func> {

    public:
        using iterator_base = ZipViewIteratorBase<LRange, RRange, Func>;
        using lrange_t = LRange;
        using rrange_t = RRange;
        using func_t = Func;
        using literator = std::ranges::iterator_t<LRange>;
        using riterator = std::ranges::iterator_t<RRange>;
        using lvalue_type = std::ranges::range_value_t<LRange>;
        using rvalue_type = std::ranges::range_value_t<RRange>;

        using difference_type = typename iterator_base::difference_type;
        using value_type      = typename iterator_base::value_type;
        using reference       = typename iterator_base::reference;
        using pointer         = typename iterator_base::pointer;

        constexpr ZipViewIterator() = default;

        template<ZipApplication<LRange, RRange> FuncImpl>
        constexpr ZipViewIterator(literator lit, riterator rit, FuncImpl func) noexcept
            : _lit(lit), _rit(rit), _func(std::move(func))
        {

        }

        constexpr auto operator*() const noexcept { 
            return _func(*_lit, *_rit); 
        }
        constexpr ZipViewIterator &operator++() noexcept
        {
            ++_lit;
            ++_rit;
            return *this;
        }             
        constexpr ZipViewIterator &operator--() noexcept
        {
            --_lit;
            --_rit;
            return *this;
        }
        constexpr bool operator==(ZipViewIterator const &o) const noexcept {
            return o._lit == _lit;
        }
        constexpr bool operator<(ZipViewIterator const &o) const noexcept {
            return std::pair{_lit, _rit} < std::pair{o._lit, o._rit};
        }
        constexpr auto operator-(ZipViewIterator const &o) const noexcept {
            return _lit - o._lit;
        }
        constexpr auto &operator+=(difference_type diff) noexcept {
            _lit += diff;
            _rit += diff;
            return *this;
        }
        constexpr auto &operator-=(difference_type diff) noexcept {
            _lit -= diff;
            _rit -= diff;
            return *this;
        }
        constexpr auto operator[](difference_type diff) const noexcept {
            return *(*this + diff);
        }

        constexpr auto lit()  const noexcept { return _lit; }
        constexpr auto rit()  const noexcept { return _rit; }
        constexpr auto func() const noexcept { return _func; }

    private:
        literator _lit;
        riterator _rit;
        std::function<value_type(lvalue_type, rvalue_type)> _func;
    };

    class ZipViewBase {};

    template <ArrayRange LRange, ArrayRange RRange, ZipApplication<LRange, RRange> Func>
        requires (std::ranges::view<LRange> && std::ranges::view<RRange>)
    class ZipView : private ZipViewBase, 
                    public  std::ranges::view_interface<ZipView<LRange, RRange, Func>> {
    public:

        using lrange_t = LRange;
        using rrange_t = RRange;
        using func_t   = Func;

        using iterator       = ZipViewIterator<LRange, RRange, Func>;
        using const_iterator = ZipViewIterator<LRange, RRange, Func>;

        using lvalue_type  = std::ranges::range_value_t<LRange>;
        using rvalue_type  = std::ranges::range_value_t<RRange>;
        using output_value_type = std::invoke_result_t<Func, lvalue_type, rvalue_type>;

        constexpr ZipView() = default;

        constexpr ZipView(LRange lrange, RRange rrange, Func func) noexcept
            : _lrange(std::move(lrange)), _rrange(std::move(rrange)), _func(std::move(func))
        {

        }

        constexpr auto size()  const noexcept { 
            return std::min(std::ranges::size(_lrange), std::ranges::size(_rrange));
        }
        constexpr auto empty() const noexcept { return size() == 0; }
        constexpr auto begin() const noexcept { 
            return ZipViewIterator<LRange, RRange, Func>(
                std::ranges::begin(_lrange), 
                std::ranges::begin(_rrange),
                _func); 
        }
        constexpr auto end() const noexcept { 
            const auto sz = size();
            return ZipViewIterator<LRange, RRange, Func>(
                std::ranges::begin(_lrange) 
                    + static_cast<typename LRange::iterator::difference_type>(sz), 
                std::ranges::begin(_rrange) 
                    + static_cast<typename RRange::iterator::difference_type>(sz),
                _func); 
        }

    private:
        LRange _lrange;
        RRange _rrange;
        std::function<output_value_type(lvalue_type, rvalue_type)> _func;
    };

    template<class T>
    struct is_zip_view {
        constexpr static bool value = std::is_base_of_v<ZipViewBase, std::remove_cvref_t<T>>;
    };

    template<class T>
    constexpr static bool is_zip_view_v = is_zip_view<T>::value;

} // namespace cpt

#endif