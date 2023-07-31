#pragma once

#include "displayable.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <stdexcept>

extern sf::Font Calibri;

namespace sds {

	class Image : public displayable
	{
	public:

		Image(std::string id, int x, int y, std::string src) : displayable(id), m_x(x), m_y(y) {
			m_src = src;

			if (!texture.loadFromFile(m_src)) {
				texture.loadFromFile("Image.png");
			}

			m_sprite.setTexture(texture);
		}

		void display() override {
			m_sprite.setPosition(m_x, m_y);
			window.draw(m_sprite);
		};

		bool checkBounds(int x, int y) {
			if (x > m_x &&
				y > m_y &&
				x < m_x + m_sprite.getGlobalBounds().width &&
				y < m_y + m_sprite.getGlobalBounds().height) {
				return true;
			}
			return false;
		}

	private:
		sf::Texture texture;
		int m_x, m_y;
		sf::Sprite m_sprite;
		std::string m_src;
	};

}