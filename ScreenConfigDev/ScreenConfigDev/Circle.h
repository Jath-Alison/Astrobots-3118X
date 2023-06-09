#pragma once

#include "displayable.h"
#include "window.h"
#include <SFML/Graphics.hpp>

class Circle : public displayable
{
public:

	Circle(int x, int y, int radius, uint32_t color) : m_x(x), m_y(y), m_radius(radius), m_color(color) {}

	void display() {
		if (!m_active) { return; }
		sf::CircleShape temp(m_radius,100);
		temp.setPosition(m_x- m_radius, m_y- m_radius);
		temp.setFillColor(sf::Color(m_color));
		window.draw(temp);
	};
private:
	int m_x, m_y;
	int m_radius;
	uint32_t m_color;
};

