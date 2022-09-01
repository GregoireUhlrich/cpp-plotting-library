#ifndef CPT_RANDOM_H_INCLUDED
#define CPT_RANDOM_H_INCLUDED

#include <random>
#include <concepts>
#include "generator_view.hpp"

namespace cpt {

    class RandomDevice {
    public:

        RandomDevice()                     = default;
        RandomDevice(RandomDevice const &) = delete;
        RandomDevice(RandomDevice &&)      = delete;

        template <std::integral IntegralType = int>
        auto rand_int(
            std::size_t        n,
            std::integral auto first, 
            std::integral auto last
            )
        {
            std::uniform_int_distribution<IntegralType> distrib(
                static_cast<IntegralType>(first), 
                static_cast<IntegralType>(last));
            return this->rand(n, distrib);
        }

        template <std::integral IntegralType = int>
        IntegralType rand_int(
            std::integral auto first, 
            std::integral auto last
            )
        {
            auto view = this->rand_int<IntegralType>(1, first, last);
            return *view.begin();
        }

        template <std::floating_point FloatingType = float>
        auto rand_real(
            std::size_t              n,
            std::floating_point auto first, 
            std::floating_point auto last
            )
        {
            std::uniform_real_distribution<FloatingType> distrib(
                static_cast<FloatingType>(first), 
                static_cast<FloatingType>(last));
            return this->rand(n, distrib);
        }

        template <std::floating_point FloatingType = float>
        FloatingType rand_real(
            std::floating_point auto first, 
            std::floating_point auto last
            )
        {
            auto view = this->rand_real<FloatingType>(1, first, last);
            return *view.begin();
        }

        template<class Distribution>
        auto rand(
            std::size_t    n, 
            Distribution &&distrib
            )
        {
            return cpt::GeneratorView {
                n, 
                [this, distrib=distrib](std::size_t) mutable
                {
                    return distrib(this->_device);
                }
            };
        }

    private:
        std::random_device _device;
    };

} // namespace cpt

#endif
