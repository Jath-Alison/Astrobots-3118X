#pragma once

#include "WPILogger.h"
#include "vex.h"

namespace logging
{

    extern WPILogger logger;

    // General Entries (Lol don't work)
    extern StringLogEntry console;
    extern StringLogEntry errors;
    extern StringLogEntry competitionState;
    extern StringLogEntry robotState;

    // Driver Entries
    extern Int64ArrayLogEntry Controller1_Axes;
    extern BooleanArrayLogEntry Controller1_Buttons;
    extern Int64ArrayLogEntry Controller1_Povs;

    // Logger Related Entries
    extern Int64LogEntry Logger_Size;
    extern Int64LogEntry Logger_Capacity;
    extern DoubleLogEntry Logger_TimeSinceLastLogged;

    int logLoop();
    extern vex::thread logThread;

} // namespace logging