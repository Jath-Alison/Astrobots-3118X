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



int waitAndClose(){
	wait(0.3, sec);
	rightWing.close();
	leftWing.close();
	return 0;
}
int intakeTillBall(){
	intake.set(75);
	wait(0.25,sec);
	waitUntil(intake.current() > 1);
	wait(0.35,sec);
	intake.set(0);
	return 1;
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

	smartDrive.arcade(0, -40, 0);
	vex::wait(0.20, vex::sec);

	smartDrive.arcade(0, -25, -10);
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
	leftWing.close();

	Jath::Angle angleToPoint2 = smartDrive.m_pos.angleTo( 
		Jath::XandY(Jath::Inches(0), Jath::Inches(-24))
	 );

	smartDrive.turnTo(angleToPoint2);

	vex::thread intooking(intakeTillBall);
	smartDrive.driveTo(smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(0), Jath::Inches(-24))) - Jath::Inches(3));

	smartDrive.turnToFast(Jath::Degrees(30));

	smartDrive.driveToFast(Jath::Inches(24));// /`` shape
	smartDrive.turnToFast(Jath::Degrees(90));
	smartDrive.driveToFast(Jath::Inches(10));

	intake.set(-100);//push into goal	
	wait(0.125,sec);
	smartDrive.arcade(0, 60, 0);
	vex::wait(0.35, vex::sec);
	smartDrive.arcade(0, -60, 0);
	vex::wait(0.35, vex::sec);
	smartDrive.arcade(0, 0, 0);

	smartDrive.driveToPoint(Jath::XandY(Jath::Inches(12), Jath::Inches(-36)));

	Jath::Angle angleToPoint = smartDrive.m_pos.angleTo( 
		Jath::XandY(Jath::Inches(0), Jath::Inches(-48))
	 );

	smartDrive.turnTo(angleToPoint);

	smartDrive.arcade(0,30,0);
	
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

	vex::thread intooking1(intakeTillBall);
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

	vex::thread intooking2(intakeTillBall);
	smartDrive.driveTo(smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(0), Jath::Inches(-24))) - Jath::Inches(3));

	Jath::Angle angleToPoint2 = smartDrive.m_pos.angleTo( 
		Jath::XandY(Jath::Inches(60), Jath::Inches(-60))
	 ) - Jath::Revolutions(0.5);

	smartDrive.arcade(0,-10,0);
	wait(0.25, sec);

	 smartDrive.turnTo(angleToPoint2);
	 smartDrive.driveTo(-(smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(60), Jath::Inches(-60))) - Jath::Inches(8)));

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

