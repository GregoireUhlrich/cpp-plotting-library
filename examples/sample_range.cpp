#include "math/functions.hpp"
#include "collections/range.hpp"
#include "collections/numview.hpp"
#include "math/arithmetics.hpp"
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
    auto s2 = cpt::sin(x) * cpt::sin(x);
    auto c2 = cpt::cos(x);
    print("x = ", x);
    print("s2 = ", s2);
    print("x = ", x);
    print("c2 = ", c2);
    print("c2 = ", cpt::cos(x) * cpt::cos(x) );
    std::cout.flush();
    auto one = c2 + s2;

    print("c2+s2 = ", one);

    return 0;
}