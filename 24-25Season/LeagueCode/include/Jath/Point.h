#pragma once
#include "ART/Vec2.h"
#include "ART/Units.h"

namespace Jath
{
    struct Point{
        art::Vec2 m_pos;
        double m_speed;

        Point(double x, double y, double speed): m_pos(art::Vec2::XandY(x,y)), m_speed(speed){}
        Point(art::Vec2 pos, double speed): m_pos(pos), m_speed(speed){};
        Point(const Point& p): m_pos(p.m_pos), m_speed(p.m_speed){};
    };
} // namespace Jath