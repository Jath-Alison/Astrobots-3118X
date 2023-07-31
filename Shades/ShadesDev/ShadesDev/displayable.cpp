#include "displayable.h"
#include "Screen.h"

namespace sds {

	displayable::displayable(std::string id) : m_id(id) {}

	std::string displayable::getId()
	{
		return m_id;
	}

	void displayable::executeCallback()
	{
		Screen::executeCallback(m_callbackId);
	}
}