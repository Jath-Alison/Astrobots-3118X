#pragma once

#include "vex.h"
#include "jwb/Utils.h"

extern vex::brain Brain;
extern vex::controller Controller;

extern jwb::SmartMotor LeftMotors;
extern jwb::SmartMotor RightMotors;

extern jwb::SmartMotor Flywheel;
extern jwb::SmartMotor Intake;

extern vex::pneumatics wings;
extern vex::pneumatics climb;

extern vex::inertial inert;
extern vex::gps GPS;

// extern jwb::RotationSensor Rotation;