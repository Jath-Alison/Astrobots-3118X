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
#include "Art/ART.h"
#include "robotConfig.h"
#include "Logging/WPILogger.h"
#include "Logging/Logging.h"
#include "Shades/Shades.h"

#include "ART/Jath/Path.h"
#include <vector>
#include "AutonSelect.h"

/**
 * @brief A global instance of competition
 *
 * This object takes care of running the different Competition Tasks when
 * commands are received from the field control.
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
	// intakeOptical.integrationTime(5);
	// outtakeOptical.integrationTime(5);
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

	while (inert.isCalibrating())
	{
		vex::wait(10, vex::msec);
	}

	autonSelect.runAuton(currentAutonId);
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
	while (inert.isCalibrating())
	{
		vex::wait(10, vex::msec);
	}

	art::PID xPid = oldDrivePID;
	xPid.withConstants(5, 0.06, -5.0);
	art::PID yPid = oldDrivePID;
	yPid.withConstants(1, 0.06, -5.0);

	art::Angle offset = 0;

	art::Vec2 input;
	art::Angle target;
	double out;
	horizontalTracker.getTravel();
	verticalTracker.getTravel();

	while (1)
	{

		holoDrive.LeftSplitArcadeCurved(Controller1);

		if(!Controller1.ButtonR1.pressing()){
			holoDrive.rotateCommand(art::Degrees(-inert.heading(vex::deg)) - offset);
		}

		if(Controller1.ButtonA.PRESSED){
			offset = art::Degrees(-inert.heading(vex::deg)); 
		}

		art::Vec2 travel = art::Vec2::XandY(horizontalTracker.getTravel(), verticalTracker.getTravel());

		pos += art::Vec2::dirAndMag(travel.direction() + art::Degrees(inert.heading(vex::deg)), travel.magnitude());

		if(Controller1.ButtonLeft.PRESSED){
			std::cout << art::Length(pos.x).inches() << ", " << art::Length(pos.y).inches() << ", " << inert.heading(vex::deg) << std::endl;
		}

		input = art::Vec2::XandY(Controller1.Axis1.position(),Controller1.Axis2.position());

		if(input.magnitude() > 70)
			target = art::Angle(input.direction() - offset);
		
		art::Vec2 dist = art::Vec2() - pos;
		dist = art::Vec2::dirAndMag(dist.direction() - art::Degrees(inert.heading(vex::deg)), dist.magnitude());
		if(Controller1.ButtonX.pressing()){
			holoDrive.arcade(xPid.calculate(dist.x),yPid.calculate(dist.y),0); 
			target = art::Angle(0);
		}
		
		out = oldTurnPID.calculate(art::shortestTurnPath(target - art::Degrees(inert.heading(vex::deg))));
		holoDrive.m_cmdRot = out;

		holoDrive.update();
		
		vex::wait(20, vex::msec);
	}
}

vex::thread trackingThread;

int tracking()
{
	// asyncDrive.track();
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

	logging::logger.logHeader();

	// Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	// Run the pre-autonomous function.
	pre_auton();

	vex::wait(0.25, vex::sec);

	sds::shadesInit();

	// Prevent main from exiting with an infinite loop.
	while (true)
	{
		vex::wait(100, vex::msec);
	}
}
