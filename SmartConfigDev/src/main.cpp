/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      1/15/2024, 6:19:25 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "RobotConfig.h"

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

  PID testPID = PID()
    .withConstants(.75, 0.01, 0.25)
    .withIntegralZone(20)
    .withTimeout(5)
    .withSettleZone(5)
    .withSettleTimeout(0.25);

  // testPID.setTimeout(5);
  // testPID.setIntegralZone(20);

  // testPID.setSettleZone(5);
  // testPID.setSettleTimeout(1);

  double target = 0;

  Rotation.setPosition(0, vex::deg);

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    
    if( Controller.ButtonY.PRESSED ){ Motor.set(Degrees( -90)); }
    if( Controller.ButtonX.PRESSED ){ Motor.set(Degrees( 0)); }
    if( Controller.ButtonA.PRESSED ){ Motor.set(Degrees( 90)); }
    if( Controller.ButtonB.PRESSED ){ Motor.set(Degrees( 180)); }

    // while ( !Motor.isCompleted() ){
    //   // double temp = testPID.calculate(target, Rotation.position(vex::degrees));
    //   // Motor.spin(vex::fwd, -temp * 12.f/100.f, vex::volt);
    //   Motor.update();
      
    //   Brain.Screen.clearScreen();
    //   int pos = 1;
    //   Brain.Screen.setCursor(pos, 1);
    //   Brain.Screen.print( "target:%f",Motor.get() );pos++;

    //   Brain.Screen.setCursor(pos, 1);
    //   Brain.Screen.print( "angle:%f",Rotation.position(vex::degrees) );pos++;

    //   Brain.Screen.setCursor(pos, 1);
    //   Brain.Screen.print( "error:%f",target - Rotation.position(vex::degrees) );pos++;

    //   Brain.Screen.setCursor(pos, 1);
    //   Brain.Screen.print( "outputRPM:%f",Motor.getOutput() );pos++;

    //   Brain.Screen.setCursor(pos, 1);
    //   Brain.Screen.print( "time:%f",testPID.timePassed() );pos++;

    //   Brain.Screen.setCursor(pos, 1);
    //   Brain.Screen.print( "timeSettled:%f",testPID.settledTimePassed() );pos++;

    //   Brain.Screen.setCursor(8, 5);
    //   Brain.Screen.print( "num Motors:%i",SmartMotor::m_allMotors.size() );

    //   vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
    // }

    Motor.update();


    Brain.Screen.clearScreen();
    int pos = 1;
    Brain.Screen.setCursor(pos, 10);
    Brain.Screen.print( "target:%f",double(Motor) );pos++;
    Brain.Screen.setCursor(pos, 10);
    Brain.Screen.print( "angle:%f",Rotation.getAngle() );pos++;
    Brain.Screen.setCursor(pos, 10);
    Brain.Screen.print( "error:%f",double(Motor) - Rotation.getAngle() );pos++;
    Brain.Screen.setCursor(pos, 10);
    Brain.Screen.print( "outputRPM:%f",Motor.getOutput() * 100.f/12.f);pos++;
    Brain.Screen.setCursor(pos, 10);
    Brain.Screen.print( "time:%f",testPID.timePassed() );pos++;
    Brain.Screen.setCursor(pos, 10);
    Brain.Screen.print( "timeSettled:%f",testPID.settledTimePassed() );pos++;

    Brain.Screen.setCursor(8, 5);
    Brain.Screen.print( "num Motors:%f",SmartMotor::m_allMotors.size() );

    vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
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
    vex::wait(100, vex::msec);
  }
}
