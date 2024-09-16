#pragma once

#include <string>
#include "vex.h"
#include "Jath\Jath.h"
// #include "x/xMotor.h"
// #include "x/TankDrive.h"
// #include "x/SmartDrive.h"
// #include "x/SmartLeds.h"
#include "Vision.h"

extern vex::brain Brain;
extern vex::controller controller1;

// extern x::Leds xleds;
// extern addressable_led leds;

extern vex::motor leftMotorF;
extern vex::motor leftMotorM;
extern vex::motor leftMotorB;
extern vex::motor_group leftMotors;

extern vex::motor rightMotorF;
extern vex::motor rightMotorM;
extern vex::motor rightMotorB;
extern vex::motor_group rightMotors;

extern vex::inertial inert;

extern Jath::TankDrive drive;
extern Jath::SmartDrive smartDrive;

extern Jath::jMotorGroup intake;
// extern Jath::jMotor flywheel;

extern vex::pneumatics climbUp;
extern vex::pneumatics climbDown;

extern vex::pneumatics park;
extern vex::pneumatics odomRetract;
extern vex::pneumatics odomRetract;

extern vex::pneumatics leftWing;
extern vex::pneumatics rightWing;

extern vex::limit climblimit;

extern Jath::Vec2 initPos;
extern Jath::Angle initDir;

extern std::string AllianceColor;