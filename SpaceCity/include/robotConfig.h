#pragma once

#include "vex.h"
#include "x/xMotor.h"
#include "x/TankDrive.h"
#include "x/SmartLeds.h"

extern vex::brain Brain;
extern vex::controller controller1;

extern x::Leds xleds;
extern addressable_led leds;

extern vex::motor leftMotorF;
extern vex::motor leftMotorM;
extern vex::motor leftMotorB;
extern vex::motor_group leftMotors;

extern vex::motor rightMotorF;
extern vex::motor rightMotorM;
extern vex::motor rightMotorB;
extern vex::motor_group rightMotors;

extern x::TankDrive drive;

extern x::xMotor intake;
extern x::xMotor flywheel;

extern vex::pneumatics wings;