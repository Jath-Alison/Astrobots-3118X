#include "WPILogger.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include "vex.h"

WPILogger::WPILogger()
{}

WPILogger::WPILogger(std::string fileBaseName)
{
	std::stringstream name;
	int id = 0;

	if (Brain.SDcard.isInserted())
	{

		name << fileBaseName << id;
		
		while (Brain.SDcard.exists(name.str().c_str()))
		{
			name.clear();
			id++;
			name << fileBaseName << id;
		}

		name << ".wpilog";

		m_fileName = name.str();
	}else{
		m_fileName = fileBaseName + ".wpilog";
	}
}

void WPILogger::logHeader()
{
	m_data.push_back('W');
	m_data.push_back('P');
	m_data.push_back('I');
	m_data.push_back('L');
	m_data.push_back('O');
	m_data.push_back('G');

	m_data.push_back(0x00);
	m_data.push_back(0x01);
	m_data.push_back(0x00);
	m_data.push_back(0x00);
	m_data.push_back(0x00);
	m_data.push_back(0x00);
}

void WPILogger::startEntry(uint32_t id, uint32_t payloadSize, uint64_t time)
{
	unsigned char headerBitmap = 0b00000000;

	int minIdSize = getmin(id);
	headerBitmap = headerBitmap | ((minIdSize - 1) & 0xFF);

	int minPayloadSize = getmin(payloadSize);
	headerBitmap = headerBitmap | (((minPayloadSize - 1) << 2) & 0xFF);

	int minTimeSize = getmin(time);
	headerBitmap = headerBitmap | (((minTimeSize - 1) << 4) & 0xFF);

	m_data.push_back(headerBitmap);
	m_data.push_back(id); // Entry id 0

	for (size_t i = 0; i < minPayloadSize; i++)
	{
		unsigned char temp = payloadSize >> (8 * i) & 0xff;
		m_data.push_back(temp);
	}

	for (size_t i = 0; i < minTimeSize; i++)
	{
		unsigned char temp = time >> (8 * i);
		m_data.push_back(temp);
	}
}

