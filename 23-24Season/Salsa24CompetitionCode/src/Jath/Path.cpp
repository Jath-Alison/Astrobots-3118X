#include "Jath\Path.h"


namespace Jath{

    Path::Path(std::vector<Point> points): m_points(points){}

    Path Path::cm(std::vector<Point> points)
    {
        Path p = Path(points);
        for (size_t i = 0; i < p.m_points.size(); i++)
        {
            p.m_points[i].m_pos.x = Centimeters(p.m_points[i].m_pos.x);
            p.m_points[i].m_pos.y = Centimeters(p.m_points[i].m_pos.y);
        }
        return p;
    }

    Path Jath::Path::in(std::vector<Point> points)
    {
        Path p = Path(points);
        for (size_t i = 0; i < p.m_points.size(); i++)
        {
            p.m_points[i].m_pos.x = Inches(p.m_points[i].m_pos.x);
            p.m_points[i].m_pos.y = Inches(p.m_points[i].m_pos.y);
        }
        return p;
    }

    Jath::Path::Path(const Path &p)
    {
        for (size_t i = 0; i < p.m_points.size(); i++)
        {
            m_points.push_back(
                Point(p.m_points[i].m_pos,p.m_points[i].m_speed)
            );
        }
        
        
    }

    Point Path::getClosestPoint(Vec2 pos)
    {
        Point closest = m_points.front();
        // Distance dist = pos.distTo(closest.m_pos);

        for (Point& p : m_points)
        {
            if(pos.distTo(p.m_pos) < pos.distTo(closest.m_pos)){
                closest = p;
            }
            
        }
        
        return closest;
    }

    Point Path::getLookahead(Vec2 pos, Distance lookaheadDist)
    {
        bool lastIn = false;
        Point p(m_points.front());
        for (size_t i = 0; i < m_points.size(); i++)
        {
            Point p = m_points[i];
            
            
            if(pos.distTo(m_points[i].m_pos) < lookaheadDist){
                lastIn = true;
            }else{
                if(lastIn == true){
                    return p;
                }
                lastIn = false;
            }
            
        }
        if(lastIn){
            return m_points.back();
        }
        // return Point(Vec2::XandY(0,0),0);
        return getClosestPoint(pos);
    }
}