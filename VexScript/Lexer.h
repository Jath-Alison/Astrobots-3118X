#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class token {
public:
	enum class type {
		ASSIGNMENT,
		PLUS,
		MINUS,
		MULTIPLY,
		DIVIDE,
		EXPONENT,
		MODULO,
		EQUALS,
		NOT_EQUALS,
		NOT,
		GREATER_THAN,
		LESS_THAN,
		GREATER_THAN_EQUAL_TO,
		LESS_THAN_EQUAL_TO,
		INCREMENT,
		DECREMENT,
		COMMA,
		QUOTES,
		DOUBLE_QUOTES,
		INTEGER,
		FLOAT,
		DOUBLE,
		BOOLEAN,
		SQUARE_BRACKET_OPEN,
		SQUARE_BRACKET_CLOSE,
		CURLY_BRACKETS_OPEN,
		CURLY_BRACKETS_CLOSE,
		PARENTHESES_OPEN,
		PARENTHESES_CLOSE,
		SEMICOLON,

		END_OF_LINE,
		END_OF_FILE
	};

	token(type type, std::string text, int startPos) :m_type(type), m_text(text), m_startPos(startPos) {}

	type getType() { return m_type; }
	std::string getText() { return m_text; }
	int getStartPos() { return m_startPos; }
private:
	type m_type;
	std::string m_text;
	int m_startPos;
};

class Lexer {
public:

	Lexer(std::string source) :m_src(source) {}
	Lexer() : m_src() {}

	int loadFromFile(std::string fileSource) {
		std::ifstream file(fileSource);
		
		if (!file.is_open()) {
			// File could not be opened
			return 1;
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		
		m_src = buffer.str();
		return 0;
	}

	token operator[](int index) {
		// do something with index
		return m_tokens[index];
	}
	size_t size() { return m_tokens.size(); }
	std::string getSource() { return m_src; }
private:
	std::vector <token> m_tokens;
	std::string m_src;
};