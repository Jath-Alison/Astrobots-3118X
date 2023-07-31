#pragma once

#include "displayable.h"
#include "window.h"
#include <SFML/Graphics.hpp>

namespace sds {

	class Circle : public displayable
	{
	public:

		Circle(std::string id, int x, int y, int radius, uint32_t color) :displayable(id), m_x(x), m_y(y), m_radius(radius), m_color(color) {}

		void display() {
			sf::CircleShape temp(m_radius, 100);
			temp.setPosition(m_x - m_radius, m_y - m_radius);
			temp.setFillColor(sf::Color(m_color));
			window.draw(temp);
		};

		bool checkBounds(int x, int y) {
			if (sqrt(pow(m_x - x, 2) + pow(m_y - y, 2)) < m_radius) {
				return true;
			}
			return false;
		}
	private:
		int m_x, m_y;
		int m_radius;
		uint32_t m_color;
	};


}