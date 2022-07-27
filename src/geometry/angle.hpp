#pragma once

#include <cmath>

namespace geometry {

class Angle {

  private:
    double value;

    double modulo(double angle)
    {
        double _2pi = 2.0 * M_PI;
        return angle - _2pi * floor(angle / _2pi);
    }

  public:
    Angle() : value(0){};

    Angle(double angle) : value(modulo(angle))
    {
    }

    Angle &operator=(double angle)
    {
        value = modulo(angle);
        return *this;
    }

    double radian() const
    {
        return value;
    }
};

using angle = Angle;

} // namespace geometry
