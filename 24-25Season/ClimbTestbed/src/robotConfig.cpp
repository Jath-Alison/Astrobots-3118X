/**
 * @file robotConfig.cpp
 * @author Jath Alison (Jath.Alison@gmail.com)
 * @brief Source defining objects that configure the robot such as the Brain,
 * Motors, and additional Devices
 * @version 1.0-beta
 * @date 06-26-2024
 *
 * @copyright Copyright (c) 2024
 *
 * This file will definine all the devices that were delcared in the various
 * headers. Anything that can be defined to change the the configuration of the
 * robot will be put here. This includes, but isn't limited to motors, sensors
 * and important variables.
 */

#include "robotConfig.h"
#include "ART/ART.h"

vex::brain Brain;
vex::controller Controller1;

vex::motor m1(vex::PORT8, !true);
vex::motor m2(vex::PORT9, true);

vex::motor m3(vex::PORT15, !false);
vex::motor m4(vex::PORT16, !false);
vex::motor m5(vex::PORT17, false);
vex::motor m6(vex::PORT18, false);
vex::motor m7(vex::PORT19, false);

art::SimpleMotorGroup motors(vex::motor_group(m1,m2,m3,m4,m5,m6,m7));