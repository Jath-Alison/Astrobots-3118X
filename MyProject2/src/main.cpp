/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 10, D        
// ClawMotor            motor         3               
// ArmMotor             motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

#include "robot-config.h"
// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int leftSide(){
  base.arcade(0, 100, 0);
  // intake.spin(fwd,12,volt);
  return 0;
}
int rightSide(){
  base.arcade(0,100,0);
  base.update();
  wait(2, seconds);
  base.arcade(0,0,0);
  base.update();
  return 0;
}

void autonomous(void) {
  // ..........................................................................
  rightSide();
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

double scale(double input){return .0001*pow(input, 3);}

void usercontrol(void) {

  double dScale = 1.125;
  double tScale = 1.0;

  // User control code here, inside the loop
  while (1) {

    base.arcade(Controller1.Axis4.position(), scale(Controller1.Axis3.position()*dScale),scale(Controller1.Axis1.position()*tScale));

    // if(Controller1.ButtonUp.PRESSED){dScale += 0.05;}
    // if(Controller1.ButtonDown.PRESSED){dScale -= 0.05;}

    // if(Controller1.ButtonX.PRESSED){tScale += 0.05;}
    // if(Controller1.ButtonB.PRESSED){tScale -= 0.05;}


    if(Controller1.ButtonR1.pressing()){
      cataLeft.set(15);
    }else if(Controller1.ButtonR2.pressing()){
      cataLeft.set(0);
    }else{
      // cataLeft.set(15);
    }
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(30, 30, 0, "%f",cataLeft.getOutput());
    Brain.Screen.printAt(30, 40, 0, "%f",cataLeft.get());
    Brain.Screen.printAt(30, 50, 0, "%f",cataRot.angle());
    cataLeft.update();
    cataRight.update();
    if(cataLeft.getOutput() < 0){
      cataLeft.stop();
      cataRight.stop();
    }

    if(Controller1.ButtonL1.pressing()){
      wings.open();
    }else{
      wings.close();
    }


    // This is the main execution loop for the user control program.
    // Each time through the loop your progra m should update motor + servo
    // values based on feedback from the joys ticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    base.update();
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
