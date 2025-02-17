#include <SFML/Graphics.hpp>
#include "Shades.h"

sf::RenderWindow window(sf::VideoMode(480, 272), "Vexcode project");

sf::Font Calibri;
int main()
{

    Calibri.loadFromFile("Calibri Light.ttf");

    //tinyxml2::XMLDocument doc;
    //doc.LoadFile("configFile.xml");
    //tinyxml2::XMLElement* root = doc.FirstChildElement();
    //tinyxml2::XMLElement* shades = root->FirstChildElement("shades");
    ////tinyxml2::XMLElement* screens = shades->FirstChildElement("screen");
    //
    //sds::Screen testScreen(shades);

    sds::Screen::initialize();

    sds::Screen::load("home");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                sds::Screen::handleClick(event.mouseButton.x, event.mouseButton.y);
        }

        sf::Vector2i pos = sf::Mouse::getPosition(window);

        sds::Screen::setData("dataOne", std::to_string(pos.x));
        sds::Screen::setData("dataTwo", std::to_string(pos.y));

        //sds::Screen::display();
        sds::Screen::waitForDisplay();
        
    }

    return 0;
}