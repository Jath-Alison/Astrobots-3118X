/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\jatha                                            */
/*    Created:      Tue Aug 01 2023                                           */
/*    Description:  Shades V5 Project                                         */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "Shades\Shades.h"

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
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {

  const char * xml = R"(
    <?xml version="1.0" encoding="utf-8"?>
    <root>
      <shades>
        <screen id="home">
          <box id="box" x="0" y="0" width="480" height="240" callback="" color="0x4287F5FF"/>
          <text id="title" x="15" y="15" text="3118B - Astrobots" color="0xFCB040FF" />
          <text id="title" x="15" y="45" text="Shades" color="0xFCB040FF" />

          <image id="0" x="7" y="107" src="AstrobotsLogo.png" callback="" />

          <box id="auton_button" x="260" y="15" width="200" height="60" color="0xFFFFFFFF" callback="auton" />
          <text id="0" x="275" y="25" text="Auton Select" color="0x000000FF" callback="" />

          <box id="stats_home_button" x="260" y="90" width="200" height="60" color="0xFFFFFFFF" callback="stats_home" />
          <text id="0" x="275" y="100" text="Robot Stats" color="0x000000FF" callback="" />

          <box id="0" x="260" y="165" width="200" height="60" color="0xFFFFFFFF" callback="" />
          <text id="programData" x="260" y="175" text="" color="0x000000FF" callback="" />
        </screen>
        
        <screen id="auton">
          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <text id="autonDisplay" x="55" y="5" text="Auton Selector" color="0xFCB040FF" callback="" />

          <box id="0" x="15" y="65" width="130" height="72" color="0xFF0000FF" callback="" />
          <box id="0" x="15" y="152" width="130" height="72" color="0xFF0000FF" callback="" />

          <image id="fieldImage" x="160" y="65" src="Over Under field.png" callback="" />

          <box id="0" x="335" y="65" width="130" height="72" color="0x0000FFFF" callback="" />
          <box id="0" x="335" y="152" width="130" height="72" color="0x0000FFFF" callback="" />
        </screen>

        <screen id="stats_home">
          <box id="0" x="0" y="0" width="480" height="50" color="0xFF0000FF" callback="" />
          <text id="0" x="65" y="15" text="Motor Temperature" color="0x000000FF" callback="" />

          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <image id="Motor1" x="17" y="50" src="Motor.png" callback="" />
          <image id="Motor2" x="125" y="50" src="Motor.png" callback="" />
          <image id="Motor3" x="234" y="50" src="Motor.png" callback="" />
          <image id="Motor4" x="343" y="50" src="Motor.png" callback="" />

          <image id="Motor5" x="17" y="144" src="Motor.png" callback="" />
          <image id="Motor6" x="125" y="144" src="Motor.png" callback="" />
          <image id="Motor7" x="234" y="144" src="Motor.png" callback="" />
          <image id="Motor8" x="343" y="144" src="Motor.png" callback="" />
          
          <text id="0" x="20" y="110" text="Left-F" color="0xFFFFFFFF" callback="" />
          <text id="0" x="128" y="110" text="Right-F" color="0xFFFFFFFF" callback="" />
          <text id="0" x="237" y="110" text="Intake-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="346" y="110" text="Intake-L" color="0xFFFFFFFF" callback="" />
          
          <text id="0" x="20" y="204" text="Left-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="128" y="204" text="Right-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="237" y="204" text="Catapult" color="0xFFFFFFFF" callback="" />
          <text id="0" x="346" y="204" text="Climb" color="0xFFFFFFFF" callback="" />

          <box id="0" x="450" y="60" width="30" height="120" color="0xFFFFFFFF" callback="stats_extend" />

        </screen>
        <screen id="stats_extend">
          <box id="0" x="0" y="0" width="480" height="50" color="0xFF0000FF" callback="" />
          <text id="0" x="65" y="15" text="Location Stats" color="0x000000FF" callback="" />

          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <box id="0" x="0" y="60" width="30" height="120" color="0xFFFFFFFF" callback="stats_home" />
        </screen>
      </shades>
    </root>    
  )";
  std::cout<<"happened";

  if(Brain.SDcard.isInserted()){
    sds::Screen::initialize();
  }else{
    sds::Screen::initialize(xml);
  }

  vex::thread eventThread(sds::Screen::eventLoop);
  vex::thread displayThread(sds::Screen::displayLoop);

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

