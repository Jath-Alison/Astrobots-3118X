#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include "robotConfig.h"

namespace sds {

	class Screen;

	class displayable
	{
	public:

		displayable();
		displayable(std::string id);

		virtual void display() = 0;
		virtual bool checkBounds(int x, int y) = 0;

		std::string getId();
		std::string getBaseText();

		void registerCallback(std::string callbackId);
		void executeCallback();

    // template<typename ... Args>
		// void setText(const std::string& format, Args ... args);
    void setText(std::string text);

	protected:

		std::string m_id;
		std::string m_callbackId;

    	std::string m_text;
		// std::string m_prevText;
		std::string m_base_text;

	};

}