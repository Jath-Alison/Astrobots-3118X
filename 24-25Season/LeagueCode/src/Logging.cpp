#include "Logging.h"

StringLogEntry console("Console");
StringLogEntry errors("Errors");
StringLogEntry competitionState("CompetitionState");
StringLogEntry robotState("RobotState");

FloatArrayLogEntry Controller_Axes("joystick0/Axes");
BooleanArrayLogEntry Controller_Buttons("joystick0/Buttons");