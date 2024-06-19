/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      6/17/2024, 4:36:25 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Jath\Graph.h"
#include "Jath\Motors\SmartMotor.h"

vex::brain Brain;
vex::controller Controller1;

Jath::SmartMotor s = Jath::SmartMotor("intake", vex::motor(vex::PORT1, vex::gearSetting::ratio6_1, true))
  .withControlMode(Jath::SmartMotor::ControlMode::VELOCITY)
  .withPID(
    Jath::PID()
    .withConstants(0.05, 0, 0)
  )
  .withFollower(vex::motor(vex::PORT8, vex::gearSetting::ratio6_1, false))
  ;

vex::task updateMotorLoopTask(Jath::updateMotorLoop);

using namespace vex;

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
  Jath::Graph g = Jath::Graph()
    .addDataset("cmd: ", [&](){ return Jath::Angle(s.get()).degrees() / 3600.f * 10; })
    .addDataset("feed: ", [&](){ return Jath::Angle(s.getFeedback()).degrees() / 3600.f * 10; })
    .addDataset("out: ", [&](){ return s.getOutput() / 12.f * 10; })
    .addDataset("v: ", [&](){ return s.voltage() / 12.f * 10; })
    ;
  while (1) {

    g.getData();

    if(Controller1.ButtonR1.pressing()){
      s.set(Jath::Revolutions(450) / 60);
      // s.set(1000);
    }else if(Controller1.ButtonR2.pressing()){
      s.set(Jath::Revolutions(-100) / 60);
    }else {
      s.set(0);
    }

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("out: %f", s.getOutput());
    g.drawGraph(Jath::Vec2::XandY(0,100),
                    Jath::Vec2::XandY(400,200));

    s.update();

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
