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

		template<typename ... Args>
		void setText(const std::string& format, Args ... args) {
			int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
			if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
			auto size = static_cast<size_t>(size_s);
			std::unique_ptr<char[]> buf(new char[size]);
			std::snprintf(buf.get(), size, format.c_str(), args ...);
			std::string text = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside

			m_text = text;
		};

	private:
		int m_x, m_y;
		uint32_t m_color;
		unsigned int m_size{ NULL };
		std::string m_text;
	};

}