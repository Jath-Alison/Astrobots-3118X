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

vex::gps GPS = vex::gps(vex::PORT14, -76.20, -127.00, vex::mm, 180);

// extern jwb::RotationSensor Rotation;