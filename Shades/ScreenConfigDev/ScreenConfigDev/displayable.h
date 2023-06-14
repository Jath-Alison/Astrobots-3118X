#pragma once
class displayable
{
public:

	displayable(std::string id): m_id(id) {}

	virtual void display() = 0;
	void setActive(bool active) { m_active = active; };

	template<typename ... Args>
	void setText(const std::string& format, Args ... args) {
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, format.c_str(), args ...);
		std::string text = std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside

		m_text = text;
	};

	void setSrc(std::string src) {
		m_src = src;
	}

	std::string getId() { return m_id; }
protected:
	bool m_active{ true };
	std::string m_id;
	std::string m_text;
	std::string m_src;
};