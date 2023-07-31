#pragma once
#include <string>
#include "window.h"

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

	private:

		std::string m_id;
		std::string m_callbackId;

	};

}