#pragma once
#include <variant>
#include <string>

class staticType
{
public:
	enum class type {
		STRING,
		BOOL,
		INT,
		FLOAT,
		DOUBLE,
		ARRAY
	};

	staticType(type t, std::string valu) : m_type(t), m_value(valu) {

	}

	type getType() { return m_type; }
	std::string getValue() { return m_value; }
private:
	type m_type;
	std::string m_value;
};

