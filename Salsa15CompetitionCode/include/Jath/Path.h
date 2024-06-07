#pragma once

#include <vector>
#include "Jath\Point.h"

namespace Jath
{
    
    struct Path{

        Point getClosestPoint(Vec2 pos);
        Point getLookahead(Vec2 pos, Distance lookaheadDist);

        Path(std::vector<Point> points);
        static Path cm(std::vector<Point> points);
        static Path in(std::vector<Point> points);

        Path(const Path& p);

        std::vector<Point> m_points;
    };

} // namespace Jath