void elimsRight()
{
	waitUntil(smartDrive.m_inert.isCalibrating() == false);

	odomRetract.set(!true);//odom retract out
	climbUp.set(true);
	climbDown.set(false);//climb nuetral
	
	//drive to border
	//spin and hit triball (open wingR, turn to other triball)
	//intake & spit barrier triball
	//return to corner
	//scoop
	//score preload, then scooped
	//grab last barrier ball
	//wings out, push all

	std::cout << "start :\n"
	<< "\tx: " << Jath::Distance(smartDrive.m_pos.x).inches() <<"\n"
	<< "\ty: " << Jath::Distance(smartDrive.m_pos.y).inches() <<"\n";

	///drive to border
	Jath::Distance distanceToBorderBall = smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(24), 0)) - Jath::Inches(8);
	smartDrive.driveToTuned(-distanceToBorderBall, Jath::Inches(2), 0.1);
	
	///spin and hit triball (open wingR, turn to other triball)
	rightWing.open();
	Jath::Angle angleToBarrierBall = Jath::Angle(smartDrive.m_pos.angleTo(Jath::XandY(Jath::Inches(3), 0)) + Jath::Degrees(-15));
	smartDrive.turnToTuned(angleToBarrierBall,Jath::Degrees(15));
	std::cout << "postSpin :\n"
	<< "\tx: " << Jath::Distance(smartDrive.m_pos.x).inches() <<"\n"
	<< "\ty: " << Jath::Distance(smartDrive.m_pos.y).inches() <<"\n";

	///intake & spit barrier triball
	rightWing.close();
	vex::thread intooking(intakeTillBall);

	Jath::Distance distanceToBarrierBall = smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(3), 0)) - Jath::Inches(5);
	smartDrive.driveToTuned(+distanceToBarrierBall,Jath::Inches(1.5));

	smartDrive.arcade(0, -70, 0);
	wait(0.20, sec);//back up

	smartDrive.turnToTuned(Jath::Degrees(90),Jath::Degrees(15));
	intake.set(-100);//turn and spit (with authority)
	std::cout << "spat :\n"
	<< "\tx: " << Jath::Distance(smartDrive.m_pos.x).inches() <<"\n"
	<< "\ty: " << Jath::Distance(smartDrive.m_pos.y).inches() <<"\n";

	wait(0.5,sec);

	///return to corner
	vex::thread intooking2(intakeTillBall);
	smartDrive.driveToPointTuned(Jath::XandY(
		Jath::Inches(54), Jath::Inches(-54)
	),Jath::Inches(4));//grabb preball
	std::cout << "cornered :\n"
	<< "\tx: " << Jath::Distance(smartDrive.m_pos.x).inches() <<"\n"
	<< "\ty: " << Jath::Distance(smartDrive.m_pos.y).inches() <<"\n";
	
	wait(0.3,sec);//wait for intake
	smartDrive.turnToTuned(Jath::Degrees(-90),Jath::Degrees((10)));
	
	///scoooop
	smartDrive.arcade(0,60,0);
	wait(0.3,sec);
	leftWing.open();//open scooper
	
	smartDrive.arcade(0, -50, -10);
	wait(0.35, sec);

	std::cout << "scooping :\n"
	<< "\tx: " << Jath::Distance(smartDrive.m_pos.x).inches() <<"\n"
	<< "\ty: " << Jath::Distance(smartDrive.m_pos.y).inches() <<"\n";

	smartDrive.arcade(0, 0, -60);
	wait(0.3, sec);//the scooping
	leftWing.close();//close scooper
	smartDrive.arcade(0, 0, 0);

	///score  preload and scooped
	smartDrive.turnToTuned(Jath::Degrees(30),Jath::Degrees((10)));

	intake.set(-100);
	smartDrive.arcade(0,70,0);
	vex::wait(0.4, vex::sec);
	
	smartDrive.arcade(0,0,0);
	wait(0.1,sec);

	smartDrive.arcade(0,-50,0);
	vex::wait(0.35, vex::sec);//pushing in//increase when tested

	std::cout << "pushed in :\n"
	<< "\tx: " << Jath::Distance(smartDrive.m_pos.x).inches() <<"\n"
	<< "\ty: " << Jath::Distance(smartDrive.m_pos.y).inches() <<"\n";

	///grab last barrier ball
	Jath::Angle angleTo2ndBarrierBall = smartDrive.m_pos.angleTo( 
		Jath::XandY(Jath::Inches(3), Jath::Inches(-24))
	 );

	smartDrive.turnToTuned(angleTo2ndBarrierBall,Jath::Degrees((10)));

	vex::thread intooking3(intakeTillBall);
	smartDrive.driveToTuned(smartDrive.m_pos.distTo(Jath::XandY(Jath::Inches(3), Jath::Inches(-24))) - Jath::Inches(6),Jath::Inches(2));

	std::cout << "lastBallIntook :\n"
	<< "\tx: " << Jath::Distance(smartDrive.m_pos.x).inches() <<"\n"
	<< "\ty: " << Jath::Distance(smartDrive.m_pos.y).inches() <<"\n";

	/// push all
	smartDrive.turnToTuned(Jath::Degrees(45),Jath::Degrees((10)));

	smartDrive.driveToFast(Jath::Inches(24));// /`` shape
	smartDrive.turnToTuned(Jath::Degrees(90),Jath::Degrees((10)));

	leftWing.open();
	rightWing.open();

	smartDrive.driveToFast(Jath::Inches(10));

	intake.set(-100);//push into goal	
	wait(0.125,sec);
	smartDrive.arcade(0, 60, 0);
	vex::wait(0.45, vex::sec);
	smartDrive.arcade(0, -60, 0);
	vex::wait(0.45, vex::sec);
	smartDrive.arcade(0, 0, 0);

}

int elimsRightCancelThread(){
	vex::thread elimsRightThread(elimsRight);
	while(true){
		if(controller1.ButtonRight.PRESSED){
			elimsRightThread.interrupt();
			smartDrive.arcade(0,0,0);
			break;
		}
	}
	return 1;
}

void autonomous(void)
{
	// leftAwp();
	// rightAwp();
	// rightRush();
	elimsRight();
}

// std::string currentAuton = "leftAwp";
// std::string currentAuton = "rightAwp";
// std::string currentAuton = "rightRush";
std::string currentAuton = "elimsRight";

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

	// odomRetract.set(true);
	climbUp.set(true);
	climbDown.set(false);

	// intake.set(10);

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
			// vex::thread intooking(intakeTillBall);
			elimsRightCancelThread();
		}

		smartDrive.LeftSplitArcadeCurved(controller1);

		// std::cout << "Base Pos:" << ": \n" <<
		//  "\t x(in) : " << Jath::Distance( smartDrive.m_pos.x ).inches() << "\n" <<
		//  "\t y(in) : " <<  Jath::Distance( smartDrive.m_pos.y ).inches() << "\n" <<
		//  "\t dir(deg) : " << smartDrive.m_dir.degrees() << "\n" <<
		//  "\t rotPos : " << (smartDrive.m_tracker.m_travelDistance.inches()) << "\n" ;

		wait(20, msec); // Sleep the task for a short amount of time to
						// prevent wasted resources.
	}
}

void print(){
	while(true){
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
		Brain.Screen.print("c: %f", intake.current());
		if (intake.current()>5)
		{
			Brain.Screen.setCursor(4, 15);
			Brain.Screen.print("r: hihihih");
		}

		Brain.Screen.setCursor(6, 1);
		Brain.Screen.print("Auton: %s", currentAuton.c_str());

		wait(20, msec);
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
	smartDrive.m_pos = Jath::XandY(Jath::Inches(36.75), Jath::Inches(-47.5));
	smartDrive.m_dir = Jath::Degrees(180);

	vex::thread tracking(track);
	vex::thread printing(print);

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
