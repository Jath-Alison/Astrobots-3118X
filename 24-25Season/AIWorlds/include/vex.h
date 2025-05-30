#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

#include "v5.h"
#include "v5_vcs.h"


#define waitUntil(condition)                                                   \
  do {                                                                         \
    vex::wait(5, vex::msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

extern vex::competition Competition;
extern vex::brain Brain;
extern vex::controller Controller1;

void pre_auton(void);
void autonomous(void);
void usercontrol(void);
void periodic(void);

extern vex::thread periodicThread;

extern std::string RobotName;