#include "math_views.hpp"


int main() {

    std::random_device rd;
    std::uniform_int_distribution<int> i(0, 10);
    std::uniform_real_distribution<float> r(-1.f, 1.f);

    cpt::print(cpt::rand::random(50, rd, i));
    cpt::print(cpt::rand::random(50, rd, r));

    return 0;
}
