#pragma once
#include <string>
#include "window.h"

namespace sds {

	class Screen;

	class displayable
	{
	public:

		displayable(std::string id);

		virtual void display() = 0;

		std::string getId();

		void executeCallback();

	private:

		std::string m_id;
		std::string m_callbackId;

	};

}