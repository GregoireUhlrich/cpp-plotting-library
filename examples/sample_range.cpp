#include "math/function.hpp"
#include "collections/range.hpp"
#include <iostream>

template<std::ranges::range Range>
void print(char const *msg, Range const &col)
{
    std::cout << msg;
    std::cout << "[ ";
    for (auto val : col) {
        std::cout << val << " ";
    }
    std::cout << "]\n";
}

int main() {

    auto x = cpt::range(10, 50);
    auto y = cpt::cos(x);

    print("x = ", x);
    print("y = ", y);

    return 0;
}