#include "array/array.hpp"
#include "array/array_view.hpp"
#include "array/math.hpp"
#include "array/builtins.hpp"
#include "array/io.hpp"
#include "array/view.hpp"

auto get_view(auto const &x)
{
   return cpt::ArrayView{x} | std::views::transform([](float x) { return x + 1; });
}

int main() {

    cpt::Array<int> arr1 = cpt::range<int>(10);
    const cpt::Array<int> arr2 = cpt::range<int>(10);
    const auto arr3 = {1, 2, 3};
    const int arr4[] = {4, 5, 6};
    std::vector<float> arr5 = {1.1, 2.2, 3.3}; 
    auto arr5_times_2 = get_view(arr5);
    const char str[] = "Hello, World!";
    cpt::print(arr1);
    cpt::print(arr2);
    cpt::print(arr3);
    cpt::print(arr4);
    cpt::print(arr5);
    cpt::print(str);
    cpt::print(arr5_times_2);
    cpt::print(cpt::ArrayView{arr5} | std::views::transform([](float x) { return x + 1; }));
    auto c = cpt::view(arr5);
    auto c2 = cpt::view(cpt::ArrayView(arr5));
    auto cc = cpt::view(cpt::cos(c));
    cpt::print(cc);
    cpt::print(c2);
    cpt::print(cpt::cos(cpt::MathView{cpt::ArrayView{arr5}}));
    //cpt::print(cpt::cos(cpt::MathView{arr5}));

    return 0;
}