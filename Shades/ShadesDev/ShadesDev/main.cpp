#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "Screen.h"

sf::RenderWindow window(sf::VideoMode(480, 240), "Vexcode project");

int main()
{

    //tinyxml2::XMLDocument doc;
    //doc.LoadFile("configFile.xml");
    //tinyxml2::XMLElement* root = doc.FirstChildElement();
    //tinyxml2::XMLElement* shades = root->FirstChildElement("shades");
    ////tinyxml2::XMLElement* screens = shades->FirstChildElement("screen");
    //
    //sds::Screen testScreen(shades);

    sds::Screen::initialize();

    sds::Screen::load("home");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){}
                //testScreen.
        }

        window.clear();
        sds::Screen::display();
        window.display();
    }

    return 0;
}