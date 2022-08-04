#ifndef CPT_ZIPVIEW_H_INCLUDED
#define CPT_ZIPVIEW_H_INCLUDED

#include <ranges>
#include <utility>
#include <type_traits>

namespace cpt
{
    template<std::ranges::range LRange, std::ranges::range RRange>
    class ZipView;

    template<std::ranges::range LRange, std::ranges::range RRange>
    class ZipConstIterator {
    public:
        using Zip = ZipView<LRange, RRange>;
        using lvalue_t = Zip::lvalue_t;
        using rvalue_t = Zip::rvalue_t;
        using value_type = std::pair<lvalue_t, rvalue_t>;
        using difference_type = int;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        ZipConstIterator() = default;

        ZipConstIterator(Zip::const_literator liter_, Zip::const_riterator riter_)
            : liter(liter_), riter(riter_)
        {
            update();
        }

        auto operator*() { 
            return data; 
        }

        auto operator->() { 
            return &data; 
        }

        auto operator*() const { 
            return data; 
        }

        auto operator->() const { 
            return &data; 
        }

        bool operator==(ZipConstIterator o) const {
            return liter == o.liter;
        }
        bool operator!=(ZipConstIterator o) const {
            return !(*this == o);
        }

        ZipConstIterator &operator++() {
            ++liter;
            ++riter;
            update();
            return *this;
        }

        ZipConstIterator &operator++(int) {
            ZipConstIterator cpy{*this};
            ++(*this);
            return cpy;
        }

        ZipConstIterator &operator--() {
            --liter;
            --riter;
            update();
            return *this;
        }

        ZipConstIterator &operator--(int) {
            ZipConstIterator cpy{*this};
            --(*this);
            return cpy;
        }

    private:

        void update() {
            data.first = *liter;
            data.second = *riter;
        }

    private:
        Zip::const_literator liter;
        Zip::const_riterator riter;
        std::pair<lvalue_t, rvalue_t> data;
    };
        
    class IndexError: public cpt::Exception {
        using Exception::Exception;
    };

    template<cpt::NumRange TRange, cpt::NumRange URange>
    void bound_check(TRange const &t, URange const &u)
    {
        const auto t_size = std::ranges::size(t);
        const auto u_size = std::ranges::size(u);
        if (t_size != u_size) {
            throw IndexError(
                "Cannot compose range of size ", 
                t_size,
                " with range of size ",
                u_size
            );
        }
    }

    template<std::ranges::range LRange, std::ranges::range RRange>
    class ZipView: public std::ranges::view_interface<ZipView<LRange, RRange>> {

        friend class ZipConstIterator<LRange, RRange>;

    public:

        using lvalue_t = std::ranges::range_value_t<LRange>;
        using rvalue_t = std::ranges::range_value_t<RRange>;
        using const_literator = std::ranges::iterator_t<LRange>;
        using const_riterator = std::ranges::iterator_t<RRange>;
        using const_iterator = ZipConstIterator<LRange, RRange>;

        ZipView(LRange lrange_, RRange rrange_)
            :lrange(std::move(lrange_)), rrange(std::move(rrange_))
        {
            bound_check(lrange, rrange);
        }

        const_iterator begin() const noexcept { 
            return const_iterator(
                std::ranges::cbegin(lrange),
                std::ranges::cbegin(rrange)
            ); 
        }

        const_iterator end() const noexcept { 
            return const_iterator(
                std::ranges::cend(lrange),
                std::ranges::cend(rrange)
            ); 
        }

        auto size() const {
            return std::ranges::size(lrange);
        }

    private:

        LRange lrange;
        RRange rrange;
    };

} // namespace cpt


#endif