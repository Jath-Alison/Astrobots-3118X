#pragma once

#include "RobotConfig.h"
#include "vex.h"
#include "jwb\Utils.h"

void arcade(double drive, double rot);
void arcadeFor(double drive, double rot, double time);

void driveTo(jwb::Distance target);
void turnTo(jwb::Angle target);