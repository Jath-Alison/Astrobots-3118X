#include "Logging/Logging.h"
#include "ART/Art.h"
// #include "RobotConfig.h"

namespace logging
{

    WPILogger logger;

    StringLogEntry console("General/Console");
    StringLogEntry errors("General/Errors");
    StringLogEntry competitionState("General/CompetitionState");
    StringLogEntry robotState("General/RobotState");

    Int64ArrayLogEntry Controller1_Axes("DS:joystick0/axes");         //
    BooleanArrayLogEntry Controller1_Buttons("DS:joystick0/buttons"); //
    Int64ArrayLogEntry Controller1_Povs("DS:joystick0/povs");         //

    Int64LogEntry Logger_Size("Logger/loggerSize");                                //
    Int64LogEntry Logger_Capacity("Logger/loggerCapacity");                        //
    DoubleLogEntry Logger_TimeSinceLastLogged("Logger/loggerTimeSinceLastLogged"); //


    auto last_logged = std::chrono::high_resolution_clock::now();
    auto current_time_logLoop = std::chrono::high_resolution_clock::now();

    uint64_t logTimePassed()
    {
        current_time_logLoop = std::chrono::high_resolution_clock::now();
        return uint64_t(std::chrono::duration_cast<std::chrono::microseconds>(current_time_logLoop - last_logged).count());
    }

    int logLoop()
    {
        logger.clearFile("ChampsCodeLog.wpilog");

        logger.logStringEntry(console, "Log Loop Started");

        logger.logStringEntry(console, "LogFile Cleared");

        std::vector<vex::motor *> baseMotors = {};

        while (true)
        {
            std::vector<int64_t> axesStates = {
                Controller1.Axis1.position(),
                Controller1.Axis2.position(),
                Controller1.Axis3.position(),
                Controller1.Axis4.position()};
            std::vector<bool> buttonStates = {
                Controller1.ButtonUp.pressing(),
                Controller1.ButtonRight.pressing(),
                Controller1.ButtonDown.pressing(),
                Controller1.ButtonLeft.pressing(),
                Controller1.ButtonX.pressing(),
                Controller1.ButtonA.pressing(),
                Controller1.ButtonB.pressing(),
                Controller1.ButtonY.pressing(),
                Controller1.ButtonL1.pressing(),
                Controller1.ButtonL2.pressing(),
                Controller1.ButtonR1.pressing(),
                Controller1.ButtonR2.pressing(),
            };
            std::vector<int64_t> povStates = {
                int64_t(art::Vec2::XandY(Controller1.Axis1.position(), Controller1.Axis2.position()).direction()),
                int64_t(art::Vec2::XandY(Controller1.Axis4.position(), Controller1.Axis3.position()).direction()),
            };

            logger.logInt64ArrayEntry(Controller1_Axes, axesStates);
            logger.logBooleanArrayEntry(Controller1_Buttons, buttonStates);
            logger.logInt64ArrayEntry(Controller1_Povs, povStates);
            

            if (Competition.AUTONOMOUS)
            {
                logger.logStringEntry(competitionState, "Auton Started");
            }
            if (Competition.DRIVER_CONTROL)
            {
                logger.logStringEntry(competitionState, "Driver Control Started");
            }
            if (Competition.DISABLED)
            {
                logger.logStringEntry(competitionState, "Robot Disabled");
            }

            if (logger.getDataSize() > 5000)
            {
                last_logged = std::chrono::high_resolution_clock::now();
                logger.writeToFile("ChampsCodeLog.wpilog");
            }
            logger.logInt64Entry(Logger_Capacity, logger.getCapacity());
            logger.logInt64Entry(Logger_Size, logger.getDataSize());
            logger.logDoubleEntry(Logger_TimeSinceLastLogged, logTimePassed());

            vex::wait(20, vex::msec);
        }

        return 0;
    }
    vex::thread logThread;

} // namespace logging