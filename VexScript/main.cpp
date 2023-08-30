#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lexer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Lexer lex;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                // Close the window
                std::cout << lex.getSource() << std::endl;
                for (size_t i = 0; i < lex.size(); i++)
                {
                    std::cout << lex[i].getText() << "\n";
                }
            }
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                // Close the window
                lex.loadFromFile("Source.txt");
                lex.tokenize();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}