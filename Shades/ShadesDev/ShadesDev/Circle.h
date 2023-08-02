#pragma once

#include "displayable.h"
#include "window.h"
#include <SFML/Graphics.hpp>

namespace sds {

	class Circle : public displayable
	{
	public:

		Circle(std::string id, int x, int y, int radius, uint32_t color) :displayable(id), m_x(x), m_y(y), m_radius(radius), m_color(color) {}

		Circle(tinyxml2::XMLElement* elem) {
			const char* id;
			int x, y, radius;
			int64_t color;
			const char* callbackId;

			if (elem->Attribute("id") == NULL) { id = ""; }
			else { elem->QueryStringAttribute("id", &id); }

			if (elem->Attribute("x") == NULL) { x = 10; }
			else { elem->QueryIntAttribute("x", &x); }

			if (elem->Attribute("y") == NULL) { y = 10; }
			else { elem->QueryIntAttribute("y", &y); }

			if (elem->Attribute("radius") == NULL) { radius = 10; }
			else { elem->QueryIntAttribute("radius", &radius); }

			if (elem->Attribute("color") == NULL) { color = 0xFFFFFFFF; }
			else { elem->QueryInt64Attribute("color", &color); }

			if (elem->Attribute("callback") == NULL) { callbackId = "none"; }
			else {
				callbackId = elem->Attribute("callback");
				registerCallback(callbackId);
			}

			m_id = id;
			m_x = x;
			m_y = y;
			m_radius = radius;
			m_color = color;
		}

		void display() override {
			sf::CircleShape temp(m_radius, 100);
			temp.setPosition(m_x - m_radius, m_y - m_radius);
			temp.setFillColor(sf::Color(m_color));
			window.draw(temp);
		};

		bool checkBounds(int x, int y) override {
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