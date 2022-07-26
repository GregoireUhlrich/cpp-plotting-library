#pragma once

namespace geometry {

namespace _2D {

template <typename T>
struct Point {

    T x;
    T y;

    Point() : x(0), y(0)
    {
    }

    Point(T x, T y) : x(x), y(y)
    {
    }
};

} // namespace _2D

namespace _3D {

template <typename T>
struct Point {

    T x;
    T y;
    T z;

    Point() : x(0), y(0), z(0)
    {
    }

    Point(T x, T y, T z) : x(x), y(y), z(z)
    {
    }
};

} // namespace _3D

} // namespace geometry
