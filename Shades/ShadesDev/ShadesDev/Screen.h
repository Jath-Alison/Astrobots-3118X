#pragma once

#include "tinyxml2.h"

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <map>
#include <functional>
#include <iostream>

namespace sds {

	class displayable;

	inline void print() {
		std::cout << "print called \n";	
	}

	class Screen
	{
	public:
		static void initialize();

		static void display();

		static void load(std::string screenId);

		static void executeCallback(std::string callbackId);

		static void handleClick(int x, int y);

		static std::shared_ptr <displayable> getElementById(std::string id);


		static void setData(std::string key, double data);
		static double getData(std::string key);


		template<typename Type>
		static Type* getElement(std::string id)
		{
			return dynamic_cast <Type*> (sds::Screen::getElementById(id).get());
		}

	private:
		Screen();

		static tinyxml2::XMLElement* getScreen(std::string namescreenId);

		static std::vector <std::shared_ptr <displayable>> m_displayables;
		static std::unordered_map < std::string, std::function <void(void)>> m_functions;

		static std::unordered_map <std::string, double> m_data;
		
		static tinyxml2::XMLDocument m_doc;
		static tinyxml2::XMLElement* m_shadesXml;
		static std::map <std::string, tinyxml2::XMLElement*> m_screens;
	};

}