#pragma once

#include <vector>
#include "ART/Jath/Point.h"

namespace Jath
{
    
    struct Path{

        Point getClosestPoint(art::Vec2 pos);
        Point getLookahead(art::Vec2 pos, art::Length lookaheadDist);

        Path();
        Path(std::vector<Point> points);
        static Path cm(std::vector<Point> points);
        static Path in(std::vector<Point> points);

        Path(const Path& p);

        void calculateSpeeds(double minSpeed, double factor);

        std::vector<Point> m_points;
    };

    double curvature(art::Vec2 a, art::Vec2 b, art::Vec2 c);

    Path bezier(std::vector<art::Vec2> points, double resolution);

} // namespace Jath
