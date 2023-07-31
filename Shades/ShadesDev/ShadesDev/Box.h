#pragma once

#include "displayable.h"
#include "window.h"
#include <SFML/Graphics.hpp>

namespace sds {

	class Screen;

	class Box : public displayable
	{
	public:

		Box(std::string id, int x, int y, int width, int height, uint32_t color) :displayable(id), m_x(x), m_y(y), m_width(width), m_height(height), m_color(color) {}

		void display() {
			//if (!m_active) { return; }
			sf::RectangleShape temp(sf::Vector2f(m_width, m_height));
			temp.setPosition(m_x, m_y);
			temp.setFillColor(sf::Color(m_color));
			window.draw(temp);
		};

		bool checkBounds(int x, int y) {
			if (x > m_x &&
				y > m_y &&
				x < m_x + m_width &&
				y < m_y + m_height) {
				return true;
			}
			return false;
		}

	private:
		int m_x, m_y;
		int m_width, m_height;
		uint32_t m_color;
	};

}