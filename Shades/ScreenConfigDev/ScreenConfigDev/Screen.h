#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <memory>

#include "tinyxml2.h"

#include "Box.h"
#include "Circle.h"
#include "Text.h"

class Screen
{
public:
	Screen() {};
	Screen(std::vector <std::shared_ptr<displayable>> displayables) : m_displayables(displayables) {};
	Screen(tinyxml2::XMLElement* screen) {
		load(screen);
	}

	void load(tinyxml2::XMLElement* screen) {
		clear();
		if (!screen) { std::cout << "Not a valid Screen" << std::endl; return; };
		if (std::strcmp(screen->Name(), "Screen") == 0) { std::cout << "Not a valid Screen" << std::endl; return; };
		std::cout << screen->Name() << ":" << screen->Attribute("name") << std::endl;

		tinyxml2::XMLElement* items = screen->FirstChildElement();
		while (items) {

			//std::cout << "     " << items->Name() << " x:" << items->Attribute("x") << " y:" << items->Attribute("y") << std::endl;

			std::string name = items->Name();


			if (name == "box") {
				const char* id;
				int x, y, width, height;
				int64_t color;
				
				if (items->Attribute("id") == NULL) { id = ""; }
				else { items->QueryStringAttribute("id", &id); }
				
				if (items->Attribute("x") == NULL) { x = 10; } 
				else { items->QueryIntAttribute("x", &x); }

				if (items->Attribute("y") == NULL) { y = 10; } 
				else { items->QueryIntAttribute("y", &y); }

				if (items->Attribute("width") == NULL) { width = 10; }
				else { items->QueryIntAttribute("width", &width); }

				if (items->Attribute("height") == NULL) { height = 10; }
				else { items->QueryIntAttribute("height", &height); }

				if (items->Attribute("color") == NULL) { color = 0xFFFFFFFF; } 
				else { items->QueryInt64Attribute("color", &color); }

				m_displayables.push_back(std::make_shared<Box>(id, x, y, width, height, color));
			}
			else if (name == "circle") {
				const char* id;
				int x, y, radius;
				int64_t color;

				if (items->Attribute("id") == NULL) { id = ""; }
				else { items->QueryStringAttribute("id", &id); }

				if (items->Attribute("x") == NULL) { x = 10; }
				else { items->QueryIntAttribute("x", &x); }

				if (items->Attribute("y") == NULL) { y = 10; }
				else { items->QueryIntAttribute("y", &y); }

				if (items->Attribute("radius") == NULL) { radius = 10; }
				else { items->QueryIntAttribute("radius", &radius); }


				if (items->Attribute("color") == NULL) { color = 0xFFFFFFFF; }
				else { items->QueryInt64Attribute("color", &color); }

				m_displayables.push_back(std::make_shared<Circle>(id, x, y, radius, color));
			}
			else if (name == "text") {
				const char* id;
				int x, y, size;
				const char* text;
				int64_t color;
				
				if (items->Attribute("id") == NULL) { id = ""; }
				else { items->QueryStringAttribute("id", &id); }

				if (items->Attribute("x") == NULL) { x = 10; }
				else { items->QueryIntAttribute("x", &x); }

				if (items->Attribute("y") == NULL) { y = 10; }
				else { items->QueryIntAttribute("y", &y); }

				if (items->Attribute("text") == NULL) { text = "No Text"; }
				else { items->QueryStringAttribute("text", &text); }

				if (items->Attribute("size") == NULL) { size = NULL; }
				else { items->QueryIntAttribute("size", &size); }


				if (items->Attribute("color") == NULL) { color = 0xFFFFFFFF; }
				else { items->QueryInt64Attribute("color", &color); }

				m_displayables.push_back(std::make_shared<Text>(id, x, y, text, size, color));
			}

			items = items->NextSiblingElement();
		}
	}

	void addData(std::string name, double* dataPtr) {
		m_data[name] = dataPtr;
	}

	void display() {
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			if (m_displayables[i]) {
				m_displayables[i]->display();
			}
			else {
				m_displayables.erase(m_displayables.begin() + i);
			}
		}
	}

	void clear() {
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			m_displayables[i] = nullptr;
		}
	}

	std::shared_ptr<displayable>getElementById(std::string id) {
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			if (m_displayables[i]->getId() == id) {
				return m_displayables[i];
			}
		}
		return nullptr;
	}

private:
	std::vector <std::shared_ptr< displayable>> m_displayables;
	std::map <std::string, double*> m_data;
};

