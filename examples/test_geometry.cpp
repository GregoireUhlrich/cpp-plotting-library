#include "geometry/point.hpp"
#include <iostream>

template <typename T>
void print(geometry::Point<T> p)
{
    std::cout << "2D point : ";
    std::cout << "(" << p.x << ":" << p.y << ")" << std::endl;
}

int main()
{

    geometry::Point<int> base(2, 3);

    print(base);
    print(base + geometry::Point(-2, 6));
    print(base * 2.3);

    return 0;
}