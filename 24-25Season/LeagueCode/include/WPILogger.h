#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <array>

uint64_t timePassed();

class WPILogger
{
public:
	void logHeader();

	/**
	* need these:
		boolean
		int64
		float
		double
		string
	* Don't need (yet)
		boolean[]
		int64[]
		float[]
		double[]
		string[]
	*/

	void startBooleanEntry(std::string name, int id);
	void startInt64Entry(std::string name, int id);
	void startFloatEntry(std::string name, int id);
	void startDoubleEntry(std::string name, int id);
	void startStringEntry(std::string name, int id);

	void startBooleanArrayEntry(std::string name, int id);
	void startInt64ArrayEntry(std::string name, int id);
	void startFloatArrayEntry(std::string name, int id);
	void startDoubleArrayEntry(std::string name, int id);
	void startStringArrayEntry(std::string name, int id);

	void logBooleanEntry(uint32_t id, uint64_t time, bool val);
	void logInt64Entry(uint32_t id, uint64_t time, int64_t val);
	void logFloatEntry(uint32_t id, uint64_t time, float val);
	void logDoubleEntry(uint32_t id, uint64_t time, double val);
	void logStringEntry(uint32_t id, uint64_t time, std::string val);

	void logBooleanArrayEntry(uint32_t id, uint64_t time, std::vector<bool> val);
	void logInt64ArrayEntry(uint32_t id, uint64_t time, std::vector<int64_t> val);
	void logFloatArrayEntry(uint32_t id, uint64_t time, std::vector<float> val);
	void logDoubleArrayEntry(uint32_t id, uint64_t time, std::vector<double> val);
	void logStringArrayEntry(uint32_t id, uint64_t time, std::vector<std::string> val);

	void clearFile(std::string filename);
	void writeToFile(std::string filename);
	size_t getDataSize();
	size_t getCapacity();
private:
	void startEntry(uint32_t id, uint32_t payloadSize, uint64_t time);
	void startDataEntry(std::string name, int id, std::string typeName);

	void addString(std::string s);
	int getmin(int64_t i);


	std::vector<unsigned char> m_data;
};

