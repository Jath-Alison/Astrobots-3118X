#pragma once

namespace Jath
{

    class Distance
    {
    public:
        friend Distance Pixels(double pixels);
        friend Distance Inches(double inches);
        friend Distance Feet(double feet);
        friend Distance Meters(double meters);
        friend Distance Centimeters(double centimeters);
        friend Distance Millimeters(double millimeters);
        friend Distance Tiles(double tiles);

        double pixels();
        double inches();
        double feet();
        double meters();
        double centimeters();
        double millimeters();
        double tiles();

        Distance();
        Distance(double f);

        Distance operator=(double const &f);

        operator double();

    private:
        double m_value{0.0};
    };

    Distance Pixels(double pixels);
    Distance Inches(double inches);
    Distance Feet(double feet);
    Distance Meters(double meters);
    Distance Centimeters(double centimeters);
    Distance Millimeters(double millimeters);
    Distance Tiles(double tiles);

    class Angle
    {
    public:
        friend Angle Degrees(double degrees);
        friend Angle Radians(double radians);
        friend Angle Revolutions(double revolutions);

        double degrees();
        double radians();
        double revolutions();

        Angle();
        Angle(double f);

        void constrain();

        Angle operator=(double const &f);
        operator double();

    private:
        double m_value{0.0};
    };

    Angle Degrees(double degrees);
    Angle Radians(double radians);
    Angle Revolutions(double revolutions);

}