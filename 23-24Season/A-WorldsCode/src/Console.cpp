#include "Console.h"
#include "robotConfig.h"

Console::Console(std::string filename) : m_file(filename)
{
}

std::stringstream& Console::get()
{
	return m_log;
}

int Console::writeToFile()
{
	if (!Brain.SDcard.isInserted())
	{
		std::cout << "no SD\n";
		return -1;
	}
	// std::ofstream outFile(m_file.c_str());
	// if (outFile.bad())
	// {
	// 	std::cout << m_file.c_str() << "is bad\n";
	// 	return -1;
	// }
	
	// Brain.SDcard.savefile(m_file.c_str(), (uint8_t *) "hello", sizeof(m_log.str()));
	std::cout << "file " << Brain.SDcard.exists(m_file.c_str()) << "\n";

	// outFile << m_log.str();

	// outFile.close();

	return 0;
}

