#pragma once

#include "vex.h"
#include "Jath\Jath.h"

extern vex::motor leftMotorA;
extern vex::motor leftMotorB;
extern vex::motor leftMotorC;
extern vex::motor leftMotorD;
extern vex::motor_group leftMotors;

extern vex::motor rightMotorA;
extern vex::motor rightMotorB;
extern vex::motor rightMotorC;
extern vex::motor rightMotorD;
extern vex::motor_group rightMotors;

extern vex::inertial inert;

extern Jath::TankDrive drive;
extern Jath::SmartDrive smartDrive;

extern Jath::jMotorGroup intake;


extern vex::message_link link;