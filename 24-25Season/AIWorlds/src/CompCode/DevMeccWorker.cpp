#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Mecc_Worker
void pre_auton(void) {
}

void autonomous(void) {
}


void usercontrol(void) {
  while (1) {

    vex::wait(20, vex::msec);
  }
}

void periodic(void) {
  
}
#endif
