#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Lexer.h"

std::map<token::type, std::string> tokenTypeStrings
{
		{token::type::ASSIGNMENT,"ASSIGNMENT"},
		{token::type::PLUS,"PLUS"},
		{token::type::MINUS,"MINUS"},
		{token::type::MULTIPLY,"MULTIPLY"},
		{token::type::DIVIDE,"DIVIDE"},
		{token::type::EXPONENT,"EXPONENT"},
		{token::type::MODULO,"MODULO"},
		{token::type::EQUALS,"EQUALS"},
		{token::type::NOT_EQUALS,"NOT_EQUALS"},
		{token::type::NOT,"NOT"},
		{token::type::GREATER_THAN,"GREATER_THAN"},
		{token::type::LESS_THAN,"LESS_THAN"},
		{token::type::GREATER_THAN_EQUAL_TO,"GREATER_THAN_EQUAL_TO"},
		{token::type::LESS_THAN_EQUAL_TO,"LESS_THAN_EQUAL_TO"},
		{token::type::INCREMENT,"INCREMENT"},
		{token::type::DECREMENT,"DECREMENT"},
		{token::type::COMMA,"COMMA"},

		{token::type::IDENTIFIER,"IDENTIFIER"},
		{token::type::QUOTES,"QUOTES"},
		{token::type::DOUBLE_QUOTES,"DOUBLE_QUOTES"},
		{token::type::STRING,"STRING"},
		{token::type::NUMBER,"NUMBER"},
		{token::type::INTEGER,"INTEGER"},
		{token::type::FLOAT,"FLOAT"},
		{token::type::DOUBLE,"DOUBLE"},
		{token::type::BOOLEAN,"BOOLEAN"},

		{token::type::SQUARE_BRACKET_OPEN,"SQUARE_BRACKET_OPEN"},
		{token::type::SQUARE_BRACKET_CLOSE,"SQUARE_BRACKET_CLOSE"},
		{token::type::CURLY_BRACKETS_OPEN,"CURLY_BRACKETS_OPEN"},
		{token::type::CURLY_BRACKETS_CLOSE,"CURLY_BRACKETS_CLOSE"},
		{token::type::PARENTHESES_OPEN,"PARENTHESES_OPEN"},
		{token::type::PARENTHESES_CLOSE,"PARENTHESES_CLOSE"},
		{token::type::COMMA,"COMMA"},
		{token::type::SEMICOLON,"SEMICOLON"},

		{token::type::KEYWORD,"KEYWORD"},
		{token::type::FUNCTION,"FUNCTION"},

		{token::type::END_OF_LINE,"END_OF_LINE"},
		{token::type::END_OF_FILE,"END_OF_FILE"},

		{token::type::ERROR,"ERROR"},
		{token::type::COMMENT,"COMMENT"}
	};

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
				std::cout << lex.getSource() << "\n\n";
                for (size_t i = 0; i < lex.size(); i++)
                {
					std::cout
						<< "Value:" 
						<< lex[i].getText() 
						<< "  Pos:"
						<< lex[i].getStartm_pos() 
						<< "  Type:"
						<< tokenTypeStrings[lex[i].getType()] 
						<< "\n";
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