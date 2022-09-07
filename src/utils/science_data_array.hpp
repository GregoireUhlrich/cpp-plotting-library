#ifndef CPT_SCIENCE_DATA_H_INCLUDED
#define CPT_SCIENCE_DATA_H_INCLUDED

#include "../math_views.hpp"
#include <concepts>
#include <optional>

namespace cpt {
template <std::floating_point T>
struct ScienceDataArray {

    ScienceDataArray()
    {
    }

    ScienceDataArray(cpt::View auto const &data_,
                     cpt::View auto const &err_plus_,
                     cpt::View auto const &err_minus_)
        : data(cpt::collect<T>(data_)),
          err_plus(cpt::collect<T>(err_plus_)),
          err_minus(cpt::collect<T>(err_minus_))
    {
    }

    ScienceDataArray(cpt::View auto const &data_, cpt::View auto const &err_)
        : ScienceDataArray(data_, err_, err_)
    {
    }

    ScienceDataArray(cpt::View auto const &data_)
        : data(cpt::collect<T>(data_)),
          err_plus(std::nullopt),
          err_minus(std::nullopt)
    {
    }

    auto size() const noexcept
    {
        return data.size();
    }

    cpt::Array<T>                data;
    std::optional<cpt::Array<T>> err_plus;
    std::optional<cpt::Array<T>> err_minus;
};
} // namespace cpt

#endif