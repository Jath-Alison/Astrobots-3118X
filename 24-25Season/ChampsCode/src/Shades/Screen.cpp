#include "Shades\Screen.h"
#include "Shades\displayable.h"
#include "Shades\displayables.h"

namespace sds
{

	Screen::Screen()
	{
	}

	std::vector<std::shared_ptr<displayable>> Screen::m_displayables = {};

	std::unordered_map<std::string, std::function<void(void)>> Screen::m_functions;
	std::unordered_map<std::string, double> Screen::m_data;

	tinyxml2::XMLDocument Screen::m_doc;
	tinyxml2::XMLElement *Screen::m_shadesXml = nullptr;
	std::map<std::string, tinyxml2::XMLElement *> Screen::m_screens = {};

	std::string Screen::m_currentScreen = "";

	bool Screen::m_changed = false;
	void Screen::forceChange(){m_changed = true;}

	int Screen::m_refreshRate = 30;

	void Screen::initialize()
	{
		m_doc.LoadFile("configFile.xml");
		tinyxml2::XMLElement *root = m_doc.FirstChildElement();
		m_shadesXml = root->FirstChildElement("shades");

		tinyxml2::XMLElement *screen = m_shadesXml->FirstChildElement("screen");
		while (screen != nullptr)
		{
			if (screen->Attribute("id"))
			{
				m_screens[screen->Attribute("id")] = screen;
			}

			screen = screen->NextSiblingElement("screen");
		}

		for (auto screen : m_screens)
		{
			std::string tempStr = screen.first;
			m_functions[tempStr] = [=]()
			{ load(tempStr); };
		}

		load("home");
	}

	void Screen::initialize(std::string xml)
	{
		m_doc.Parse(xml.c_str());
		tinyxml2::XMLElement *root = m_doc.FirstChildElement("root");
		m_shadesXml = root->FirstChildElement("shades");

		tinyxml2::XMLElement *screen = m_shadesXml->FirstChildElement("screen");
		while (screen != nullptr)
		{
			if (screen->Attribute("id"))
			{
				m_screens[screen->Attribute("id")] = screen;
			}

			screen = screen->NextSiblingElement("screen");
		}

		for (auto screen : m_screens)
		{
			std::string tempStr = screen.first;
			m_functions[tempStr] = [=]()
			{ load(tempStr); };
		}

		load("home");
	}

	int Screen::eventLoop()
	{
		while (true)
		{
			if (Brain.Screen.PRESSED)
			{
				Screen::handleClick(Brain.Screen.xPosition(), Brain.Screen.yPosition());
			}
			vex::wait(10, vex::msec);
		}
	}

	int Screen::displayLoop()
	{
		while (true)
		{
			if (m_changed)
			{
				display();
				m_changed = false;
				// Brain.Screen.render();
			}
			vex::wait(m_refreshRate, vex::msec);
		}
	}

	void Screen::display()
	{
		Brain.Screen.clearScreen();
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			m_displayables[i]->display();
		}
		Brain.Screen.render();
	}

	void Screen::load(std::string screenId)
	{

		m_changed = true;

		m_displayables.clear();

		tinyxml2::XMLElement *screen = getScreen(screenId);
		if(!screen){return;}
		m_currentScreen = screenId;

		std::cout << screen->Name() << ":" << screen->Attribute("id") << std::endl;

		tinyxml2::XMLElement *items = screen->FirstChildElement();
		while (items)
		{

			// std::cout << "     " << items->Name() << " x:" << items->Attribute("x") << " y:" << items->Attribute("y") << std::endl;

			std::string name = items->Name();

			if (name == "box")
			{
				m_displayables.push_back(std::make_shared<Box>(items));
			}
			else if (name == "circle")
			{
				m_displayables.push_back(std::make_shared<Circle>(items));
			}
			else if (name == "text")
			{
				m_displayables.push_back(std::make_shared<Text>(items));
			}
			else if (name == "image")
			{
				m_displayables.push_back(std::make_shared<Image>(items));
			}
			if (name == "smart_text")
			{
				m_displayables.push_back(std::make_shared<SmartText>(items));
			}

			items = items->NextSiblingElement();
		}
	}

	std::string Screen::getCurrentScreen()
	{
		return m_currentScreen;
	}

	void Screen::executeCallback(std::string callbackId)
	{
		if (m_functions.find(callbackId) != m_functions.end())
		{
			m_functions[callbackId]();
		}
	}
	void Screen::addCallback(std::string callbackId, std::function<void(void)> function)
    {
		m_functions[callbackId] = function;
    }

	void Screen::handleClick(int x, int y)
	{
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			if (m_displayables[i]->checkBounds(x, y))
			{
				m_displayables[i]->executeCallback();
			}
		}
	}

	std::shared_ptr<displayable> Screen::getElementById(std::string id)
	{
		for (size_t i = 0; i < m_displayables.size(); i++)
		{
			if (m_displayables[i]->getId() == id)
			{
				return m_displayables[i];
			}
		}
		return nullptr;
	}

	void Screen::setData(std::string key, double data)
	{
		m_data[key] = data;
	}

	double Screen::getData(std::string key)
	{
		if (m_data.find(key) != m_data.end())
		{
			return m_data[key];
		}
		return 0.0;
	}

	tinyxml2::XMLElement *Screen::getScreen(std::string screenId)
	{
		tinyxml2::XMLElement *screen = m_shadesXml->FirstChildElement("screen");
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