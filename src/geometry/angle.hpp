#pragma once

#include <cmath>

namespace geometry {

class Angle {

  private:
    double value;

    /**
     * @brief
     *
     * @param angle
     * @return double
     */
    double modulo(double angle)
    {
        double _2pi = 2.0 * M_PI;
        return angle - _2pi * floor(angle / _2pi);
    }

  public:
    /**
     * @brief Construct a new Angle object
     *
     */
    Angle() : value(0){};

    /**
     * @brief Construct a new Angle object
     *
     * @param angle
     */
    Angle(double angle) : value(modulo(angle))
    {
    }

    /**
     * @brief
     *
     * @param angle
     * @return Angle&
     */
    Angle &operator=(double angle)
    {
        value = modulo(angle);
        return *this;
    }

    /**
     * @brief
     *
     * @return double
     */
    double radian() const
    {
        return value;
    }
};

} // namespace geometry
