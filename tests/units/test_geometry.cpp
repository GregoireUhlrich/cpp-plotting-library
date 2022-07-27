#include "geometry/angle.hpp"
#include "geometry/point.hpp"
#include "gtest/gtest.h"
#include <concepts>
#include <numbers>

/**
 * @brief Helper function to assert a Point's content (x *and* y).
 *
 * @tparam T Type of numbers
 * @param p Point to assert
 * @param x Required point value for x
 * @param y Required point value for y
 *
 * @note Template specialisation only for floating-point types.
 */
template <class T>
requires std::floating_point<T>
void assert_point(geometry::Point<T> const &p, T x, T y)
{
    if constexpr (std::same_as<T, float>) {
        ASSERT_FLOAT_EQ(p.x, x);
        ASSERT_FLOAT_EQ(p.y, y);
    }
    else {
        ASSERT_DOUBLE_EQ(p.x, x);
        ASSERT_DOUBLE_EQ(p.y, y);
    }
}

/**
 * @brief Helper function to assert a Point's content (x *and* y) with
 * an acceptable error margin (for floating-point numbers).
 *
 * @tparam T Type of numbers
 * @param p   Point to assert
 * @param x   Required point value for x
 * @param y   Required point value for y
 * @param eps Absolute precision required for the assertion
 *
 * @note Template specialisation only for floating-point types.
 */
template <class T>
requires std::floating_point<T>
void assert_point_near(geometry::Point<T> const &p, T x, T y, T eps)
{
    ASSERT_NEAR(p.x, x, eps);
    ASSERT_NEAR(p.y, y, eps);
}

/**
 * @brief Helper function to assert a Point's content (x *and* y).
 *
 * @tparam T Type of numbers
 * @param p Point to assert
 * @param x Required point value for x
 * @param y Required point value for y

 * @note Template specialisation only for integral types.
 */
template <class T>
requires std::integral<T>
void assert_point(geometry::Point<T> const &p, T x, T y)
{
    ASSERT_EQ(p.x, x);
    ASSERT_EQ(p.y, y);
}

TEST(Geometry, Point)
{
    geometry::Point<int> base{.x = 2, .y = 3};
    assert_point(base, 2, 3);
    assert_point(base + geometry::Point<int>{-2, 6}, 0, 9);
    assert_point(base * 2.3, 4.6, 6.9);

    base += geometry::Point<int>{1, -1};

    assert_point(base, 3, 2);

    base *= 0;

    assert_point(base, 0, 0);
}

TEST(Geometry, Angle)
{
    geometry::Point<float> newBase{2, 3};

    geometry::Angle pi_2 = std::numbers::pi / 2;
    geometry::Angle pi   = std::numbers::pi;
    geometry::Angle pi_4 = std::numbers::pi / 4;

    newBase = geometry::Point<float>::from_angle(1.0f, pi_2);
    assert_point_near(newBase, 0.0f, 1.0f, 1e-10f);
    newBase = geometry::Point<float>::from_angle(1.0f, pi);
    assert_point_near(newBase, -1.f, 0.f, 1e-10f);
    newBase = geometry::Point<float>::from_angle(1.0f, pi_4);
    assert_point_near(
        newBase, 0.7071067811865476f, 0.7071067811865476f, 1e-10f);

    geometry::Angle a(6.59);
    geometry::Angle a_bis = 8.6555879;
    geometry::Angle b(2.34);
    geometry::Angle c(2 * std::numbers::pi);

    ASSERT_DOUBLE_EQ(a.radian(), 0.3068146928204136);
    ASSERT_DOUBLE_EQ(a_bis.radian(), 2.372402592820414);
    ASSERT_DOUBLE_EQ(b.radian(), 2.34);
    ASSERT_DOUBLE_EQ(c.radian(), 0);
}
