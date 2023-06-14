#pragma once

#include "displayable.h"
#include "window.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <stdexcept>

extern sf::Font Calibri;

class Image : public displayable
{
public:

	Image(std::string id, int x, int y, std::string src) : displayable(id), m_x(x), m_y(y){
		m_src = src;
		
		if (!texture.loadFromFile(m_src)) {
			texture.loadFromFile("Image.png");
		}
		
		m_sprite.setTexture(texture);
	}

	void display() override {
		if (!m_active) { return; }
		m_sprite.setPosition(m_x, m_y);
		window.draw(m_sprite);
	};

private:
	sf::Texture texture;
	int m_x, m_y;
	sf::Sprite m_sprite;
};

