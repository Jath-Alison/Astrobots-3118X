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

void leftAwp()
{
	waitUntil(smartDrive.m_inert.isCalibrating() == false);

	smartDrive.m_pos = Jath::XandY(Jath::Inches(-36.75), Jath::Inches(-47.5));
	smartDrive.m_dir = Jath::Degrees(0);

	odomRetract.set(!true);
	climbUp.set(true);
	climbDown.set(false);

	smartDrive.turnTo(Jath::Degrees(-30));

	smartDrive.driveTo(Jath::Inches(18));
	intake.set(-100);

	// smartDrive.arcade(0, 60, 50);
	vex::wait(0.35, vex::sec);
	smartDrive.turnTo(0);

	smartDrive.arcade(0, -50, 0);
	leftWing.open();
	vex::wait(0.35, vex::sec);

	std::cout << "-----First Part Done-----\n";

	// std::cout << "location is: " <<  Jath::Distance(smartDrive.m_pos.x).inches() <<"," << Jath::Distance(smartDrive.m_pos.y).inches() << "\n";

	Jath::Angle angleToPoint = smartDrive.m_pos.angleTo(Jath::XandY(Jath::Inches(-48), Jath::Inches(-60))) - Jath::Revolutions(0.5);
	// std::cout << "angle is: " << smartDrive.m_pos.angleTo(Jath::XandY(Jath::Inches(-48), Jath::Inches(-60))) << "\n";
	// std::cout << "angle is: " <<smartDrive.m_pos.angleTo(Jath::XandY(Jath::Inches(-48), Jath::Inches(-60))) - Jath::Revolutions(0.5) << "\n";

	smartDrive.turnTo(angleToPoint);

	smartDrive.arcade(0, -60, 0);
	vex::wait(0.20, vex::sec);

	smartDrive.arcade(0, -35, -15);
	vex::wait(0.15, vex::sec);

	smartDrive.arcade(0, 0, -75);//scoooop
	vex::wait(1, vex::sec);
	leftWing.close();

	smartDrive.turnTo(Jath::Degrees(120));
	smartDrive.driveTo(Jath::Inches(15));

	smartDrive.turnTo(Jath::Degrees(95));
	smartDrive.driveTo(-Jath::Distance(smartDrive.m_pos.x + Jath::Inches(8)));
	std::cout << "----done ---- \n";
}

void rightAwp()
{
	waitUntil(smartDrive.m_inert.isCalibrating() == false);

	smartDrive.m_pos = Jath::XandY(Jath::Inches(36.75), Jath::Inches(-47.5));
	smartDrive.m_dir = Jath::Degrees(0);



	odomRetract.set(!true);
	climbUp.set(true);
	climbDown.set(false);

	smartDrive.driveToPoint(Jath::XandY(
		Jath::Inches(6),Jath::Inches(0)
	));

	// smartDrive.turnToFast(Jath::Degrees(45));
	leftWing.open();
	smartDrive.turnToFast(Jath::Degrees(90));

	intake.set(-100);
	smartDrive.driveToFast(Jath::Inches(24));
	
	smartDrive.arcade(0, 60, 0);
	vex::wait(0.35, vex::sec);
	smartDrive.arcade(0, -60, 0);
	vex::wait(0.35, vex::sec);
	smartDrive.arcade(0, 0, 0);

	Jath::Angle angleToPoint = smartDrive.m_pos.angleTo( 
		Jath::XandY(Jath::Inches(0), Jath::Inches(-48))
	 );

	smartDrive.turnTo(angleToPoint);

	smartDrive.arcade(0,30,0);
	
}

void waitAndClose(){
	wait(0.3, sec);
	rightWing.close();
	leftWing.close();
}
void rightRush()
{
	waitUntil(smartDrive.m_inert.isCalibrating() == false);

	smartDrive.m_pos = Jath::XandY(Jath::Inches(36.75), Jath::Inches(-47.5));
	smartDrive.m_dir = Jath::Degrees(0);


	odomRetract.set(!true);
	climbUp.set(true);
	climbDown.set(false);
	
	rightWing.open();vex::thread closeWings(waitAndClose);

	intake.set(100);
	smartDrive.driveToPoint(Jath::XandY(
		Jath::Inches(6),Jath::Inches(0)
	));
	intake.set(0);
	leftWing.open();

	// smartDrive.turnToFast(Jath::Degrees(45));
	smartDrive.turnToFast(Jath::Degrees(90));

	intake.set(-100);
	smartDrive.driveToFast(Jath::Inches(24));
	
	smartDrive.arcade(0, 60, 0);
	vex::wait(0.35, vex::sec);
	smartDrive.arcade(0, -60, 0);
	vex::wait(0.35, vex::sec);
	smartDrive.arcade(0, 0, 0);
	leftWing.close();

	Jath::Angle angleToPoint = smartDrive.m_pos.angleTo( 
		Jath::XandY(Jath::Inches(0), Jath::Inches(-24))
	 );

	smartDrive.turnTo(angleToPoint);

	intake.set(100);
	smartDrive.driveTo(smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(0), Jath::Inches(-24))) - Jath::Inches(3));
	intake.set(0);

	Jath::Angle angleToPoint2 = smartDrive.m_pos.angleTo( 
		Jath::XandY(Jath::Inches(60), Jath::Inches(-60))
	 ) - Jath::Revolutions(0.5);
	 smartDrive.turnTo(angleToPoint2);
	 smartDrive.driveTo(-(smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(60), Jath::Inches(-60))) - Jath::Inches(3)));

	leftWing.open();

	smartDrive.arcade(0, 0, -75);//scoooop
	vex::wait(0.7, vex::sec);
	leftWing.close();

	smartDrive.turnTo(Jath::Degrees(30));
	intake.set(-100);

	smartDrive.arcade(0,80,-25);
	vex::wait(0.4, vex::sec);

	smartDrive.arcade(0,-50,0);
	vex::wait(0.15, vex::sec);

	smartDrive.arcade(0,60,0);
	vex::wait(0.25, vex::sec);






	
}

void autonomous(void)
{
	// leftAwp();
	// rightAwp();
	rightRush();
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

	odomRetract.set(true);
	climbUp.set(true);
	climbDown.set(false);

	intake.set(0);

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
		}
		else if (controller1.ButtonX.pressing())
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

		if (controller1.ButtonLeft.PRESSED) // controller1.ButtonL1.pressing())
		{
			// odomRetract.close();
			// smartDrive.turnToFast( Jath::Degrees(90) );
			// smartDrive.driveToFast(Jath::Tiles(1));
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
		if (climblimit.pressing())
		{
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
