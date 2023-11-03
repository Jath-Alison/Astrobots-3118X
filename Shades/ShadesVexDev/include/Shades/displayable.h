#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include "robot-config.h"

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

		void registerCallback(std::string callbackId);
		void executeCallback();

    // template<typename ... Args>
		// void setText(const std::string& format, Args ... args);
    void setText(std::string text);

	protected:

		std::string m_id;
		std::string m_callbackId;

    std::string m_text;

	};

}