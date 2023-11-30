#pragma once

#include <functional>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

namespace x{

    float timePassed();

    class Logger
    {
    public:
        struct LogItem {
            std::string m_name;
            std::function <double(void)> m_callback;
        };

        Logger(std::string fileName);
        Logger(Logger& log);
        Logger& withLogItem(std::string name, std::function <double(void)> callback);

        void logHeader();
        void log();

    private:
        std::string m_fileName;
        std::vector <LogItem> m_logItems;
        std::ofstream m_file;
    };

}