#ifndef CPT_LINEDATA_H_INCLUDED
#define CPT_LINEDATA_H_INCLUDED

#include <span>
#include "../utils/error.hpp"
#include "../utils/numeric.hpp"

namespace cpt
{
    class InvalidLineDataError: public cpt::Exception {
        using Exception::Exception;
    };

    template<Numeric T, Numeric U>
    class LineData {

    public:

        LineData() = default;

        LineData(std::span<T> const &x, std::span<U> const &y)
            :_x(x), _y(y)
        {
            check();
        }

        bool empty() const noexcept { return _x.empty(); }
        auto size()  const noexcept { return _x.size();  }

        auto const &x() const noexcept { return _x; }
        auto const &y() const noexcept { return _y; }

        void check()
        {
            if (_x.size() != _y.size()) {
                throw InvalidLineDataError(
                    "Size mismatch for LineData: x is of size ", _x.size(),
                    " and y is of size ", _y.size()
                    );
            }
        }

    private:
        std::span<T> _x;
        std::span<U> _y;
    };
} // namespace cpt


#endif