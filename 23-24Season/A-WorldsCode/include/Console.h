#pragma once
#include <sstream>
#include <fstream>
#include <string>


class Console
{
public:
	Console(std::string filename);

	std::stringstream& get();

	int writeToFile();
private:
	std::string m_file;
	std::stringstream m_log;
};

