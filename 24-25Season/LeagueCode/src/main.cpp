/**
 * @file main.cpp
 * @author Jath Alison (Jath.Alison@gmail.com)
 * @brief Source containing the main function and competition functions such as
 * auton and usercontrol
 * @version 1.0-beta
 * @date 06-25-2024
 *
 * @copyright Copyright (c) 2024
 *
 * This file is where the competition code is really running. All the Code for
 * the autonomous and usercontrol periods should be here as well as the set-up
 * during pre_auton.
 */

#include "vex.h"
#include "robotConfig.h"
#include "Art\ART.h"


/**
 * @brief A global instance of competition
 *
 * This object takes care of running the different Competition Tasks when
 * commands are recived from the field control.
 */
vex::competition Competition;

/**
 * @brief Runs after robot is powered on and before autonomous or usercontrol
 *
 * You may want to perform some actions before the competition starts. Do them
 * in the following function.  You must return from this function or the
 * autonomous and usercontrol tasks will not be started.  This function is only
 * called once after the V5 has been powered on and not every time that the
 * robot is disabled.
 *
 * Here, perform All activities that occur before the competition starts
 * Example: clearing encoders, setting servo positions, ...
 *
 */
void pre_auton(void)
{
}

void blueSoloAWP(){

	//Grab Goal1
	smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25),art::Tiles(-1.0));
	smartDrive.m_dir = art::Degrees(90);

	art::Vec2 travel = art::Vec2(art::Vec2::XandY(art::Tiles(1),art::Tiles(-1)) - smartDrive.m_pos);
	
	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	smartDrive.driveFor(travel.magnitude() * -.825, -35);
	clamp.set(true);
	smartDrive.arcade(0,0);
	
	//score preload
	intake.set(100);
	vex::wait(0.75, vex::sec);

	//Grab and score ring2
	travel = art::Vec2(art::Vec2::XandY(art::Tiles(1),art::Tiles(-2)) - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveFor(travel.magnitude() * .75, 35);
	smartDrive.arcade(0,0);

	vex::wait(1, vex::sec);

	//drop goal & drive to centerline
	travel = art::Vec2(art::Vec2::XandY(art::Tiles(2),art::Tiles(0)) - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveForPID(travel.magnitude() * 0.85);
	clamp.set(false);
	smartDrive.arcade(0,0);
	

	// Grab Goal2
	travel = art::Vec2(art::Vec2::XandY(art::Tiles(1),art::Tiles(1)) - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	// smartDrive.driveFor(travel.magnitude() * -.80, -50);//disabled to hard code instead

	smartDrive.turnToPID(art::Degrees(-45) + art::Degrees(180));
	smartDrive.driveFor(art::Inches(-30), -50);
	smartDrive.arcade(0,0);

	clamp.set(true);

	// // Grab ring2 and score

	smartDrive.turnToPID(art::Degrees(0));
	intake.set(100);
	smartDrive.driveFor(art::Inches(15), 50);
	smartDrive.arcade(0,0);
	vex::wait(0.35,vex::sec);
	smartDrive.driveFor(art::Inches(-24), -40);
	smartDrive.arcade(0,0);

	vex::wait(4,vex::sec);
	
	intake.set(0);
	smartDrive.arcade(0,0);
}
void redSoloAWP(){
	double xFlip = -1.0;

	//Grab Goal1
	smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25)*-1,art::Tiles(-1.0));
	smartDrive.m_dir = art::Degrees(90 *-1);

	art::Vec2 travel = art::Vec2(art::Vec2::XandY(art::Tiles(1)*-1,art::Tiles(-1)) - smartDrive.m_pos);
	
	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	smartDrive.driveFor(travel.magnitude() * -.825, -35);
	clamp.set(true);
	smartDrive.arcade(0,0);
	
	//score preload
	intake.set(100);
	vex::wait(0.75, vex::sec);

	//Grab and score ring2
	travel = art::Vec2(art::Vec2::XandY(art::Tiles(1)*-1,art::Tiles(-2)) - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveFor(travel.magnitude() * .75, 35);
	smartDrive.arcade(0,0);

	vex::wait(1, vex::sec);

	//drop goal & drive to centerline
	travel = art::Vec2(art::Vec2::XandY(art::Tiles(2)*-1,art::Tiles(0)) - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveForPID(travel.magnitude() * 0.85);
	clamp.set(false);
	smartDrive.arcade(0,0);
	

	// Grab Goal2
	travel = art::Vec2(art::Vec2::XandY(art::Tiles(1)*-1,art::Tiles(1)) - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	// smartDrive.driveFor(travel.magnitude() * -.80, -50);//disabled to hard code instead

	smartDrive.turnToPID(art::Degrees(-45*-1) + art::Degrees(180));
	smartDrive.driveFor(art::Inches(-30), -50);
	smartDrive.arcade(0,0);

	clamp.set(true);

	// // Grab ring2 and score

	smartDrive.turnToPID(art::Degrees(0));
	intake.set(100);
	smartDrive.driveFor(art::Inches(15), 50);
	smartDrive.arcade(0,0);
	vex::wait(0.45,vex::sec);
	smartDrive.driveFor(art::Inches(-24), -40);
	smartDrive.arcade(0,0);

	vex::wait(4,vex::sec);
	
	intake.set(0);
	smartDrive.arcade(0,0);
}

/**
 * @brief Runs the Autonomous Task
 *
 * This task is used to control your robot during the autonomous phase of a VEX
 * Competition.
 * You must modify the code to add your own robot specific commands here.
 *
 * Code here will run once and be stopped automatically when autonomous ends. It
 * is not guaranteed that the end of the function will be reached and if the end
 * is reached, the program will wait till the end of the autonomous period
 * without calling the function again.
 *
 */
void autonomous(void)
{
	while (smartDrive.m_inert.isCalibrating())
	{
		vex::wait(10, vex::msec);
	}
	
	Brain.Screen.setCursor(10,1);
	Brain.Screen.print("BlueAuto");
	blueSoloAWP();

	// Brain.Screen.setCursor(10,1);
	// Brain.Screen.print("RedAuto");
	// redSoloAWP();
}

/**
 * @brief Runs the User Control Task
 *
 * This task is used to control your robot during the user control phase of a
 * VEX Competition.
 * You must modify the code to add your own robot specific commands here.
 *
 * Code outside the loop will run once and can be used to configure the robot to
 * a starting state. Things like setting pneumatics to specific positions or
 * setting default values.
 *
 * Code inside the loop will run continuously until the usercontrol period ends.
 * Here, you should use values from the controller(s) to update the robot.
 *
 * A 20 millisecond sleep is included to prevent wasted resources while
 * repeating the loop.
 *
 */
void usercontrol(void)
{
	while (smartDrive.m_inert.isCalibrating())
	{
		vex::wait(10, vex::msec);
	}

	while (1)
	{

		smartDrive.LeftSplitArcadeCurved(Controller1);

		if(Controller1.ButtonR1.pressing()){
			intake.set(100);
		}else if (Controller1.ButtonR2.pressing()){
			intake.set(-100);
		}else{
			intake.set(0);
		}

		if(Controller1.ButtonL1.PRESSED){
			clamp.set(true);
		}else if (Controller1.ButtonL2.PRESSED){
			clamp.set(false);
		}

		if(Controller1.ButtonRight.PRESSED){
			// smartDrive.turnToPID(art::Degrees(90));
			smartDrive.driveForPID(art::Inches(5));
		}else if (Controller1.ButtonLeft.PRESSED){
			// smartDrive.turnToPID(art::Degrees(-90));
			smartDrive.driveForPID(art::Inches(-5));
		}

		vex::wait(20, vex::msec);
	}
}

int tracking(){
	smartDrive.track();
	return 1;
}

int displayLoop(){
	while(1){
		Brain.Screen.setCursor(1,1);
		Brain.Screen.print("X: %f", art::Length(smartDrive.m_pos.x).inches());
		Brain.Screen.setCursor(2,1);
		Brain.Screen.print("Y: %f", art::Length(smartDrive.m_pos.y).inches());
		Brain.Screen.setCursor(3,1);
		Brain.Screen.print("Rot: %f", art::Angle(smartDrive.m_dir).degrees());
	}
	return 1;
}

/**
 * @brief Sets up Competition Tasks and runs pre_auton
 *
 * All code is run from here, but you rarely need to add any code here. Main
 * sets up the competition tasks and calls pre_auton before allowing them to
 * run. Other than that, main just waits for either autonomous or usercontrol to
 * start by running an infinite loop.
 *
 * If you really want, code that needs to run once can be placed at the start of
 * main, but it is recommended you do that in pre_auton instead.
 *
 * @return int (doesn't actually return anything)
 */
int main()
{
	// Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	vex::task trackingThread(tracking);
	vex::task displayThread(displayLoop);

	// Run the pre-autonomous function.
	pre_auton();

	// Prevent main from exiting with an infinite loop.
	while (true)
	{
		vex::wait(100, vex::msec);
	}
}
