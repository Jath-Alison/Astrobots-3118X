#pragma once

#include "Shades\displayable.h"
#include "Shades\tinyxml2.h"

namespace sds
{

	class Box : public displayable
	{
	public:
		Box(std::string id, int x, int y, int width, int height, uint32_t color) : displayable(id), m_x(x), m_y(y), m_width(width), m_height(height), m_color(color) {}

		Box(tinyxml2::XMLElement *elem)
		{
			const char *id;
			int x, y, width, height;
			int64_t color;
			int64_t outlineColor;
			int64_t outlineWidth;
			const char *callbackId;

			if (elem->Attribute("id") == NULL)
			{
				id = "";
			}
			else
			{
				elem->QueryStringAttribute("id", &id);
			}

			if (elem->Attribute("x") == NULL)
			{
				x = 10;
			}
			else
			{
				elem->QueryIntAttribute("x", &x);
			}

			if (elem->Attribute("y") == NULL)
			{
				y = 10;
			}
			else
			{
				elem->QueryIntAttribute("y", &y);
			}

			if (elem->Attribute("width") == NULL)
			{
				width = 10;
			}
			else
			{
				elem->QueryIntAttribute("width", &width);
			}

			if (elem->Attribute("height") == NULL)
			{
				height = 10;
			}
			else
			{
				elem->QueryIntAttribute("height", &height);
			}

			if (elem->Attribute("color") == NULL)
			{
				color = 0xFFFFFFFF;
			}
			else
			{
				elem->QueryInt64Attribute("color", &color);
			}

			if (elem->Attribute("outlineColor") == NULL)
			{
				outlineColor = color;
			}
			else
			{
				elem->QueryInt64Attribute("outlineColor", &outlineColor);
			}

			if (elem->Attribute("outlineWidth") == NULL)
			{
				outlineWidth = 1.0;
			}
			else
			{
				elem->QueryInt64Attribute("outlineWidth", &outlineWidth);
			}

			if (elem->Attribute("callback") == NULL)
			{
				callbackId = "none";
			}
			else
			{
				callbackId = elem->Attribute("callback");
				registerCallback(callbackId);
			}

			m_id = id;
			m_x = x;
			m_y = y;
			m_width = width;
			m_height = height;
			m_color = color;
			m_outlineColor = outlineColor;
			m_outlineWidth = outlineWidth;
		}

		void display() override
		{
			// if (!m_active) { return; }

			// sf::RectangleShape temp(sf::Vector2f(m_width, m_height));
			// temp.setPosition(m_x, m_y);
			// temp.setFillColor(sf::Color(m_color));
			// window.draw(temp);

			Brain.Screen.setPenWidth(m_outlineWidth);
			Brain.Screen.setPenColor(m_outlineColor);

			Brain.Screen.drawRectangle(m_x, m_y, m_width, m_height, m_color);
		};

		bool checkBounds(int x, int y) override
		{
			if (x > m_x &&
				y > m_y &&
				x < m_x + m_width &&
				y < m_y + m_height)
			{
				return true;
			}
			return false;
		}

	private:
		int m_x, m_y;
		int m_width, m_height;
		uint32_t m_color;
		uint32_t m_outlineColor;
		int m_outlineWidth;
	};

}