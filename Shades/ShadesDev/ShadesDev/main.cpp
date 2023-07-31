#include <SFML/Graphics.hpp>
#include "Shades.h"

sf::RenderWindow window(sf::VideoMode(480, 240), "Vexcode project");

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

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                sds::Screen::handleClick(event.mouseButton.x, event.mouseButton.y);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
                sds::Screen::executeCallback("home");
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B)
                sds::Screen::executeCallback("first");
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                sds::Screen::getElement <sds::Text>("title")->setText("It works!!!");
            }
        }

        window.clear();
        sds::Screen::display();
        window.display();
    }

    return 0;
}