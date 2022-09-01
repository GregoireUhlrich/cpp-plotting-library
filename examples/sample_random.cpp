#include "math_views.hpp"


int main() {

    cpt::RandomDevice rand;
    cpt::print(rand.rand_int(50, 0, 10));
    cpt::print(rand.rand_int<long unsigned int>(50, 0, 10));
    cpt::print(rand.rand_real(50, -1.f, 1.f));
    cpt::print(rand.rand_real<double>(50, -1.f, 1.f));
    std::cout << rand.rand_int(0, 10) << std::endl;
    std::cout << rand.rand_real(-1.f, 1.f) << std::endl;

    return 0;
}
