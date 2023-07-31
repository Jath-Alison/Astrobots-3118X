#include "Screen.h"
#include "displayable.h"
#include "Box.h"

namespace sds {

	Screen::Screen()
	{
	}

	std::vector <std::shared_ptr <displayable>> Screen::m_displayables = {};

	std::unordered_map < std::string, std::function <void(void)>> Screen::m_functions = {};
	
	tinyxml2::XMLDocument Screen::m_doc;
	tinyxml2::XMLElement* Screen::m_shadesXml = nullptr;
	//std::map <std::string, tinyxml2::XMLElement> Screen::m_screens = {};


	void Screen::initialize()
	{
		m_doc.LoadFile("configFile.xml");
		tinyxml2::XMLElement* root = m_doc.FirstChildElement();
		m_shadesXml = root->FirstChildElement("shades");
		tinyxml2::XMLElement* temp = m_shadesXml->FirstChildElement("screen");

	}

	void Screen::display()
	{
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			m_displayables[i]->display();
		}
	}

	void Screen::load(std::string screenId)
	{
		m_displayables.clear();

		tinyxml2::XMLElement* screen = getScreen(screenId);

		std::cout << screen->Name() << ":" << screen->Attribute("id") << std::endl;

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
			/*else if (name == "circle") {
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
			}*/

			items = items->NextSiblingElement();
		}
	}

	void Screen::executeCallback(std::string callbackId)
	{
		if (m_functions.find(callbackId) != m_functions.end()) {
			m_functions[callbackId]();
		}
	}


	std::shared_ptr<displayable> Screen::getElementById(std::string id)
	{
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			if (m_displayables[i]->getId() == id) {
				return m_displayables[i];
			}
		}
		return nullptr;
	}
	tinyxml2::XMLElement* Screen::getScreen(std::string screenId)
	{
		bool temp = m_shadesXml == nullptr;
		tinyxml2::XMLElement* screen = m_shadesXml->FirstChildElement("screen");
		while (screen != nullptr)
		{
			if (screen->Attribute("id", screenId.c_str()))
			{
				return screen;
			}

			screen = screen->NextSiblingElement("screen");
		}
		return nullptr;
	}
}