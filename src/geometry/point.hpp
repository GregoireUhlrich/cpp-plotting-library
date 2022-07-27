#ifndef CPP_PLOT_POINT_H_INCLUDED
#define CPP_PLOT_POINT_H_INCLUDED

#include "angle.hpp"
#include <cmath>
#include <concepts>
#include <iostream>

namespace geometry {

/**
 * @brief Rounds a floating point value and return an integer.
 *
 * @details This function calls `std::round`, `std::lround` or `std::llround`
 * depending on the integral type size (`int`, `long` or `long long`).
 *
 * @tparam IntegralType Type of integer to create
 * @param value Value to round
 * @return IntegralType The rounded integer
 */
template <std::integral IntegralType>
IntegralType round(std::floating_point auto value)
{
    if constexpr (sizeof(IntegralType) == sizeof(long long)) { // long long
        return static_cast<IntegralType>(std::llround(value));
    }
    else if constexpr (sizeof(IntegralType) == sizeof(long)) { // long
        return static_cast<IntegralType>(std::lround(value));
    }
    else { // int
        return static_cast<IntegralType>(std::round(value));
    }
}

template <class T>
struct Point {

    T x;
    T y;

    /**
     * @brief Converts a floating-point `Point` structure to an integer
     * `Point`.
     *
     * @tparam U         Integer type of the resulting `Point`
     * @return Point<U>  The point rounded to the appropriate integer values.
     *
     * @note This template is only available for floating-point types.
     */
    template <class U>
    requires std::integral<U> && std::floating_point<T>
    explicit operator Point<U>() const noexcept
    {
        return Point<U>{
            .x = round<U>(x),
            .y = round<U>(y),
        };
    }

    static Point<T>
    from_angle(double       modulus,
               Angle const &angle) noexcept requires std::floating_point<T>
    {
        const auto rad = angle.radian();
        return Point<T>{
            .x = static_cast<T>(modulus * std::cos(rad)),
            .y = static_cast<T>(modulus * std::sin(rad)),
        };
    }

    /**
     * @brief Defaulted equality operator.
     */
    bool operator==(Point const &) const noexcept = default;
    /**
     * @brief Defaulted comparison operators.
     */
    bool operator<=>(Point const &) const noexcept = default;

    /**
     * @brief
     *
     * @return double
     */
    double absolute()
    {
        return std::sqrt(x * x + y * y);
    }

    /**
     * @brief
     *
     * @return Angle
     */
    Angle argument() const
    {
        return std::atan(float(y) / x);
    }

    /**
     * @brief
     *
     * @param other
     */
    void translate(const Point<T> &other)
    {
        *this += other;
    }

    /**
     * @brief
     *
     * @tparam U
     * @param factor
     */
    template <typename U>
    void scale(U factor)
    {
        x *= factor;
        y *= factor;
    }

    /**
     * @brief
     *
     * @param theta
     */
    void rotate(const Angle &theta)
    {
        T prevX = x;
        T prevY = y;

        x = prevX * std::cos(theta.radian())
            - prevY * std::sin(theta.radian());
        y = prevX * std::sin(theta.radian())
            + prevY * std::cos(theta.radian());
    }
};

// Operator definitions for Point

// Addition

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>&
 */
template <class T>
constexpr Point<T> &operator+=(Point<T> &left, Point<T> const &right)
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
template <class T>
constexpr Point<T> &operator+=(Point<T> &left, T right)
{
    left.x += right;
    left.y += right;
    return left;
}

/**
 * @brief
 *
 * @tparam T
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator+(Point<T> const &left, Point<U> const &right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x + right.x,
                                           .y = left.y + right.y};
}

/**
 * @brief
 *
 * @tparam T
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator+(Point<T> const &left, U right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x + right,
                                           .y = left.y + right};
}

/**
 * @brief
 *
 * @tparam U
 * @tparam T
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class U, class T>
constexpr auto operator+(U left, Point<T> const &right)
{
    return right + left;
}

// Substraction

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @return constexpr Point<T>
 */
template <class T>
constexpr Point<T> operator-(Point<T> const &left)
{
    return {.x = -left.x, .y = -left.y};
}

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>&
 */
template <class T>
constexpr Point<T> &operator-=(Point<T> &left, Point<T> const &right)
{
    left.x -= right.x;
    left.y -= right.y;
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
template <class T>
constexpr Point<T> &operator-=(Point<T> &left, T right)
{
    left.x -= right;
    left.y -= right;
    return left;
}

/**
 * @brief
 *
 * @tparam T
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator-(Point<T> const &left, Point<U> const &right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x - right.x,
                                           .y = left.y - right.y};
}

/**
 * @brief
 *
 * @tparam T
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator-(Point<T> const &left, U right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x - right,
                                           .y = left.y - right};
}

/**
 * @brief
 *
 * @tparam U
 * @tparam T
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class U, class T>
constexpr auto operator-(U left, Point<T> const &right)
{
    return (-right) + left;
}

// Muliplication

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>&
 */
template <class T>
constexpr Point<T> &operator*=(Point<T> &left, Point<T> const &right)
{
    left.x *= right.x;
    left.y *= right.y;
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
template <class T>
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
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator*(Point<T> const &left, Point<U> const &right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x * right.x,
                                           .y = left.y * right.y};
}

/**
 * @brief
 *
 * @tparam T
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator*(Point<T> const &left, U right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x * right,
                                           .y = left.y * right};
}

/**
 * @brief
 *
 * @tparam U
 * @tparam T
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class U, class T>
constexpr auto operator*(U left, Point<T> const &right)
{
    return right * left;
}

// Division

/**
 * @brief
 *
 * @tparam T
 * @param left
 * @param right
 * @return constexpr Point<T>&
 */
template <class T>
constexpr Point<T> &operator/=(Point<T> &left, Point<T> const &right)
{
    left.x /= right.x;
    left.y /= right.y;
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
template <class T>
constexpr Point<T> &operator/=(Point<T> &left, T right)
{
    left.x /= right;
    left.y /= right;
    return left;
}

/**
 * @brief
 *
 * @tparam T
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator/(Point<T> const &left, Point<U> const &right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x / right.x,
                                           .y = left.y / right.y};
}

/**
 * @brief
 *
 * @tparam T
 * @tparam U
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class T, class U>
constexpr auto operator/(Point<T> const &left, U right)
{
    return Point<std::common_type_t<T, U>>{.x = left.x / right,
                                           .y = left.y / right};
}

/**
 * @brief
 *
 * @tparam U
 * @tparam T
 * @param left
 * @param right
 * @return constexpr auto
 */
template <class U, class T>
constexpr auto operator/(U left, Point<T> const &right)
{
    return Point<std::common_type_t<T, U>>{.x = left / right.x,
                                           .y = left / right.y};
}

} // namespace geometry

#endif
