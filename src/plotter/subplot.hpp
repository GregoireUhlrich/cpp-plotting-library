#ifndef CPT_SUBPLOT_H_INCLUDED
#define CPT_SUBPLOT_H_INCLUDED

#include "subplot_texture.hpp"

namespace cpt
{
    class Subplot: public SubplotTexture {
    public:
        Subplot()               = default;
        Subplot(Subplot const&) = delete;
        Subplot(Subplot &&)     = default;
    };
} // namespace cpt

#endif