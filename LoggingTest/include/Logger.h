#pragma once

#include <functional>
#include <vector>
#include <string>
#include <chrono>
#include <memory>
#include <fstream>

float timePassed();

class Logger
{
public:
	struct LogValue
	{
		virtual void writeValue(std::ofstream &file) = 0;
	};

	struct BoolLogValue : public LogValue
	{
		bool val;
		BoolLogValue(bool val);
		void writeValue(std::ofstream &file) override { file << val; }
	};
	struct IntLogValue : public LogValue
	{
		int val;
		IntLogValue(int val);
		void writeValue(std::ofstream &file) override { file << val; }
	};
	struct DoubleLogValue : public Logger::LogValue
	{
		double val;
		DoubleLogValue(double val);
		void writeValue(std::ofstream &file) override { file << val; }
	};
	struct StringLogValue : public LogValue
	{
		std::string val;
		StringLogValue(std::string val);
		void writeValue(std::ofstream &file) override { file << val; }
	};

	struct LogEntry
	{
		double time; // store in seconds since start of program
		std::string seriesName;

		LogEntry(double time, std::string seriesName, bool val);
		LogEntry(double time, std::string seriesName, int val);
		LogEntry(double time, std::string seriesName, double val);
		LogEntry(double time, std::string seriesName, std::string val);

		std::unique_ptr<LogValue> value;
	};

	void putData(std::string seriesName, bool val);
	void putData(std::string seriesName, int val);
	void putData(std::string seriesName, double val);
	void putData(std::string seriesName, std::string val);

	void writeToFile(std::string fileName);

private:
	std::vector<LogEntry> entries;
};
