#ifndef CPT_RANDOM_H_INCLUDED
#define CPT_RANDOM_H_INCLUDED

#include <random>
#include <concepts>
#include "generator_view.hpp"

namespace cpt {

    class rand {
    public:

        rand() = delete;

        template <std::integral IntegralType = int>
        static 
        IntegralType rand_int(
            std::integral auto first, 
            std::integral auto last
            )
        {
            std::uniform_int_distribution<IntegralType> distrib(
                static_cast<IntegralType>(first), 
                static_cast<IntegralType>(last));
            return distrib(rand::_device);
        }

        template <std::floating_point FloatingType = float>
        static 
        FloatingType rand_real(
            std::floating_point auto first, 
            std::floating_point auto last
            )
        {
            std::uniform_real_distribution<FloatingType> distrib(
                static_cast<FloatingType>(first), 
                static_cast<FloatingType>(last));
            return distrib(rand::_device);
        }

        template<class RandomDevice, class Distribution>
        static
        auto random(
            std::size_t n, 
            RandomDevice &device, 
            Distribution &distrib
            )
        {
            return cpt::GeneratorView {
                n, 
                [&](std::size_t)
                {
                    return distrib(device);
                }
            };
        }

    private:
        static inline std::random_device _device;
    };

} // namespace cpt

#endif
