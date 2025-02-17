#include "ART/Path.h"

namespace art
{

    Path::Path(std::vector<Point> points) : m_points(points) {}

    Path Path::cm(std::vector<Point> points)
    {
        Path p = Path(points);
        for (size_t i = 0; i < p.m_points.size(); i++)
        {
            p.m_points[i].m_pos.x = art::Centimeters(p.m_points[i].m_pos.x);
            p.m_points[i].m_pos.y = art::Centimeters(p.m_points[i].m_pos.y);
        }
        return p;
    }

    Path Path::in(std::vector<Point> points)
    {
        Path p = Path(points);
        for (size_t i = 0; i < p.m_points.size(); i++)
        {
            p.m_points[i].m_pos.x = art::Inches(p.m_points[i].m_pos.x);
            p.m_points[i].m_pos.y = art::Inches(p.m_points[i].m_pos.y);
        }
        return p;
    }

    Path::Path(const Path &p)
    {
        for (size_t i = 0; i < p.m_points.size(); i++)
        {
            m_points.push_back(
                Point(p.m_points[i].m_pos, p.m_points[i].m_speed));
        }
    }

    void Path::calculateSpeeds(double minSpeed, double factor)
    {
        for (size_t i = 0; i < m_points.size(); i++)
        {
            double curve = 1.0;
            double calcSpeed = 100.0;

            if (i > 1 && i < m_points.size() - 1)
            {
                curve = curvature(m_points[i - 1].m_pos, m_points[i].m_pos, m_points[i + 1].m_pos) * factor;
            }

            calcSpeed = calcSpeed * std::max(1.0 - curve, 0.0);

            m_points[i].m_speed = std::max(calcSpeed, minSpeed);
        }

        m_points.back().m_speed = 0;
    }

    Point Path::getClosestPoint(art::Vec2 pos)
    {
        Point closest = m_points.front();
        // Distance dist = pos.distTo(closest.m_pos);

        for (Point &p : m_points)
        {
            if (pos.distTo(p.m_pos) < pos.distTo(closest.m_pos))
            {
                closest = p;
            }
        }

        return closest;
    }

    Point Path::getLookahead(art::Vec2 pos, art::Length lookaheadDist)
    {
        bool lastIn = false;
        Point p(m_points.front());
        for (size_t i = m_points.size() - 1; i >= 0; i--)
        {
            p = m_points[i];

            if (pos.distTo(m_points[i].m_pos) < lookaheadDist)
            {
                return p;//
                lastIn = true;
            }
            else
            {
                if (lastIn == true)
                {
                    return p;
                }
                lastIn = false;
            }
        }
        if (lastIn)
        {
            return m_points.back();
        }
        // return Point(Vec2::XandY(0,0),0);
        return getClosestPoint(pos);
    }

    double curvature(art::Vec2 a, art::Vec2 b, art::Vec2 c)
    {
        double area = std::abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));

        return 4.0 * area / ((a.distTo(b)) * (b.distTo(c)) * (c.distTo(a)));
    }

    Path bezier(std::vector<art::Vec2> points, double resolution)
    {
        std::vector<art::Vec2> targetPoints = points;

        std::vector<art::Vec2> outputPoints;
        for (double j = 0; j <= 1.0; j += 1.0 / resolution)
        {
            std::vector<art::Vec2> pointsCopy = targetPoints;
            while (pointsCopy.size() > 1)
            {
                std::vector<art::Vec2> out;

                for (size_t i = 0; i < pointsCopy.size() - 1; i++)
                {
                    art::Vec2 lerpedPos = lerp(pointsCopy[i], pointsCopy[i + 1], j);
                    out.push_back(lerpedPos);
                }

                pointsCopy = out;
            }

            outputPoints.push_back(pointsCopy.front());
        }

        double curve = 0.0;

        std::vector<Point> pathPoints;
        for (size_t i = 0; i < outputPoints.size(); i++)
        {
            Point p(outputPoints[i].x, outputPoints[i].y, 100);
            pathPoints.push_back(p);
        }

        return Path(pathPoints);
    }

}