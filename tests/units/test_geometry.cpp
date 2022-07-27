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

TEST(Geometry, point_base)
{
    geometry::Point<int>    p1{.x = 2, .y = -3};
    geometry::Point<double> p2{.x = 2.6, .y = -1.4e5};
    assert_point(p1, 2, -3);
    assert_point(p2, 2.6, -1.4e5);
    assert_point(static_cast<geometry::Point<long>>(p2), 3l, -140'000l);
}

TEST(Geometry, point_addition)
{
    geometry::Point<int>   i1{4, 6};
    geometry::Point<int>   i2{-2, 0};
    geometry::Point<float> f1{-2.7f, -1.5f};
    geometry::Point<float> f2{-9.0f, 0.5f};

    assert_point(i1 + i2, 2, 6);
    assert_point(i2 + i1, 2, 6);
    assert_point(i1 + 5, 9, 11);
    assert_point(5 + i1, 9, 11);
    i1 += 5;
    i1 += i2;
    assert_point(i1, 7, 11);

    assert_point(f1 + f2, -11.7f, -1.f);
    assert_point(f2 + f1, -11.7f, -1.f);
    assert_point(f1 + 5.0f, 2.3f, 3.5f);
    assert_point(5.0f + f1, 2.3f, 3.5f);
    f1 += f2;
    f1 += 6.f;
    assert_point(f1, -5.7f, 5.0f);
}

TEST(Geometry, point_substraction)
{
    geometry::Point<int>   i1{4, 6};
    geometry::Point<int>   i2{-2, 0};
    geometry::Point<float> f1{-2.7f, -1.5f};
    geometry::Point<float> f2{-9.0f, 0.5f};

    assert_point(i1 - i2, 6, 6);
    assert_point(i2 - i1, -6, -6);
    assert_point(i1 - 5, -1, 1);
    assert_point(5 - i1, 1, -1);
    i1 -= 5;
    i1 -= i2;
    assert_point(i1, 1, 1);

    assert_point(f1 - f2, 6.3f, -2.f);
    assert_point(f2 - f1, -6.3f, 2.f);
    assert_point(f1 - 5.0f, -7.7f, -6.5f);
    assert_point(5.0f - f1, 7.7f, 6.5f);
    f1 -= f2;
    f1 -= 6.f;
    assert_point_near(f1, 0.3f, -8.0f, 1e-5f);
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
