#pragma once

#include "vex.h"

double rateLimit(double rate, double target, double current);
double rateLimit(double rate, double target, double current, double dt);

double motionProfilePos(double maxVel, double maxAccel, double distance, double elapsedTime);
double motionProfileVel(double maxVel, double maxAccel, double distance, double elapsedTime);
double motionProfileAccel(double maxVel, double maxAccel, double distance, double elapsedTime);

