#pragma once

#include "Shades\displayable.h"
#include "Shades\tinyxml2.h"
#include <memory>
#include <string>
#include <stdexcept>


namespace sds {

	class Text : public displayable
	{
	public:

		Text(std::string id, int x, int y, std::string text, int size, uint32_t color) : displayable(id), m_x(x), m_y(y), m_color(color) {
			m_text = text;
		}
		Text(tinyxml2::XMLElement* elem) {
			const char* id;
			int x, y, size;
			const char* text;
			const char* font;
			int64_t color;
			int64_t bkgColor;
			const char* callbackId;

			if (elem->Attribute("id") == NULL) { id = ""; }
			else { elem->QueryStringAttribute("id", &id); }

			if (elem->Attribute("x") == NULL) { x = 10; }
			else { elem->QueryIntAttribute("x", &x); }

			if (elem->Attribute("y") == NULL) { y = 10; }
			else { elem->QueryIntAttribute("y", &y); }

			if (elem->Attribute("text") == NULL) { text = "No Text"; }
			else { elem->QueryStringAttribute("text", &text); }

			if (elem->Attribute("font") == NULL) { font = "mono15"; }
			else { elem->QueryStringAttribute("font", &font); }

			if (elem->Attribute("color") == NULL) { color = 0xFFFFFFFF; }
			else { elem->QueryInt64Attribute("color", &color); }

			if (elem->Attribute("bkgColor") == NULL) { bkgColor = 0x00000000; }
			else { elem->QueryInt64Attribute("bkgColor", &bkgColor); }

			if (elem->Attribute("callback") == NULL) { callbackId = "none"; }
			else {
				callbackId = elem->Attribute("callback");
				registerCallback(callbackId);
			}

			m_id = id;
			m_text = text;
			if(fontMap.find(font)!= fontMap.end()) {
				m_font = fontMap[font];
			}else{
				m_font = vex::fontType::mono15;
			}
			m_x = x;
			m_y = y;
			m_color = color;
			m_bkgColor = bkgColor;
		}

		void display() override {
			Brain.Screen.setFillColor(m_bkgColor);
			Brain.Screen.setPenColor(m_color);
			Brain.Screen.setFont(m_font);
			Brain.Screen.printAt(m_x, m_y, m_text.c_str());

		};

		bool checkBounds(int x, int y) override {
			//Lets say its unclickable for now
			return false;
		}

	private:
		int m_x, m_y;
		uint32_t m_color;
		uint32_t m_bkgColor;
		vex::fontType m_font;

		std::map<std::string, vex::fontType> fontMap = {
			{ "mono12", vex::fontType::mono12 },
			{ "mono15", vex::fontType::mono15 },
			{ "mono20", vex::fontType::mono20 },
			{ "mono30", vex::fontType::mono30 },
			{ "mono40", vex::fontType::mono40 },
			{ "mono60", vex::fontType::mono60 },

			{ "prop20", vex::fontType::prop20 },
			{ "prop30", vex::fontType::prop30 },
			{ "prop40", vex::fontType::prop40 },
			{ "prop60", vex::fontType::prop60 },

			{ "CJK16", vex::fontType::cjk16 },

			{ "monoXS", vex::fontType::mono12 },
			{ "monoS", vex::fontType::mono15 },
			{ "monoM", vex::fontType::mono20 },
			{ "monoL", vex::fontType::mono30 },
			{ "monoXL", vex::fontType::mono40 },
			{ "monoXXL", vex::fontType::mono60 },

			{ "propM", vex::fontType::prop20 },
			{ "propL", vex::fontType::prop30 },
			{ "propXL", vex::fontType::prop40 },
			{ "propXXL", vex::fontType::prop60 },
		};
			
	};

}