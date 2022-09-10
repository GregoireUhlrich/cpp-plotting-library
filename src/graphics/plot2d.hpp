#ifndef CPT_PLOT2D_H_INCLUDED
#define CPT_PLOT2D_H_INCLUDED

#include "../utils/data2d.hpp"

namespace cpt
{
    struct Plot2DConfig {

    };

    class Plot2D {
    public:
        Plot2D(
            cpt::ArrayRange const &x,
            cpt::ArrayRange const &y,
            Plot2DConfig    const &config_ = {})
            :_data(x, y),
             config(config_)
        {

        }

    public:
        Plot2DConfig config;

    private:
        Data2D<float> _data;
    };
} // cpt

#endif
