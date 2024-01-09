#pragma once

#include "vex.h"
#include "x/xMotor.h"
#include "x/TankDrive.h"
#include "x/SmartDrive.h"
#include "x/SmartLeds.h"
#include "Vision.h"

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

extern vex::inertial inert;

extern x::TankDrive drive;
extern x::SmartDrive smartDrive;


extern x::xMotor intake;
extern x::xMotor flywheel;

extern vex::pneumatics wings;
extern vex::pneumatics climb;

extern x::Vec2 initPos;
extern x::Angle initDir;

extern std::string AllianceColor;