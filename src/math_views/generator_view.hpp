#ifndef CPT_GENERATORVIEW_H_INCLUDED
#define CPT_GENERATORVIEW_H_INCLUDED

#include <ranges>
#include <iterator>
#include <concepts>
#include <functional>
#include "array_view.hpp"
#include "iterator.hpp"

namespace cpt
{
    template<class T>
    concept Generator = std::invocable<T, std::size_t>
        && ArrayValue<std::invoke_result_t<T, std::size_t>>;

    template<Generator G>
    using GeneratorViewIteratorBase = std::iterator<
            std::random_access_iterator_tag,
            std::invoke_result_t<G, std::size_t>,
            std::ptrdiff_t
            >;

    template<Generator G>
    class GeneratorViewIterator: private IteratorImpl,
                                 public GeneratorViewIteratorBase<G> {
    public:
        using iterator_base = GeneratorViewIteratorBase<G>;

        using generator_t = G;
        
        using difference_type = iterator_base::difference_type;
        using value_type      = iterator_base::value_type;
        using reference       = iterator_base::reference;
        using pointer         = iterator_base::pointer;

        GeneratorViewIterator() = default;

        template<Generator GImpl>
        constexpr GeneratorViewIterator(std::size_t it, GImpl generator) noexcept
            : _it(it), _generator(std::move(generator))
        {

        }

        constexpr auto operator*() const noexcept { return _generator(_it); }

        constexpr auto &operator++() noexcept { 
            ++_it; 
            return *this;
        }
        constexpr auto &operator--() noexcept { 
            --_it;
            return *this;
        }
        constexpr bool operator==(GeneratorViewIterator const &o) const noexcept {
            return o._it == _it;
        }
        constexpr bool operator<(GeneratorViewIterator const &o) const noexcept {
            return _it < o._it;
        }
        constexpr auto operator-(GeneratorViewIterator const &o) const noexcept {
            return _it - o._it;
        }
        constexpr auto &operator+=(difference_type diff) noexcept {
            _it += diff;
            return *this;
        }
        constexpr auto &operator-=(difference_type diff) noexcept {
            _it -= diff;
            return *this;
        }
        constexpr auto operator[](difference_type diff) const noexcept {
            return *(*this + diff);
        }

        constexpr auto it()        const noexcept { return _it; }
        constexpr auto generator() const noexcept { return _generator; }
    
    private:
        std::size_t _it;
        std::function<value_type(std::size_t)> _generator;
    };

    class GeneratorViewBase {};

    template<Generator G>
    class GeneratorView: private GeneratorViewBase,
                         public std::ranges::view_interface<GeneratorView<G>> {
    public: 
        using generator_t = G;

        using iterator       = GeneratorViewIterator<G>;
        using const_iterator = GeneratorViewIterator<G>;

        using output_value_type = std::invoke_result_t<G, std::size_t>;
        
        constexpr GeneratorView() = default;

        constexpr GeneratorView(std::size_t size, G generator) noexcept
            : _size(size), _generator(std::move(generator))
        {
        }

        constexpr auto size()  const noexcept { return _size;  }
        constexpr auto empty() const noexcept { return _size == 0; }
        constexpr auto begin() const noexcept { return GeneratorViewIterator<G>(0,      _generator); }
        constexpr auto end()   const noexcept { return GeneratorViewIterator<G>(size(), _generator); }
    
    private:
        std::size_t _size;
        std::function<output_value_type(std::size_t)> _generator;
    };

    template<class T>
    struct is_generator_view {
        constexpr static bool value = std::is_base_of_v<GeneratorViewBase, std::remove_cvref_t<T>>;
    };

    template<class T>
    constexpr static bool is_generator_view_v = is_generator_view<T>::value;

} // namespace cpt


#endif