#ifndef CPT_TICKS_H_INCLUDED
#define CPT_TICKS_H_INCLUDED

#include "../utils/error.hpp"
#include <vector>

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

    std::vector<float> calculate_ticks(
        float xmin, 
        float xmax,
        AutoTicksConfiguration const &config = {}
        );
        
} // namespace cpt


#endif
