#include <SFML/Graphics.hpp>
#include "Vec2.h"
#include <iostream>

sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

std::vector<art::Vec2> points = {
    art::Vec2::XandY(100,100),
    art::Vec2::XandY(100,100),
    art::Vec2::XandY(300,800),
    art::Vec2::XandY(900,900),
};

static double curvature(art::Vec2 a, art::Vec2 b, art::Vec2 c) {
    double area = abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));

    //std::cout << (4*area / ((a.distTo(b)) * (b.distTo(c)) * (c.distTo(a)))) << std::endl;

    return 4*area/((a.distTo(b))* (b.distTo(c)) * (c.distTo(a)));
}

static art::Vec2 lerp(art::Vec2 start, art::Vec2 end, double t) {
    art::Vec2 travel = end - start;
    travel = travel * t;

    return start + travel;
}

std::vector<art::Vec2> getBezier(art::Vec2 start, art::Vec2 vel, art::Vec2 endVel, art::Vec2 end) {

    std::vector<art::Vec2> targetPoints = {
        start,
        start + vel,
        end - endVel,
        end
    };

    std::vector<art::Vec2> outputPoints;
    for (double j = 0; j <= 1.0; j += 0.01) {
        std::vector<art::Vec2> pointsCopy = targetPoints;
        while (pointsCopy.size() > 1) {
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

    sf::CircleShape shape(30.f);
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    for (size_t i = 0; i < targetPoints.size(); i++) {


        shape.setPosition(targetPoints[i].x, targetPoints[i].y);

        window.draw(shape);
    }

    return outputPoints;
}

int main()
{
    window.setFramerateLimit(60);

    sf::CircleShape shape(30.f);
    sf::CircleShape shape2(10.f);
    shape.setFillColor(sf::Color::Green);
    shape2.setFillColor(sf::Color::Cyan);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape2.setOrigin(shape2.getRadius(), shape2.getRadius());

    sf::CircleShape bot(20.f);
    bot.setOrigin(bot.getRadius(), bot.getRadius());
    bot.setFillColor(sf::Color::Yellow);

    int selectedPoint = -1;
    art::Vec2 CurrentMousePos;
    art::Vec2 PrevMousePos;
    art::Vec2 MouseVel;

    bool printed = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {

                art::Vec2 MousePos = art::Vec2::XandY(
                    event.mouseButton.x, event.mouseButton.y
                );

                if (event.mouseButton.button == sf::Mouse::Right) {
                    points.push_back(MousePos);
                }

                for (size_t i = 0; i < points.size(); i++)
                {
                    if (points[i].distTo(MousePos) < shape.getRadius()) {
                        selectedPoint = i;
                        if (event.mouseButton.button == sf::Mouse::Middle) {
                            points.erase(points.begin() + selectedPoint);
                            selectedPoint = -1;
                        }
                        
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                selectedPoint = -1;
                //points[1] = points[0] + MouseVel.normalize() * 600;
                printed = false;
                std::cout << "\n\n";
            }
        }
        
        CurrentMousePos = art::Vec2::XandY(
            sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y
        );
        MouseVel = (CurrentMousePos - PrevMousePos);

        if (selectedPoint >= 0 && selectedPoint < points.size()) {
            points[selectedPoint] = CurrentMousePos;
        }

        window.clear();
        
        sf::VertexArray connectingLine(sf::PrimitiveType::LineStrip, points.size());
        for (size_t i = 0; i < points.size(); i++)
        {
            shape.setPosition(points[i].x, points[i].y);
            window.draw(shape);
            /*connectingLine[i].position = sf::Vector2f(points[i].x, points[i].y);*/
        }

        std::vector<art::Vec2> pathPoints = getBezier(
            points[0],
            points[1],
            points[2],
            points[3]
        );

        curvature(points[0], points[1], points[2]);

        for (size_t i = 0; i < pathPoints.size(); i++)
        {
            shape2.setPosition(pathPoints[i].x, pathPoints[i].y);
            double c = 0.3;
            if (i > 0 && i < pathPoints.size() - 1) {
                c = curvature(pathPoints[i-1], pathPoints[i], pathPoints[i+1]) * 70;
                if (printed == false) {
                    std::cout << c << std::endl;
                }
            }

            if (c > 1) { c = 1.0; }

            shape2.setFillColor(
                sf::Color(c * 255.0, 50, c * 255.0)
            );

            window.draw(shape2);
        }
        if (printed == false) { printed = true; }
        
        window.draw(connectingLine);

        art::Vec2 targetPos;

        art::Vec2 botPos = art::Vec2::XandY(bot.getPosition().x, bot.getPosition().y);

        bool inside = false;
        double curve = 1;
        for (size_t i = 1; i < pathPoints.size(); i++)
        {
            if(botPos.distTo(pathPoints[i]) < 50){
                inside = true;
            }
            if (botPos.distTo(pathPoints[i]) > 50 && inside) {
                targetPos = pathPoints[i-1];
                if (i > 1 && i < pathPoints.size() - 1)
                    curve = curvature(pathPoints[i - 1], pathPoints[i], pathPoints[i + 1]) * 70.0;
                break;
            }
        }

        art::Vec2 travel = targetPos - botPos;
        travel = travel.normalize() * 10 * (1.0-curve);

        bot.setPosition(
            bot.getPosition().x + travel.x,
            bot.getPosition().y + travel.y
        );
        window.draw(bot);

        window.display();

        PrevMousePos = CurrentMousePos;
    }

    return 0;
}