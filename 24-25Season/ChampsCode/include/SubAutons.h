#pragma once

#include "RobotConfig.h"

void zeroGyro();
extern bool gyroZeroed;

void ladyBrownMacroTest();

void localize(double scale);
extern bool localizing;