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
#include "Art\ART.h"
#include "WPILogger.h"

extern WPILogger logger;

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

extern art::SimpleMotor intake;
extern vex::digital_out clamp;