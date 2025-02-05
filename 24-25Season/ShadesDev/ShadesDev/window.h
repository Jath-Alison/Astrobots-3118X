#pragma once
#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;

enum ClickTypes {
	PRESSED,
	PRESSING,
	RELEASED,
	NONE
};