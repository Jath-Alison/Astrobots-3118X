/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      4/9/2024, 9:37:21 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robotConfig.h"
#include <iostream>

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

void pre_auton(void)
{

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

void autonomous(void)
{
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

void usercontrol(void)
{

	waitUntil(smartDrive.m_inert.isCalibrating() == false);

	Jath::Vec2 origin = Jath::XandY(0, 0);

	smartDrive.m_pos = Jath::XandY(Jath::Tiles(-1), Jath::Tiles(-1));
	smartDrive.m_dir = Jath::Degrees(90);

	// User control code here, inside the loop
	while (1)
	{
		if (controller1.ButtonR1.pressing())
		{
			intake.set(100);
		}
		else if (controller1.ButtonR2.pressing())
		{
			intake.set(-100);
		}
		else if (controller1.ButtonR1.RELEASED)
		{
			intake.set(50);
		}
		else if (controller1.ButtonR2.RELEASED)
		{
			intake.set(0);
		}

		if (controller1.ButtonL1.pressing())
		{
			smartDrive.arcade(0, controller1.Axis3.position() / 2.f, controller1.Axis1.position() / 3.f);
		}
		else
		{
			smartDrive.LeftSplitArcade(controller1);
		}

		std::cout << "Base Pos:" << ": \n" <<
		 "\t x(in) : " << Jath::Distance( smartDrive.m_pos.x ).inches() << "\n" <<
		 "\t y(in) : " <<  Jath::Distance( smartDrive.m_pos.y ).inches() << "\n" <<
		 "\t dir(deg) : " << smartDrive.m_dir.degrees() << "\n" <<
		 "\t rotPos : " << (smartDrive.m_tracker.m_travelDistance.inches()) << "\n" ;


		wait(20, msec); // Sleep the task for a short amount of time to
						// prevent wasted resources.
	}
}

void track(){
	smartDrive.track();
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
	vex::thread tracking(track);

	// Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	// Run the pre-autonomous function.
	pre_auton();

	// Prevent main from exiting with an infinite loop.
	while (true)
	{
		wait(100, msec);
	}
}
