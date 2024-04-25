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

	smartDrive.m_pos = Jath::XandY(Jath::Tiles(0), Jath::Tiles(0));
	smartDrive.m_dir = Jath::Degrees(0);

	odomRetract.set(!true);
	climbUp.set(true);
	climbDown.set(false);

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
			intake.set(0);
		}
		else if (controller1.ButtonR2.RELEASED)
		{
			intake.set(0);
		}

		static bool climbUpb = false;

		if (controller1.ButtonA.PRESSED)
		{
			climbUp.set(true);
			climbDown.set(false);
			climbUpb = false;
		}else
		if (controller1.ButtonX.PRESSED)
		{
			climbUp.set(false);
			climbDown.set(false);
			climbUpb = true;
		}
		else if (controller1.ButtonB.PRESSED || (climblimit.pressing() && climbUpb))
		{
			climbUp.set(true);
			climbDown.set(true);
			climbUpb = false;
		}

		if (controller1.ButtonL1.PRESSED)
		{
			leftWing.set(true);
			rightWing.set(true);
		}
		else if (controller1.ButtonL1.RELEASED)
		{
			leftWing.set(false);
			rightWing.set(false);
		}

		static bool parking = false;
		if (controller1.ButtonL2.PRESSED)
		{
			parking = !parking;
		}
		park.set(parking);
		
		if (controller1.ButtonLeft.PRESSED)//controller1.ButtonL1.pressing())
		{
			// odomRetract.close();
			// smartDrive.turnTo( Jath::Degrees(90) );
			smartDrive.driveTo( Jath::Tiles(1) );
			// odomRetract.open();
		}
		
		smartDrive.LeftSplitArcadeCurved(controller1);

		

			// std::cout << "Base Pos:" << ": \n" <<
			//  "\t x(in) : " << Jath::Distance( smartDrive.m_pos.x ).inches() << "\n" <<
			//  "\t y(in) : " <<  Jath::Distance( smartDrive.m_pos.y ).inches() << "\n" <<
			//  "\t dir(deg) : " << smartDrive.m_dir.degrees() << "\n" <<
			//  "\t rotPos : " << (smartDrive.m_tracker.m_travelDistance.inches()) << "\n" ;

			Brain.Screen.clearScreen();
			Brain.Screen.setCursor(1, 1);
			Brain.Screen.print("x(t): %f", Jath::Distance(smartDrive.m_pos.x).inches());
			Brain.Screen.setCursor(2, 1);
			Brain.Screen.print("y(t): %f", Jath::Distance(smartDrive.m_pos.y).inches());
			Brain.Screen.setCursor(3, 1);
			Brain.Screen.print("r(d): %f", Jath::Angle(smartDrive.m_dir).degrees());

			Brain.Screen.setCursor(1, 15);
			Brain.Screen.print("x: %f", smartDrive.m_pos.x);
			Brain.Screen.setCursor(2, 15);
			Brain.Screen.print("y: %f", smartDrive.m_pos.y);
			Brain.Screen.setCursor(3, 15);
			Brain.Screen.print("l: %f", leftMotors.position(vex::deg));
			if(climblimit.pressing()){
				Brain.Screen.setCursor(4, 15);
				Brain.Screen.print("r: hihihih");
			}
		

		wait(20, msec); // Sleep the task for a short amount of time to
						// prevent wasted resources.
	}
}

void track()
{
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
