#pragma once

#include "Shades\displayable.h"
#include "Shades\tinyxml2.h"
#include <cmath>

namespace sds
{

	class Circle : public displayable
	{
	public:
		Circle(std::string id, int x, int y, int radius, uint32_t color) : displayable(id), m_x(x), m_y(y), m_radius(radius), m_color(color) {}

		Circle(tinyxml2::XMLElement *elem)
		{
			const char *id;
			int x, y, radius;
			int64_t color;
			const char *callbackId;

			int64_t outlineColor;
			int64_t outlineWidth;

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

			if (elem->Attribute("radius") == NULL)
			{
				radius = 10;
			}
			else
			{
				elem->QueryIntAttribute("radius", &radius);
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
			m_radius = radius;
			m_color = color;
			m_outlineColor = outlineColor;
			m_outlineWidth = outlineWidth;
		}

		void display() override
		{
			Brain.Screen.setPenWidth(m_outlineWidth);
			Brain.Screen.setPenColor(m_outlineColor);
			Brain.Screen.drawCircle(m_x, m_y, m_radius, m_color);
		};

		bool checkBounds(int x, int y) override
		{
			if (sqrt(pow(m_x - x, 2) + pow(m_y - y, 2)) < m_radius)
			{
				return true;
			}
			return false;
		}

	private:
		int m_x, m_y;
		int m_radius;
		uint32_t m_color;
		uint32_t m_outlineColor;
		int m_outlineWidth;
	};

}