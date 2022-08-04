#ifndef CPT_ARITHMETICS_H_INCLUDED
#define CPT_ARITHMETICS_H_INCLUDED

#include "../utils/numeric.hpp"
#include "../collections/numview.hpp"
#include "../utils/error.hpp"
#include "../collections/zipview.hpp"

namespace cpt
{
    template<cpt::NumRange TRange, cpt::NumRange URange>
    auto operator+(NumView<TRange> const &t, NumView<URange> const &u)
    {
        return NumView{
            std::move(ZipView{t, u}) | std::views::transform(
                [](auto const &p) {
                    return p.first + p.second;
                }
            )
        };
    }

    template<cpt::NumRange TRange, cpt::NumRange URange>
    auto operator*(NumView<TRange> const &t, NumView<URange> const &u)
    {
        return NumView{
            std::move(ZipView{t, u}) | std::views::transform(
                [](auto const &p) {
                    return p.first * p.second;
                }
            )
        };
    }

    template<cpt::NumRange Range>
    auto operator-(NumView<Range> const &view)
    {
        return NumView{
            view | std::views::transform(
                [](auto val) {
                    return -val;
                }
            )
        };
    }
} // namespace cpt


#endif