#include "geometry/angle.hpp"
#include "geometry/point.hpp"
#include <iostream>
#include <string>

template <typename T>
void print(const geometry::Point<T> &p, const std::string &message)
{
    std::cout << "2D point : ";
    std::cout << "(" << p.x << "," << p.y << ") --> " << message << std::endl;
}

void print(const geometry::Angle &p, const std::string &message)
{
    std::cout << "Angle : ";
    std::cout << p.radian() << " --> " << message << std::endl;
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

    ////////////////////////////////////////////////////////////////////////////

    geometry::Angle a(6.59);
    geometry::Angle a_bis = 8.6555879;
    geometry::Angle b(2.34);
    geometry::Angle c(2 * M_PI);

    print(a, "0.3068146928204136");
    print(a_bis, "2.372402592820414");
    print(b, "2.34");
    print(c, "0");

    return 0;
}