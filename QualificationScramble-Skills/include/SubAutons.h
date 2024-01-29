#pragma once

#include "RobotConfig.h"
#include "vex.h"
#include "jwb\Utils.h"

void driveTo(jwb::Distance target);
void turnTo(jwb::Angle target);