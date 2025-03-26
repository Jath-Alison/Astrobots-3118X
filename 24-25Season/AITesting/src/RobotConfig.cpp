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

vex::inertial inert (vex::PORT18);

vex::motor mot_lf_a(vex::PORT20, !true);
vex::motor mot_lf_b(vex::PORT19, !false);
vex::motor mot_lb_a(vex::PORT10, !!false);
vex::motor mot_lb_b(vex::PORT9, !!true);
vex::motor mot_rf_a(vex::PORT11, !false);
vex::motor mot_rf_b(vex::PORT12, !true);
vex::motor mot_rb_a(vex::PORT1, !!true);
vex::motor mot_rb_b(vex::PORT2, !!false);

art::HolonomicDrive holoDrive(
  art::SimpleMotorGroup(vex::motor_group(mot_lf_a, mot_lf_b)),
  art::SimpleMotorGroup(vex::motor_group(mot_lb_a, mot_lb_b)),
  art::SimpleMotorGroup(vex::motor_group(mot_rf_a, mot_rf_b)),
  art::SimpleMotorGroup(vex::motor_group(mot_rb_a, mot_rb_b))
);