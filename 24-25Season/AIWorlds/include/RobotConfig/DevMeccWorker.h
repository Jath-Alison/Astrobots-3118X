#pragma once
#include "vex.h"
#include "ART/ART.h"


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

extern vex::gps leftGps;
extern vex::gps rightGps;

extern art::HolonomicDrive holoDrive;

extern art::Vec2 pos;

void receive_message( const char *message, const char *linkname, int32_t index, double value );