/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      1/27/2024, 2:59:05 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "RobotConfig.h"
#include "SubAutons.h"
#include "Autons.h"
#include <iostream>

// using namespace vex;

// A global instance of competition
vex::competition Competition;

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

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  Skills();
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

void usercontrol(void) {
  // User control code here, inside the loop

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    LeftMotors.set( Controller.Axis3.position() + Controller.Axis1.position());
    RightMotors.set( Controller.Axis3.position() - Controller.Axis1.position());

    if(Controller.ButtonRight.pressing()){
      // Intake = 100;
      driveTo(jwb::Inches(10));
    }

    if (Controller.ButtonR1.pressing()) {
      Intake = 100;
    }else if (Controller.ButtonR2.pressing()){
      Intake = -100;
    }else if(Controller.ButtonR1.RELEASED ){
      Intake = 50;
    } else if(Controller.ButtonR2.RELEASED ){
      Intake = 0;
    }

    if (Controller.ButtonX.PRESSED) {
      Flywheel =  Flywheel + 10;
    }else if (Controller.ButtonB.PRESSED){
      Flywheel =  Flywheel - 10;
    }else if ( Controller.ButtonA.pressing()){
      Flywheel = 0;
    }

    if(Controller.ButtonLeft.pressing()){
      climb.open();
    }else{
      climb.close();
    }

    if(Controller.ButtonL2.pressing()){
      wings.open();
      climb.open();
    }else{
      wings.close();
      climb.close();
    }

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    jwb::SmartMotor::updateAllMotors();

    vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  
  vex::task updateMotors(updateMotorsTask);

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    vex::wait(100, vex::msec);
  }
}
