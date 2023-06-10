#pragma once

#include "displayable.h"
#include "window.h"
#include <SFML/Graphics.hpp>

class Box : public displayable
{
public:

	Box(int x, int y, int width, int height, uint32_t color) : m_x(x), m_y(y), m_width(width), m_height(height), m_color(color){}

	void display() {
		if (!m_active) { return; }
		sf::RectangleShape temp(sf::Vector2f(m_width, m_height));
		temp.setPosition(m_x, m_y);
		temp.setFillColor(sf::Color(m_color));
		window.draw(temp);
	};
private:
	int m_x, m_y;
	int m_width, m_height;
	uint32_t m_color;
};

