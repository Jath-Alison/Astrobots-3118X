#include "Logger.h"

auto start_time = std::chrono::high_resolution_clock::now();
auto current_time = std::chrono::high_resolution_clock::now();

float timePassed() {
    current_time = std::chrono::high_resolution_clock::now();
    return float(std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() / 1000.f);
}

Logger::Logger(std::string fileName) : m_fileName(fileName)
{
}

Logger::Logger(Logger& log) : m_fileName(log.m_fileName), m_logItems(log.m_logItems)
{
}

Logger& Logger::withLogItem(std::string name, std::function<float(void)> callback)
{
	LogItem temp;
	temp.m_name = name;
	temp.m_callback = callback;
	m_logItems.push_back(temp);
    return *this;
}

void Logger::logHeader()
{
    m_file.open(m_fileName.c_str(), std::ios_base::trunc);
    for (size_t i = 0; i < m_logItems.size(); i++) {
        m_file << m_logItems[i].m_name;
        if (!(i == m_logItems.size() - 1)) {
            m_file << ",";
        }
    }
    m_file << std::endl;
    m_file.close();
}

void Logger::log()
{
    m_file.open(m_fileName.c_str(), std::ios_base::app);
    for (size_t i = 0; i < m_logItems.size(); i++) {
        m_file << m_logItems[i].m_callback();
        if (!(i == m_logItems.size() - 1)) {
            m_file << ",";
        }
    }
    m_file << std::endl;
    m_file.close();
}
