#ifndef CPT_TICKS_H_INCLUDED
#define CPT_TICKS_H_INCLUDED

#include "../math_views/array_view.hpp"
#include "../utils/error.hpp"

namespace cpt
{
    class InvalidTicksConfiguration: public cpt::Exception {
        using cpt::Exception::Exception;
    };

    struct AutoTicksConfiguration {
        int min_n_ticks   = 2;
        int ideal_n_ticks = 6;
        int max_n_ticks   = 10;
    };

    cpt::Array<float> calculate_ticks(
        float xmin, 
        float xmax,
        AutoTicksConfiguration const &config = {}
        );
        
} // namespace cpt


#endif
