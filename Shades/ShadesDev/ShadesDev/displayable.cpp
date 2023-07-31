#include "displayable.h"
#include "Screen.h"

namespace sds {

	displayable::displayable() : m_id("none") {}
	displayable::displayable(std::string id) : m_id(id) {}

	std::string displayable::getId()
	{
		return m_id;
	}

	void displayable::registerCallback(std::string callbackId)
	{
		m_callbackId = callbackId;
	}

	void displayable::executeCallback()
	{
		Screen::executeCallback(m_callbackId);
	}
}