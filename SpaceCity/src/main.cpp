/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      11/18/2023, 9:49:47 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <string>
#include "robotConfig.h"
#include "x/leds.h"
#include "Shades\Shades.h"

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

  // intake.spin(vex::fwd);
  // wait(.25,vex::sec);
  // intake.stop();

  // drive.arcade(0,75,0);
  // wait(1.5,vex::sec);
  // drive.arcade(0,-50,0);
  // wait(0.5,vex::sec);
  // drive.arcade(0,0,0);//right score 1 auton

  wings.open();
  drive.arcade(0,-35,0);
  wait(0.35,vex::sec);
  drive.arcade(0,-25,25);
  wait(.75,vex::sec);
  wings.close();
  drive.arcade(0,50,0);
  wait(.75,vex::sec);
  drive.arcade(0,0,0);

  intake.spin(vex::fwd, 5, vex::volt);
  wait(.25,vex::sec);
  intake.stop();

  drive.arcade(0,0,-35);
  wait(.35,vex::sec);
  drive.arcade(0,75,0);
  wait(.5,vex::sec);
  drive.arcade(0,0,-50);
  wait(.2,vex::sec);
  drive.arcade(0,20,0);
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

    // leds.clear();   

  while (1) {

    if (controller1.ButtonR1.pressing()) {
      leds.clear(vex::color::green);
      intake.set(100);
    }else if (controller1.ButtonR2.pressing()){
      leds.clear(vex::color::red);
      intake.set(-100);
    }else if(controller1.ButtonR1.RELEASED ){
      intake.set(50);
    } else if(controller1.ButtonR2.RELEASED ){
      intake.set(0);
    }
    
    if (controller1.ButtonX.PRESSED) {
      flywheel.set(flywheel.get()+10);
      // flywheel.spin(vex::fwd, 12, vex::volt);
    }else if (controller1.ButtonB.PRESSED){
      flywheel.set(flywheel.get()-10);
      // flywheel.spin(vex::fwd, 12, vex::volt);
    }else if ( controller1.ButtonA.pressing()){
      flywheel.set(0);
    }

    if(controller1.ButtonL1.pressing()){
      drive.arcade(0,controller1.Axis3.position()/2.f,controller1.Axis1.position()/3.f);
    }else{
      drive.LeftSplitArcade(controller1);
    }

    if(controller1.ButtonL2.PRESSED){
      wings.open();
    }else if(controller1.ButtonL2.RELEASED){
      wings.close();
    }

    // std::string output = "";
    // output = string_format("Hello World %d", flywheel.get());

    

    vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

  // drive.m_rotScale = [](double rot){}


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
