#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <memory>

#include "tinyxml2.h"

#include "Box.h"
#include "Circle.h"
#include "Text.h"
#include "Image.h"

inline void printttt() {
	std::cout << "print just ran \n";
}

class Screen
{
public:

	Screen() { m_functions["print"] = printttt; };
	//Screen(std::vector <std::shared_ptr<displayable>> displayables) : m_displayables(displayables) {};
	Screen(tinyxml2::XMLElement* screen) {
		m_functions["print"] = printttt;
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
			else if (name == "image") {
				const char* id;
				int x, y, size;
				const char* src;
				int64_t color;

				if (items->Attribute("id") == NULL) { id = ""; }
				else { items->QueryStringAttribute("id", &id); }

				if (items->Attribute("x") == NULL) { x = 10; }
				else { items->QueryIntAttribute("x", &x); }

				if (items->Attribute("y") == NULL) { y = 10; }
				else { items->QueryIntAttribute("y", &y); }

				if (items->Attribute("src") == NULL) { src = "Image.png"; }
				else { items->QueryStringAttribute("src", &src); }


				m_displayables.push_back(std::make_shared<Image>(id, x, y, src));
			}

			items = items->NextSiblingElement();
		}
	}

	void setData(std::string name, double data) {
		m_data[name] = data;
	}
	double getData(std::string name) {
		if (m_data.find(name) != m_data.end()) {
			return m_data[name];
		}
		return NULL;
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
		m_displayables.clear();
	}

	void handleClick(ClickTypes type, int x, int y) {
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			m_displayables[i]->clickEvent( type, x, y);
		}
	}
	
	void handleCallbacks() {
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			if (m_displayables[i]->isWaitingForCallback()) {
				std::string callback = m_displayables[i]->execCallBackFunc();
				if (m_functions.find(callback) != m_functions.end()) {
					m_functions[m_displayables[i]->execCallBackFunc()]();
				}
			}
		}
	}

	std::shared_ptr<displayable>getElementById(std::string id) {
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			if (m_displayables[i]) {
				if (m_displayables[i]->getId() == id) {
					return m_displayables[i];
				}
			}
			else {
				m_displayables.erase(m_displayables.begin() + i);
			}
		}
		return nullptr;
	}

	template<typename ... Args>
	void setElementText(std::string id, std::string text, Args... args) {
		int size_s = std::snprintf(nullptr, 0, text.c_str(), args ...) + 1; // Extra space for '\0'
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, text.c_str(), args ...);
		std::string formattedText = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside

		if ( getElementById(id) != nullptr ) { getElementById(id)->setText(formattedText); }
	}

	void setElementSrc(std::string id, std::string text) {
		if (getElementById(id) != nullptr) { getElementById(id)->setSrc(text); }
	}

	void setElementCallbackFunc(std::string id, std::string callbackFunc) {
		if (getElementById(id) != nullptr) { getElementById(id)->setCallbackFunc(callbackFunc); }
	}

private:

	std::vector <std::shared_ptr<displayable>> m_displayables;
	std::unordered_map <std::string, double> m_data;
	std::unordered_map <std::string, std::function<void(void)>> m_functions;
};