void WPILogger::startDataEntry(std::string name, int id, std::string typeName)
{
	std::vector<char> tempVector;

	tempVector.push_back(0x00); // record type start

	for (size_t i = 0; i < 4; i++) // default 4 bytes to store new ID
	{
		unsigned char temp = id >> (8 * i);
		tempVector.push_back(temp);
	}

	for (size_t i = 0; i < 4; i++) // default 4 bytes to store name length
	{
		unsigned char temp = name.size() >> (8 * i);
		tempVector.push_back(temp);
	}
	for (size_t i = 0; i < name.size(); i++) // Add name itself
	{
		tempVector.push_back(name[i]);
	}

	std::string type = typeName;
	for (size_t i = 0; i < 4; i++) // default 4 bytes to store type name length
	{
		unsigned char temp = type.size() >> (8 * i);
		tempVector.push_back(temp);
	}
	for (size_t i = 0; i < type.size(); i++) // Add type name itself
	{
		tempVector.push_back(type[i]);
	}

	std::string meta = "";
	for (size_t i = 0; i < 4; i++) // default 4 bytes to store meta length
	{
		unsigned char temp = meta.size() >> (8 * i);
		tempVector.push_back(temp);
	}
	for (size_t i = 0; i < meta.size(); i++) // Add meta itself
	{
		tempVector.push_back(meta[i]);
	}

	startEntry(0, tempVector.size(), timePassed());
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::startBooleanEntry(std::string name, int id)
{
	startDataEntry(name, id, "boolean");
}
void WPILogger::startInt64Entry(std::string name, int id)
{
	startDataEntry(name, id, "int64");
}
void WPILogger::startFloatEntry(std::string name, int id)
{
	startDataEntry(name, id, "float");
}

void WPILogger::startDoubleEntry(std::string name, int id)
{
	startDataEntry(name, id, "double");
}

void WPILogger::startStringEntry(std::string name, int id)
{
	startDataEntry(name, id, "string");
}

void WPILogger::startBooleanArrayEntry(std::string name, int id)
{
	startDataEntry(name, id, "boolean[]");
}

void WPILogger::startInt64ArrayEntry(std::string name, int id)
{
	startDataEntry(name, id, "int64[]");
}

void WPILogger::startFloatArrayEntry(std::string name, int id)
{
	startDataEntry(name, id, "float[]");
}

void WPILogger::startDoubleArrayEntry(std::string name, int id)
{
	startDataEntry(name, id, "double[]");
}

void WPILogger::startStringArrayEntry(std::string name, int id)
{
	startDataEntry(name, id, "string[]");
}

void WPILogger::logBooleanEntry(uint32_t id, uint64_t time, bool val)
{
	std::vector<char> tempVector;

	int minValSize = sizeof(val); // int64 uses 8 bytes

	for (size_t i = 0; i < minValSize; i++)
	{
		unsigned char temp = val >> (8 * i);
		tempVector.push_back(temp);
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logInt64Entry(uint32_t id, uint64_t time, int64_t val)
{
	std::vector<char> tempVector;

	int minValSize = sizeof(val); // int64 uses 8 bytes

	for (size_t i = 0; i < minValSize; i++)
	{
		unsigned char temp = val >> (8 * i);
		tempVector.push_back(temp);
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logFloatEntry(uint32_t id, uint64_t time, float val)
{
	std::vector<char> tempVector;

	int minValSize = sizeof(val); // int64 uses 8 bytes

	char dest[100];

	memcpy(dest, &val, minValSize);

	for (size_t i = 0; i < minValSize; i++)
	{

		tempVector.push_back(dest[i]);
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logDoubleEntry(uint32_t id, uint64_t time, double val)
{
	std::vector<char> tempVector;

	int minValSize = sizeof(val); // int64 uses 8 bytes

	char dest[100];

	memcpy(dest, &val, minValSize);

	for (size_t i = 0; i < minValSize; i++)
	{

		tempVector.push_back(dest[i]);
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logStringEntry(uint32_t id, uint64_t time, std::string val)
{
	std::vector<char> tempVector;

	int minValSize = sizeof(val); // int64 uses 8 bytes

	for (size_t i = 0; i < val.size(); i++)
	{
		tempVector.push_back(val[i]);
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logBooleanArrayEntry(uint32_t id, uint64_t time, std::vector<bool> val)
{
	std::vector<char> tempVector;

	for (size_t i = 0; i < val.size(); i++)
	{
		for (size_t j = 0; j < sizeof(bool); j++)
		{
			char temp = val[i] >> (8 * j);
			tempVector.push_back(temp);
		}
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logInt64ArrayEntry(uint32_t id, uint64_t time, std::vector<int64_t> val)
{
	std::vector<char> tempVector;

	for (size_t i = 0; i < val.size(); i++)
	{
		for (size_t j = 0; j < sizeof(int64_t); j++)
		{
			unsigned char temp = val[i] >> (8 * j);
			tempVector.push_back(temp);
		}
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logFloatArrayEntry(uint32_t id, uint64_t time, std::vector<float> val)
{
	std::vector<char> tempVector;

	int minValSize = sizeof(float); // int64 uses 8 bytes

	for (size_t i = 0; i < val.size(); i++)
	{
		char dest[100];

		memcpy(dest, &val[i], minValSize);

		for (size_t j = 0; j < minValSize; j++)
		{

			tempVector.push_back(dest[j]);
		}
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logDoubleArrayEntry(uint32_t id, uint64_t time, std::vector<double> val)
{
	std::vector<char> tempVector;

	int bitCount = sizeof(double);

	for (size_t i = 0; i < val.size(); i++)
	{

		char dest[100];
		bool extra = false;

		memcpy(dest, &val[i], bitCount);

		size_t j = 0;
		double floored = floor(val[i]);

		for (; j < bitCount; j++)
		{
			tempVector.push_back(dest[j]);
		}
	}

	startEntry(id, tempVector.size(), time);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		m_data.push_back(tempVector[i]);
	}
}

void WPILogger::logStringArrayEntry(uint32_t id, uint64_t time, std::vector<std::string> val)
{
}

void WPILogger::clearFile()
{
	if (Brain.SDcard.isInserted())
	{
		std::ofstream out(m_fileName.c_str());
		out.close();
	}
}

void WPILogger::clearFile(std::string filename)
{
	if (Brain.SDcard.isInserted())
	{
		std::ofstream out(filename.c_str());
		out.close();
	}
}

void WPILogger::writeToFile()
{
	if (Brain.SDcard.isInserted())
	{
		std::ofstream out(m_fileName.c_str(), std::ios_base::app);
		for (size_t i = 0; i < m_data.size(); i++)
		{
			out << m_data[i];
		}
		out.close();
	}

	m_data.clear();
}

void WPILogger::writeToFile(std::string filename)
{
	if (Brain.SDcard.isInserted())
	{
		std::ofstream out(filename.c_str(), std::ios_base::app);
		for (size_t i = 0; i < m_data.size(); i++)
		{
			out << m_data[i];
		}
		out.close();
	}

	m_data.clear();
}

size_t WPILogger::getDataSize()
{
	return m_data.size();
}

size_t WPILogger::getCapacity()
{
	return m_data.capacity();
}

void WPILogger::addString(std::string s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		m_data.push_back(s[i]);
	}
}

int WPILogger::getmin(int64_t i)
{
	if (i == (int8_t)(i & 0xFF))
		return 1;
	if (i == (int16_t)(i & 0xFFFF))
		return 2;
	if (i == (int32_t)(i & 0xFFFFFF))
		return 3;
	if (i == (int32_t)(i & 0xFFFFFFFF))
		return 4;
	if (i == (int32_t)(i & 0xFFFFFFFFFFFF))
		return 6;
	if (i == (int64_t)(i & 0xFFFFFFFFFFFFFFFF))
		return 8;
	return 8;
}

auto start_time = std::chrono::high_resolution_clock::now();
auto current_time = std::chrono::high_resolution_clock::now();

uint64_t timePassed()
{
	current_time = std::chrono::high_resolution_clock::now();
	return uint64_t(std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time).count());
}
