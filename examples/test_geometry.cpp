#include "geometry/point.hpp"
#include <iostream>
#include <string>

template <typename T>
void print(geometry::Point<T> p, std::string const message)
{
    std::cout << "2D point : ";
    std::cout << "(" << p.x << "," << p.y << ") --> " << message << std::endl;
}

int main()
{

    geometry::Point<int> base(2, 3);

    print(base, "(2,3)");
    print(base + geometry::Point(-2, 6), "(0,9)");
    print(base * 2.3, "(4.6,6.9)");

    base += geometry::Point(1, -1);

    print(base, "(3,2)");
    print(base + geometry::Point(-2, 6), "(1,8)");
    print(base * 2.3, "(6.9, 4.6)");
    print(base / 2., "(1.5, 1)");

    base *= 0;

    print(base, "(0,0)");
    print(base + geometry::Point(-2, 6), "(-2,6)");
    print(base * 2.3, "(0,0)");

    return 0;
}