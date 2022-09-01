#ifndef CPT_DIRECTION_H_INCLUDED
#define CPT_DIRECTION_H_INCLUDED

#include "error.hpp"

namespace cpt
{
    enum class Anchor {
        Top, Bottom, Left, Right
    };

    class InvalidAnchorError: public cpt::Exception {
        using cpt::Exception::Exception;
    };
} // namespace cpt

#endif
