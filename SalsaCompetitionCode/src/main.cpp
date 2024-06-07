/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      6/6/2024, 3:42:38 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <string>
#include <fstream>
#include <sstream>

#include "RobotConfig.h"

#include "Jath\Vec2.h"
#include "Jath\Path.h"
#include "Jath\Motors\jMotorGroup.h"
#include "Jath\Graph.h"

#include "Command.h"

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

void pre_auton(void)
{

    // All activities that occur before the competition starts
    // Example: clearing encoders, setting servo positions, ...
}

void auto_isolation(void) {}

void auto_interaction(void) {}

bool firstAutoFlag = true;

void autonomous_main(void)
{
    if (firstAutoFlag)
    {
        firstAutoFlag = false;
        auto_isolation();
    }
    else
    {
        auto_interaction();
    }
}

void usercontrol(void)
{
    // User control code here, inside the loop
    while (1)
    {

        smartDrive.LeftSplitArcadeCurved(controller1);

        if (controller1.ButtonR1.pressing())
        {
            intake.set(100);
        }
        else if (controller1.ButtonR2.pressing())
        {
            intake.set(-100);
        }
        else
        {
            intake.set(0);
        }

        vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
                                  // prevent wasted resources.
    }
}

void track() { smartDrive.track(); }

int main()
{
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous_main);
    Competition.drivercontrol(usercontrol);

    vex::thread tracking(track);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true)
    {
        vex::wait(100, vex::msec);
    }
}
