#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Mecc_Worker
void pre_auton(void) {
  RobotName = "Dev_Mecc_Worker";
}

void autonomous(void) {
}


void usercontrol(void) {
  while (1) {

    if (Controller1.ButtonA.pressing()) {
      mot_lf.spin(vex::fwd, 50, vex::percent);
      mot_lb.spin(vex::fwd, 50, vex::percent);
      mot_rf.spin(vex::fwd, 50, vex::percent);
      mot_rb.spin(vex::fwd, 50, vex::percent);
    } else if (Controller1.ButtonB.pressing()) {
      mot_lf.stop();
      mot_lb.stop();
      mot_rf.stop();
      mot_rb.stop();
    } else if (Controller1.ButtonX.pressing()) {
      mot_lf.spin(vex::fwd, -50, vex::percent);
      mot_lb.spin(vex::fwd, -50, vex::percent);
      mot_rf.spin(vex::fwd, -50, vex::percent);
      mot_rb.spin(vex::fwd, -50, vex::percent);
    }
    

    vex::wait(20, vex::msec);
  }
}

void periodic(void) {
  while (1)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(RobotName.c_str());

    Brain.Screen.setCursor(2, 1);//time
    Brain.Screen.print("Time: %d:%02d", (int)vex::timer::system() / (60 * 1000), (int)vex::timer::system() % (60 * 1000));

    
    
    vex::wait(20, vex::msec);
  }
}
#endif
