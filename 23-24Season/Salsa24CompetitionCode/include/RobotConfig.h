#pragma once

#include "vex.h"
#include "Jath\Jath.h"

extern vex::motor leftMotorA;
extern vex::motor leftMotorB;
extern vex::motor leftMotorC;
extern vex::motor_group leftMotors;

extern vex::motor rightMotorA;
extern vex::motor rightMotorB;
extern vex::motor rightMotorC;
extern vex::motor_group rightMotors;

extern vex::inertial inert;

extern Jath::TankDrive drive;
extern Jath::SmartDrive smartDrive;

extern Jath::jMotorGroup shooter;

extern Jath::jMotorGroup intake;
extern Jath::jMotor leftFlapper;
extern Jath::jMotor rightFlapper;


extern vex::message_link link;