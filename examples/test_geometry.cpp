#include "geometry/point.hpp"
#include <iostream>

void print2D(geometry::_2D::Point<int> p)
{
    std::cout << "2D point : ";
    std::cout << "(" << p.x << ":" << p.y << ")" << std::endl;
}

void print3D(geometry::_3D::Point<int> p)
{
    std::cout << "3D point : ";
    std::cout << "(" << p.x << ":" << p.y << ":" << p.z << ")" << std::endl;
}

int main()
{

    print2D(geometry::_2D::Point(2, 3));
    print2D(geometry::_2D::Point(-2, 6));
    print2D(geometry::_2D::Point(-1, 0));

    print3D(geometry::_3D::Point(2, 3, 6));
    print3D(geometry::_3D::Point(-2, 6, 9));
    print3D(geometry::_3D::Point(-1, 0, 1));

    return 0;
}