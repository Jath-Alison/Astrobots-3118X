#include "Jath/Units.h"

namespace Jath
{
    double Distance::pixels()
    {
        return m_value;
    }

    double Distance::inches()
    {
        return m_value * 0.2f;
    }

    double Distance::feet()
    {
        return inches() / 12.f;
    }

    double Distance::meters()
    {
        return inches() * .0254f;
    }

    double Distance::centimeters()
    {
        return inches() * 2.54f;
    }

    double Distance::millimeters()
    {
        return inches() * 25.4f;
    }

    double Distance::tiles()
    {
        return inches() / 24.f;
    }

    Distance Distance::operator=(double const &f)
    {
        Distance output;
        output.m_value = f;
        return output;
    }

    Distance::operator double()
    {
        return m_value;
    }

    Distance::Distance() : m_value(0.0) {}

    Distance::Distance(double f) : m_value(f) {}

    Distance Pixels(double pixels)
    {
        Distance output;
        output.m_value = pixels;
        return output;
    }

    Distance Inches(double inches)
    {
        Distance output;
        output.m_value = inches * 5;
        return output;
    }

    Distance Feet(double feet)
    {
        Distance output;
        output.m_value = feet * 5 * 12;
        return output;
    }

    Distance Meters(double meters)
    {
        Distance output = Inches(meters);
        output.m_value = output.m_value * 39.3700787402f;
        return output;
    }

    Distance Centimeters(double centimeters)
    {
        Distance output = Inches(centimeters);
        output.m_value = output.m_value * 0.393700787402f;
        return output;
    }

    Distance Millimeters(double millimeters)
    {
        Distance output = Inches(millimeters);
        output.m_value = output.m_value * .0393700787402f;
        return output;
    }

    Distance Tiles(double tiles)
    {
        Distance output = Inches(tiles);
        output.m_value = output.m_value * 24;
        return output;
    }

    Angle Degrees(double degrees)
    {
        Angle output;
        output.m_value = degrees * 3.14159265f / 180;
        return output;
    }

    Angle Radians(double radians)
    {
        Angle output;
        output.m_value = radians;
        return output;
    }

    Angle Revolutions(double revolutions)
    {
        Angle output;
        output.m_value = revolutions * 2.f * 3.14159265f;
        return output;
    }

    Angle::Angle() : m_value(0.0) {}

    Angle::Angle(double f) : m_value(f) {}

    void Angle::constrain()
    {
        while (m_value > 3.14159265f)
        {
            m_value -= 2.f * 3.14159265f;
        }
        while (m_value < -3.14159265f)
        {
            m_value += 2.f * 3.14159265f;
        }
    }

    Angle Angle::operator=(double const &f)
    {
        Angle output;
        output.m_value = f;
        return output;
    }

    Angle::operator double()
    {
        //constrain();
        return m_value;
    }

    double Angle::degrees()
    {
        //constrain();
        return m_value * 180 / 3.14159265f;
    }

    double Angle::radians()
    {
        //constrain();
        return m_value;
    }

    double Angle::revolutions()
    {
        //constrain();
        return m_value / (3.14159265f * 2.f);
    }
}