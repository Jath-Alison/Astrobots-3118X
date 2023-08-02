#pragma once

#include "Shades\displayable.h"
#include "Shades\tinyxml2.h"
#include "Shades\Screen.h"
#include <memory>
#include <array>
#include <string>
#include <stdexcept>

namespace sds {

  class Screen;

	class SmartText : public displayable
	{
	public:

		SmartText(std::string id, int x, int y, std::string text, int size, uint32_t color) : displayable(id), m_x(x), m_y(y),  m_color(color) {
			m_text = text;
		}
		SmartText(tinyxml2::XMLElement* elem) {
			const char* id;
			int x, y, size;
			const char* format;
			int64_t color;
			const char* callbackId;

			if (elem->Attribute("id") == NULL) { id = ""; }
			else { elem->QueryStringAttribute("id", &id); }

			if (elem->Attribute("x") == NULL) { x = 10; }
			else { elem->QueryIntAttribute("x", &x); }

			if (elem->Attribute("y") == NULL) { y = 10; }
			else { elem->QueryIntAttribute("y", &y); }

			if (elem->Attribute("format") == NULL) { format = "No Text"; }
			else { elem->QueryStringAttribute("format", &format); }

			if (elem->Attribute("color") == NULL) { color = 0xFFFFFFFF; }
			else { elem->QueryInt64Attribute("color", &color); }

			if (elem->Attribute("callback") == NULL) { callbackId = "none"; }
			else {
				callbackId = elem->Attribute("callback");
				registerCallback(callbackId);
			}

			tinyxml2::XMLElement* data = elem->FirstChildElement("data");
			int count = 0;
			while (data != nullptr)
			{
				if (data->Attribute("id"))
				{
					m_dataIds[count] = data->Attribute("id");
				}

				count++;
				data = data->NextSiblingElement("data");
			}

			m_id = id;
			m_format = format;
			m_x = x;
			m_y = y;
			m_color = color;
		}

		void display() override {

			double one = Screen::getData(m_dataIds[0]);
			double two = Screen::getData(m_dataIds[1]);

			setText(m_format,
				Screen::getData(m_dataIds[0]), Screen::getData(m_dataIds[1]),Screen::getData( m_dataIds[2]), Screen::getData(m_dataIds[3]), Screen::getData(m_dataIds[4]), Screen::getData(m_dataIds[5]), Screen::getData(m_dataIds[6]), Screen::getData(m_dataIds[7]), Screen::getData(m_dataIds[8]), Screen::getData(m_dataIds[9])
			);

			Brain.Screen.printAt(m_x, m_y, m_text.c_str());
		};

		bool checkBounds(int x, int y) override{
			//Lets say its unclickable for now
			return false;
		}

	private:

		template<typename ... Args>
		void setText(const std::string& format, Args ... args) {

			int size_s = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
			if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
			auto size = static_cast<size_t>(size_s);
			std::unique_ptr<char[]> buf(new char[size]);
			snprintf(buf.get(), size, format.c_str(), args ...);
			std::string text = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside

			m_text = text;
		};

		int m_x, m_y;
		uint32_t m_color;
		std::string m_text;

		std::string m_format;
		std::array <std::string,10> m_dataIds;
	};

}