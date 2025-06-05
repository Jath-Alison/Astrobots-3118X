#pragma once
#include "vex.h"
#include "ART/ART.h"

extern art::SimpleMotor armDeployMotor;
extern vex::message_link link;

void receive_message( const char *message, const char *linkname, int32_t index, double value );