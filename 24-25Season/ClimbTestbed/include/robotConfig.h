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

extern vex::motor m1;
extern vex::motor m2;

extern vex::motor m3;
extern vex::motor m4;
extern vex::motor m5;
extern vex::motor m6;
extern vex::motor m7;

extern art::SimpleMotorGroup motors;