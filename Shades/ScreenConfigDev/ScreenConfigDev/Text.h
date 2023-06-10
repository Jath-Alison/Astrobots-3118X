#pragma once

#include "displayable.h"
#include "window.h"
#include <SFML/Graphics.hpp>

extern sf::Font Calibri;

class Text : public displayable
{
public:

	Text(int x, int y, std::string text, int size, uint32_t color) : m_x(x), m_y(y), m_text(text), m_size(size), m_color(color) {}

	void display() {
		if (!m_active) { return; }
		sf::Text temp;
		if (m_size != NULL) { temp = sf::Text(sf::String(m_text), Calibri, m_size); }
		else { temp = sf::Text(sf::String(m_text), Calibri); }
		temp.setPosition(m_x, m_y);
		temp.setFillColor(sf::Color(m_color));
		window.draw(temp);
	};
private:
	int m_x, m_y;
	std::string m_text;
	uint32_t m_color;
	unsigned int m_size{NULL};
};

