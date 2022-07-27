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
    base.translate(geometry::Point(2, 4));
    print(base, "(5, 6)");

    base *= 0;

    print(base, "(0,0)");
    print(base + geometry::Point(-2, 6), "(-2,6)");
    print(base * 2.3, "(0,0)");

    geometry::Point<float> newBase(2, 3);

    geometry::angle pi_2 = M_PI_2;
    geometry::angle pi   = M_PI;
    geometry::angle pi_4 = M_PI_4;

    newBase = geometry::Point(1.0, pi_2);
    print(newBase, "(0,1)");
    newBase = geometry::Point(1.0, pi);
    print(newBase, "(-1,0)");
    newBase = geometry::Point(1.0, pi_4);
    print(newBase, "(0.7071067811865476,0.7071067811865476)");
    ////////////////////////////////////////////////////////////////////////////

    geometry::angle a(6.59);
    geometry::angle a_bis = 8.6555879;
    geometry::angle b(2.34);
    geometry::angle c(2 * M_PI);

    print(a, "0.3068146928204136");
    print(a_bis, "2.372402592820414");
    print(b, "2.34");
    print(c, "0");

    return 0;
}