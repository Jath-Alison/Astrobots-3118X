#include "Lexer.h"

int Lexer::tokenize()
{
    m_tokens.clear();
    m_pos = 0;
    for (m_pos = 0; m_pos < m_src.size(); m_pos++) {

        std::string s(1, m_src[m_pos]);

        if (s == "/") {
            s = addNext();
            if (s == "/") {
                s = addNext();
                while (getNextc() != '\n')
                {
                    if (m_pos + 1 < m_src.size()) {
                        s += addNext();
                    }
                }
                //m_pos++;
                m_tokens.push_back(token(token::type::COMMENT, s, m_pos));
                continue;
            }
            else {
                m_tokens.push_back(token(token::type::ERROR, s + "     -Invalid Token", m_pos));
            }
        }
        
        if (inNumChars(m_src[m_pos])) {//Checks Numbers
            size_t initm_pos = m_pos;
            while (inNumChars(getNextc())) {
                s += addNext();
            }

            m_tokens.push_back(token(token::type::NUMBER, s, initm_pos));
            continue;
        }


        if (inChars(m_src[m_pos])) {//Checks identifiers
            size_t initm_pos = m_pos;
            while (inChars(getNextc())) {
                s += addNext();
            }

            if (isKeyword(s)) {
                m_tokens.push_back(token(token::type::KEYWORD, s, initm_pos));
                continue;
            }
            if (isFunction(s)) {
                m_tokens.push_back(token(token::type::FUNCTION, s, initm_pos));
                continue;
            }

            m_tokens.push_back(token(token::type::ERROR, "Invalid Token", initm_pos));
            return 1; //Invalid Keyword
        }

        if (m_src[m_pos] == '\'') {//Checks single quotes
            //consider do while
            size_t initm_pos = m_pos;
            s = addNext();
            while (getNextc() != '\''){
                if (m_pos+1 < m_src.size()) {
                    if (getNextc() == '\\')
                    {
                        m_pos++;
                    }
                    s += addNext();
                }
                else {
                    m_tokens.push_back(token(token::type::ERROR, "Unclosed single quotes", initm_pos));
                    return 1;//Unclosed single quotes
                }
            }
            m_pos++;
            m_tokens.push_back(token(token::type::STRING, s, initm_pos));
            continue;
        }

        if (m_src[m_pos] == '\"') {//checks double quotes
            //consider do while
            size_t initm_pos = m_pos;
            s = addNext();
            while (getNextc() != '\"') {
                if (m_pos + 1 < m_src.size()) {
                    if (getNextc() == '\\')
                    {
                        m_pos++;
                    }
                    s += addNext();
                }
                else {
                    m_tokens.push_back(token(token::type::ERROR, "Unclosed double quotes", initm_pos));
                    return 1;//Unclosed double quotes
                }
            }
            m_pos++;
            m_tokens.push_back(token(token::type::STRING, s, initm_pos));
            continue;
        }
          

        if (s == " " || s=="\t" || s == "\r" || s == "\n") {//Ignore Whitespace
            continue;
        }

        if (s == "{") {//Curly Braces
            m_tokens.push_back(token(token::type::CURLY_BRACKETS_OPEN, s, m_pos));
            continue;
        }if (s == "}") {
            m_tokens.push_back(token(token::type::CURLY_BRACKETS_CLOSE, s, m_pos));
            continue;
        }

        if (s == "[") {//Square Brackets
            m_tokens.push_back(token(token::type::SQUARE_BRACKET_OPEN, s, m_pos));
            continue;
        }if (s == "]") {
            m_tokens.push_back(token(token::type::SQUARE_BRACKET_CLOSE, s, m_pos));
            continue;
        }

        if (s == "(") {//Parantheses
            m_tokens.push_back(token(token::type::PARENTHESES_OPEN, s, m_pos));
            continue;
        }if (s == ")") {
            m_tokens.push_back(token(token::type::PARENTHESES_CLOSE, s, m_pos));
            continue;
        }

        if (s == ";") {//Semicolon
            m_tokens.push_back(token(token::type::SEMICOLON, s, m_pos));
            continue;
        }
        
        m_tokens.push_back(token(token::type::ERROR, s + "     -Unhandled Character", m_pos));
    }

    m_pos++;
    m_tokens.push_back(token(token::type::END_OF_FILE, "END_OF_FILE", m_pos));

    return 0;
}
