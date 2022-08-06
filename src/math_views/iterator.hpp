#ifndef CPT_ITERATOR_H_INCLUDED
#define CPT_ITERATOR_H_INCLUDED

#include <concepts>

namespace cpt
{
    class IteratorImpl {};

    template<class T>
    concept Iterator = std::is_base_of_v<IteratorImpl, T> 
        && requires(T a) {
               typename T::difference_type;
           };

    template<class T>
    concept EqualityComparableIterator = Iterator<T>
        && requires(T const a, T const b) {
               { a == b };
           };

    template<class T>
    concept ComparableIterator = Iterator<T>
        && requires(T const a, T const b) {
               { a < b };
           };

    template<class T>
    concept IncrementableIterator = Iterator<T>
        && requires(T a, T::difference_type diff) {
               { ++a };
               { a += diff };
           };

    template<class T>
    concept DecrementableIterator = Iterator<T>
        && requires(T a, T::difference_type diff) {
               { --a };
               { a -= diff };
           };

    template<EqualityComparableIterator Iterator>
    constexpr auto operator!=(Iterator const &left, Iterator const &right) noexcept
    {
        return !(right == left);
    }

    template<ComparableIterator Iterator>
    constexpr auto operator>(Iterator const &left, Iterator const &right) noexcept
    {
        return right < left;
    }
    template<ComparableIterator Iterator>
    constexpr auto operator>=(Iterator const &left, Iterator const &right) noexcept
    {
        return !(left < right);
    }
    template<ComparableIterator Iterator>
    constexpr auto operator<=(Iterator const &left, Iterator const &right) noexcept
    {
        return !(left > right);
    }

    template<IncrementableIterator Iterator>
    constexpr auto operator++(Iterator &it, int) noexcept
    {
        auto cpy = it;
        ++it;
        return cpy;
    }
    template<IncrementableIterator Iterator>
    constexpr auto operator+(Iterator const &it, typename Iterator::difference_type diff) noexcept
    {
        auto cpy = it;
        cpy += diff;
        return cpy;
    }
    template<IncrementableIterator Iterator>
    constexpr auto operator+(typename Iterator::difference_type diff, Iterator const &it) noexcept
    {
        return it + diff;
    }

    template<DecrementableIterator Iterator>
    constexpr auto operator--(Iterator &it, int) noexcept
    {
        auto cpy = it;
        --it;
        return cpy;
    }
    template<DecrementableIterator Iterator>
    constexpr auto operator-(Iterator const &it, typename Iterator::difference_type diff) noexcept
    {
        auto cpy = it;
        cpy -= diff;
        return cpy;
    }

} // namespace cpt


#endif