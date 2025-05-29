#pragma once

#include <string>

namespace logging
{

    enum EntryType
    {
        BOOLEAN,
        INT64,
        FLOAT,
        DOUBLE,
        STRING,
        BOOLEAN_ARR,
        INT64_ARR,
        FLOAT_ARR,
        DOUBLE_ARR,
        STRING_ARR,
    };

    class logEntry
    {
    public:
        virtual EntryType getType() = 0;
        int getId() { return id; }
        std::string getName() { return name; }

    protected:
        logEntry(EntryType type, std::string name) : id(++lastId), name(name) {}

    private:
        int id;

        std::string name;
        inline static int lastId = 0;
    };

    class BooleanLogEntry : public logEntry
    {
    public:
        BooleanLogEntry(std::string name) : logEntry(BOOLEAN, name) {}

        EntryType getType() { return BOOLEAN; }
    };

    class Int64LogEntry : public logEntry
    {
    public:
        Int64LogEntry(std::string name) : logEntry(INT64, name) {}

        EntryType getType() { return INT64; }
    };

    class FloatLogEntry : public logEntry
    {
    public:
        FloatLogEntry(std::string name) : logEntry(FLOAT, name) {}

        EntryType getType() { return FLOAT; }
    };

    class DoubleLogEntry : public logEntry
    {
    public:
        DoubleLogEntry(std::string name) : logEntry(DOUBLE, name) {}

        EntryType getType() { return DOUBLE; }
    };

    class StringLogEntry : public logEntry
    {
    public:
        StringLogEntry(std::string name) : logEntry(STRING, name) {}

        EntryType getType() { return STRING; }
    };
    class BooleanArrayLogEntry : public logEntry
    {
    public:
        BooleanArrayLogEntry(std::string name) : logEntry(BOOLEAN_ARR, name) {}

        EntryType getType() { return BOOLEAN_ARR; }
    };

    class Int64ArrayLogEntry : public logEntry
    {
    public:
        Int64ArrayLogEntry(std::string name) : logEntry(INT64_ARR, name) {}

        EntryType getType() { return INT64_ARR; }
    };
    class FloatArrayLogEntry : public logEntry
    {
    public:
        FloatArrayLogEntry(std::string name) : logEntry(FLOAT_ARR, name) {}

        EntryType getType() { return FLOAT_ARR; }
    };

    class DoubleArrayLogEntry : public logEntry
    {
    public:
        DoubleArrayLogEntry(std::string name) : logEntry(DOUBLE_ARR, name) {}

        EntryType getType() { return DOUBLE_ARR; }
    };

    class StringArrayLogEntry : public logEntry
    {
    public:
        StringArrayLogEntry(std::string name) : logEntry(STRING_ARR, name) {}

        EntryType getType() { return STRING_ARR; }
    };

} // namespace logging