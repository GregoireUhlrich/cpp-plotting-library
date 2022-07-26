#include "geometry/point.hpp"
#include <iostream>

void print(geometry::Point<int> p)
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