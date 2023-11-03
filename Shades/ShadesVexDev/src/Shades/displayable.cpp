#include "Shades\displayable.h"
#include "Shades\Screen.h"

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

  // template<typename ... Args>
	// 	void displayable::setText(const std::string& format, Args ... args) {
	// 		int size_s = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	// 		// if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
	// 		auto size = static_cast<size_t>(size_s);
	// 		std::unique_ptr<char[]> buf(new char[size]);
	// 		snprintf(buf.get(), size, format.c_str(), args ...);
	// 		std::string text = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside

	// 		m_text = text;
	// 	};
  void displayable::setText(std::string text){
    m_text = text;
  };

}