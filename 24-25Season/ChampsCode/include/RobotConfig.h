/**
 * @file robotConfig.h
 * @author Jath Alison (Jath.Alison@gmail.com)
 * @brief Header declaring robot-configuring objects like Motors and other
 * Devices
 * @version 1.0-beta
 * @date 06-25-2024
 *
 * @copyright Copyright (c) 2024
 *
 * This file will declare all the devices that will be neccesary to write code
 * controlling the robot. This way, other files can know what motors, sensors
 * and important variables exist, allowing them to access, use, and modify them,
 * even though they are defined in a different file.
 */

#pragma once

#include "vex.h"
#include "ART/ART.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Arm.h"
#include "Subsystems/AsyncDrive.h"

extern vex::gps gpsSensorL;
extern vex::gps gpsSensorR;

extern vex::motor leftMotorA;
extern vex::motor leftMotorB;
extern vex::motor leftMotorC;
extern vex::motor_group leftMotors;

extern vex::motor rightMotorA;
extern vex::motor rightMotorB;
extern vex::motor rightMotorC;
extern vex::motor_group rightMotors;

extern vex::inertial inert;

extern art::TankDrive drive;
extern art::SmartDrive smartDrive;
extern AsyncDrive asyncDrive;

// extern art::SimpleMotor intake;
extern Intake intake;

extern vex::digital_out clamp; extern bool clampState;

// extern art::SimpleMotor arm;
// extern vex::rotation armRot;
// extern art::PID armPID;

extern Arm arm;

extern vex::digital_out doinkerDeployR; extern bool doinkerDeployRState;
extern vex::digital_out doinkerDeployL; extern bool doinkerDeployLState;

extern vex::aivision FrontVision;
// extern vex::optical intakeOptical;
// extern vex::optical outtakeOptical;