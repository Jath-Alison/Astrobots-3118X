#include <SFML/Graphics.hpp>
#include "Vec2.h"

sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

std::vector<art::Vec2> points = {
    art::Vec2::XandY(100,100),
    art::Vec2::XandY(100,100),
    art::Vec2::XandY(300,800),
    art::Vec2::XandY(900,900),
};

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

    int selectedPoint = -1;
    art::Vec2 CurrentMousePos;
    art::Vec2 PrevMousePos;
    art::Vec2 MouseVel;

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

        for (size_t i = 0; i < pathPoints.size(); i++)
        {

            shape2.setPosition(pathPoints[i].x, pathPoints[i].y);
            window.draw(shape2);
        }
        
        window.draw(connectingLine);

        window.display();

        PrevMousePos = CurrentMousePos;
    }

    return 0;
}