#pragma once

namespace geometry {

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

    template <typename U>
    Point(const Point<U> &other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
    {
    }
};

/**
 * @brief
 *
 * @tparam T
 * @param right
 * @return constexpr Point<T>
 */
template <typename T>
constexpr Point<T> operator-(const Point<T> &right)
{
    return Point<T>(-right.x, -right.y);
}

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>
 */
template <typename T>
constexpr Point<T> operator+(const Point<T> &left, const Point<T> &right)
{
    return Point<T>(left.x + right.x, left.y + right.y);
}

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>
 */
template <typename T>
constexpr Point<T> operator-(const Point<T> &left, const Point<T> &right)
{
    return Point<T>(left.x - right.x, left.y - right.y);
}

/**
 * @brief
 *
 * @tparam U
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<U>
 */
template <typename U, typename T>
constexpr Point<U> operator*(const Point<T> &left, U right)
{
    return Point<U>(left.x * right, left.y * right);
}

/**
 * @brief
 *
 * @tparam U
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<U>
 */
template <typename U, typename T>
constexpr Point<U> operator*(U left, const Point<T> &right)
{
    return Point<U>(left * right.x, left * right.y);
}

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>&
 */
template <typename T>
constexpr Point<T> &operator+=(Point<T> &left, const Point<T> &right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>&
 */
template <typename T>
constexpr Point<T> &operator*=(Point<T> &left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>&
 */
template <typename T>
constexpr Point<T> &operator-=(Point<T> &left, const Point<T> &right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

} // namespace geometry
