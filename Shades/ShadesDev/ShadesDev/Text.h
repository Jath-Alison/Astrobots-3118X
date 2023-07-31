#pragma once

#include "displayable.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <stdexcept>

extern sf::Font Calibri;

namespace sds {

	class Text : public displayable
	{
	public:

		Text(std::string id, int x, int y, std::string text, int size, uint32_t color) : displayable(id), m_x(x), m_y(y), m_size(size), m_color(color) {
			m_text = text;
		}

		void display() override {
			sf::Text temp;
			if (m_size != NULL) { temp = sf::Text(sf::String(m_text), Calibri, m_size); }
			else { temp = sf::Text(sf::String(m_text), Calibri); }
			temp.setPosition(m_x, m_y);
			temp.setFillColor(sf::Color(m_color));
			window.draw(temp);
		};

		bool checkBounds(int x, int y) {
			//Lets say its unclickable for now
			return false;
		}

	private:
		int m_x, m_y;
		uint32_t m_color;
		unsigned int m_size{ NULL };
		std::string m_text;
	};

}