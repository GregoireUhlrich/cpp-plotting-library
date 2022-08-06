#include "views.hpp"

// Utilities to apply a threshold on very small floating-point values
constexpr static double threshold = 1e-10;

auto min_threshold = [](auto val)
{
    return std::abs(val) < threshold ? 0 : val;
};

using namespace cpt;

int main() {

    const auto x = range(10);

    ////
    // Test [cos(x)^2 + sin(x)^2 == 1]
    auto y1 = 1 - (cos(x)*cos(x) + sin(x)*sin(x)); // No calculation is done here!

    std::cout << "Should be 0 : ";
    print(apply_on_view(y1, min_threshold)); // Apply a threshold to detect 'almost 0' values
    //
    ////

    ////
    // Test [1 + tan(x)^2 == 1 / cos(x)^2 ]
    auto y2 = 1 / pow(cos(x), 2);
    auto y3 = 1 + pow(tan(x), 2);

    std::cout << "Should be 0 : ";
    print(apply_on_view(y2 - y3, min_threshold)); // Apply a threshold to detect 'almost 0' values
    //
    ////
    print(linspace(0., 10, 10l));
    print(linspace<double>(0., 10., 10u, {.end_point = false}));
    print(logspace<double>(0., 10., 10u));
    print(logspace<double>(0., 10., 10u, {.end_point = false}));
    print(logspace<double>(0., 10., 10u, {.base = 2}));
    print(atan2(y2, y2));
    print(exp2(x));

    print(collect(y2 - y3));
    print(collect<double>(y2 - y3));
    print(collect<int>(y2 - y3));
}