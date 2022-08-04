#include "array/array.hpp"
#include "array/array_view.hpp"
#include "array/math.hpp"
#include "array/builtins.hpp"
#include "array/io.hpp"
#include "array/view.hpp"
#include "array/collect.hpp"
#include "array/arithmetics.hpp"

// Utilities to apply a threshold on very small floating-point values
constexpr static double threshold = 1e-10;

auto min_threshold = [](auto val)
{
    return std::abs(val) < threshold ? 0 : val;
};

using namespace cpt;

int main() {

    const auto x_data = range(10);    // Store the data in a variable first
    auto x            = view(x_data); // Then we can take the view and work from there

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
}