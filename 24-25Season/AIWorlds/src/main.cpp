/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      5/29/2025, 3:27:48 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

vex::competition Competition;
vex::brain Brain;
vex::controller Controller1;

void pre_auton(void) {
}

void autonomous(void) {
}


void usercontrol(void) {
  while (1) {

    vex::wait(20, vex::msec);
  }
}


int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    vex::wait(100, vex::msec);
  }
}
