#ifndef CPT_SCIENCE_DATA_H_INCLUDED
#define CPT_SCIENCE_DATA_H_INCLUDED

#include "../math_views.hpp"
#include "../utils/error.hpp"
#include <concepts>
#include <optional>
#include <span>

namespace cpt {

class InvalidData2DError: public cpt::Exception 
    using cpt::Exception::Exception;
};

template <std::floating_point T>
class Data2D {

public:

    Data2D()
    {
    }

    Data2D(cpt::ArrayRange auto const &x,
           cpt::ArrayRange auto const &y)
    {
        set(x, y);
    }

    bool empty() const noexcept {
        return _x.empty();
    }

    std::size_t size() const noexcept
    {
        return _x.size();
    }

    std::span<T> get_x() const noexcept {
        return _x;
    }

    std::span<T> get_y() const noexcept {
        return _y;
    }

    void set(
        cpt::ArrayRange auto const &x,
        cpt::ArrayRange auto const &y
        )
    {
        if (x.size() != y.size()) {
            throw InvalidData2DError(
                "x and y views should have the same size, "
                x.size(), " and ", y.size(), " given."
            );
        }
        _x = cpt::collect<T>(x);
        _y = cpt::collect<T>(y);
    }


private:
    cpt::Array<T> _x;
    cpt::Array<T> _y;
};
} // namespace cpt

#endif
