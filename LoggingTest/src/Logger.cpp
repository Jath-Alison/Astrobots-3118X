#include "Logger.h"

auto start_time = std::chrono::high_resolution_clock::now();
auto current_time = std::chrono::high_resolution_clock::now();

float timePassed()
{
    current_time = std::chrono::high_resolution_clock::now();
    return float(std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() / 1000.f);
}

Logger::BoolLogValue::BoolLogValue(bool val)
{
    this->val = val;
}
Logger::IntLogValue::IntLogValue(int val)
{
    this->val = val;
}
Logger::DoubleLogValue::DoubleLogValue(double val)
{
    this->val = val;
}
Logger::StringLogValue::StringLogValue(std::string val)
{
    this->val = val;
}

Logger::LogEntry::LogEntry(double time, std::string seriesName, bool val)
{
    this->time = time;
    this->seriesName = seriesName;
    this->value = std::unique_ptr<BoolLogValue>(new BoolLogValue(val));
}
Logger::LogEntry::LogEntry(double time, std::string seriesName, int val)
{
    this->time = time;
    this->seriesName = seriesName;
    this->value = std::unique_ptr<IntLogValue>(new IntLogValue(val));
}
Logger::LogEntry::LogEntry(double time, std::string seriesName, double val)
{
    this->time = time;
    this->seriesName = seriesName;
    this->value = std::unique_ptr<DoubleLogValue>(new DoubleLogValue(val));
}
Logger::LogEntry::LogEntry(double time, std::string seriesName, std::string val)
{
    this->time = time;
    this->seriesName = seriesName;
    this->value = std::unique_ptr<StringLogValue>(new StringLogValue(val));
}

void Logger::putData(std::string seriesName, bool val)
{
    entries.push_back(LogEntry(timePassed(), seriesName, val));
}
void Logger::putData(std::string seriesName, int val)
{
    entries.push_back(LogEntry(timePassed(), seriesName, val));
}
void Logger::putData(std::string seriesName, double val)
{
    entries.push_back(LogEntry(timePassed(), seriesName, val));
}
void Logger::putData(std::string seriesName, std::string val)
{
    entries.push_back(LogEntry(timePassed(), seriesName, val));
}

void Logger::writeToFile(std::string fileName)
{
    std::ofstream file(fileName.c_str());

    file << "Time,Series,Value" << std::endl;

    for (size_t i = 0; i < entries.size(); i++)
    {
        file << entries[i].time << "," << entries[i].seriesName << ",";
        entries[i].value->writeValue(file);
        file << std::endl;
    }

    file.close();
    
}
