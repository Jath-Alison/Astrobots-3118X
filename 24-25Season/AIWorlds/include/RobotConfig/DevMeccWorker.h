#pragma once
#include "vex.h"
#include "ART/SimpleMotorGroup.h"


extern  vex::message_link link;

extern vex::inertial inert;

extern vex::motor mot_lf_a;
extern vex::motor mot_lf_b;
extern art::SimpleMotorGroup mot_lf;

extern vex::motor mot_lb_a;
extern vex::motor mot_lb_b;
extern art::SimpleMotorGroup mot_lb;

extern vex::motor mot_rf_a;
extern vex::motor mot_rf_b;
extern art::SimpleMotorGroup mot_rf;

extern vex::motor mot_rb_a;
extern vex::motor mot_rb_b;
extern art::SimpleMotorGroup mot_rb;


// art::HolonomicDrive holoDrive(
//   art::SimpleMotorGroup(vex::motor_group(mot_lf_a, mot_lf_b)),
//   art::SimpleMotorGroup(vex::motor_group(mot_lb_a, mot_lb_b)),
//   art::SimpleMotorGroup(vex::motor_group(mot_rf_a, mot_rf_b)),
//   art::SimpleMotorGroup(vex::motor_group(mot_rb_a, mot_rb_b))
// );

void receive_message( const char *message, const char *linkname, int32_t index, double value );