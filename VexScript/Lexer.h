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

		IDENTIFIER,
		QUOTES,
		DOUBLE_QUOTES,
		STRING,
		NUMBER,
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
		COMMA,
		SEMICOLON,

		KEYWORD,
		FUNCTION,

		END_OF_LINE,
		END_OF_FILE,

		ERROR,
		COMMENT,
	};


	token(type type, std::string text, int startm_pos) :m_type(type), m_text(text), m_startm_pos(startm_pos) {}

	type getType() { return m_type; }
	std::string getText() { return m_text; }
	int getStartm_pos() { return m_startm_pos; }

private:
	type m_type;
	std::string m_text;
	int m_startm_pos;
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

	int tokenize();

	token operator[](int index) {
		// do something with index
		return m_tokens[index];
	}
	size_t size() { return m_tokens.size(); }
	std::string getSource() { return m_src; }
private:

	const std::string allChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_";
	bool inChars(char c) {
		for (size_t i = 0; i < allChars.size(); i++)
		{
			if (c == allChars[i]) { return true; }
		}
		return false;
	}
	const std::string allNumChars = "1234567890";
	bool inNumChars(char c) {
		for (size_t i = 0; i < allNumChars.size(); i++)
		{
			if (c == allNumChars[i]) { return true; }
		}
		return false;
	}

	std::vector <std::string> keyWords = {
		"auto",
		"break",
		"case",
		"char",
		"const",
		"continue",
		"default",
		"do",
		"double",
		"else",
		"enum",
		"extern",
		"float",
		"for",
		"goto",
		"if",
		"int",
		"long",
		"register",
		"return",
		"short",
		"signed",
		"sizeof",
		"static",
		"struct",
		"switch",
		"typedef",
		"union",
		"unsigned",
		"void",
		"volatile",
		"while"
	};
	bool isKeyword(std::string s) {
		for (size_t i = 0; i < keyWords.size(); i++)
		{
			if (s == keyWords[i]) { return true; }
		}
		return false;
	}

	std::vector <std::string> functionNames = { "main", "print" };
	bool isFunction(std::string s) {
		for (size_t i = 0; i < functionNames.size(); i++)
		{
			if (s == functionNames[i]) { return true; }
		}
		return false;
	}

	std::string addNext() {
		if (m_pos + 1 < m_src.size()) {
			m_pos++;
			return std::string(1, m_src[m_pos]);
		}
		return "\0";
	}
	std::string getNexts() {
		if (m_pos + 1 < m_src.size()) {
			return std::string(1, m_src[m_pos + 1]);
		}
		return "\0";
	}
	char getNextc() {
		if (m_pos + 1 < m_src.size()) {
			return m_src[m_pos + 1];
		}
		return '\0';
	}

	std::vector <token> m_tokens;
	std::string m_src;
	size_t m_pos = 0;
	
};