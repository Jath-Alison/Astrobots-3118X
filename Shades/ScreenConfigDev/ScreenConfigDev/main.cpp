#include <SFML/Graphics.hpp>

#include "Screen.h"

sf::Font Calibri;

Box Box1("",10, 10, 100, 200, 0x33FF99FF);
Box Box2("",110, 10, 100, 200, 0xFF3399FF);
Box Box3("",210, 10, 100, 200, 0xFF9933FF);

Circle Cir1("",125+31, 250, 125, 0xFF000077);
Circle Cir2("",250, 250+125, 125, 0x00FF0077);
Circle Cir3("",375-31, 250, 125, 0x0000FF77);

std::vector <std::shared_ptr<displayable>> displayables{
    std::make_shared<Box>("",10, 10, 100, 200, 0x33FF99FF),
    std::make_shared<Circle>("",125 + 31, 250, 125, 0xFF000077)
};

sf::RenderWindow window(sf::VideoMode(480, 240), "Vexcode project");

int main()
{
    Calibri.loadFromFile("Calibri Light.ttf");

    tinyxml2::XMLDocument doc;
    doc.LoadFile("configFile.xml");
    tinyxml2::XMLElement* root = doc.FirstChildElement();
    tinyxml2::XMLElement* shades = root->FirstChildElement("shades");
    tinyxml2::XMLElement* screens = shades->FirstChildElement("screen");
 

    //Screen testScreen(displayables);
    Screen testScreen(screens);

    screens = screens->NextSiblingElement();

    window.setFramerateLimit(30);

    int counter = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                    
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
                counter++;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                testScreen.load(screens);
                //testScreen.clear();
            }
        }

        if (testScreen.getElementById("title") != nullptr) { testScreen.getElementById("title")->setText("Counter: %d", counter); }

        window.clear();
        testScreen.display();
        window.display();
    }

    return 0;
}