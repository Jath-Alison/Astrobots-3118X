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
#include "Art\ART.h"
#include "WPILogger.h"
#include "robotConfig.h"
#include "Autons.h"
#include "Logging.h"
#include "Threads.h"
#include "SubAutons.h"

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
	// logger.logStringEntry(100, timePassed(), "Pre Auton Started");

	arm.setPosition(armRot.angle(), vex::degrees);
	// logger.logStringEntry(100, timePassed(), "Pre Auton Started");
	logger.logStringEntry(console, "Pre Auton Started");
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

	// logger.logStringEntry(100, timePassed(), "Auton Routine Started");

	while (smartDrive.m_inert.isCalibrating())
	{
		vex::wait(10, vex::msec);
	}
	// logger.logStringEntry(100, timePassed(), "Auton - Inertial Finished Calibrating");

	if (isBlue)
	{
		Brain.Screen.setCursor(10, 1);
		// blueSoloAWP();
		// blueElims();

		// Brain.Screen.print("BlueAuto- Rush");
		// blueRushAWP();

		// blueAWPGoalFirstNeg();
		// Brain.Screen.print("BlueAuto- Goal First AWPNeg");

		// Brain.Screen.print("BlueAuto- Stake First AWPPos");
		// blueAWPStakeFirstPos();

		// winfred_blueAWPStakeFirstPos();
		JathsSketchyFullFlippingAWP();
	}
	else
	{
		Brain.Screen.setCursor(10, 1);
		// redSoloAWP();
		// redElims();

		// Brain.Screen.print("RedAuto- Rush");
		// redRushAWP();

		// Brain.Screen.print("RedAuto- Goal First AWPNeg");
		// redAWPGoalFirstNeg();

		// Brain.Screen.print("RedAuto- Stake First AWPPos");
		// redAWPStakeFirstPos();

		// winfred_redAWPStakeFirstPos();
		// negStackedRings();
		negStackedRingsStakeFirst();
	}

	// logger.logStringEntry(100, timePassed(), "Auton Routine Finished");
}

// int armMacro()
// {

// 	// arm.set(-100);

// 	// vex::wait(.25, vex::sec);

// 	arm.set(75);
// 	vex::wait(.25, vex::sec);
// 	arm.set(0);
// 	arm.stop(vex::hold);

// 	macroRunning = false;

// 	return 1;
// }

vex::thread macroThread;

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
	logger.logStringEntry(console, "Driver Control - Inertial Finished Calibrating");

	clampState;
	doinkerDeployState;
	doinkerClampState;

	while (1)
	{

		smartDrive.LeftSplitArcadeCurved(Controller1);

		if (Controller1.ButtonR1.pressing())
		{
			intake.set(100);
		}
		else if (Controller1.ButtonA.pressing())
		{
			intake.set(-100);
		}
		else
		{
			intake.set(0);
		}

		if (Controller1.ButtonL1.PRESSED)
		{
			clampState = !clampState;
			clamp.set(clampState);
		}

		if (Controller1.ButtonX.PRESSED)
		{
			doinkerDeployState = !doinkerDeployState;
			doinkerDeploy.set(doinkerDeployState);
		}
		if (Controller1.ButtonB.PRESSED)
		{
			doinkerClampState = !doinkerClampState;
			doinkerClamp.set(doinkerClampState);
		}

		// if (Controller1.ButtonR2.pressing())
		// {
		// 	arm.set(100);
		// 	macroRunning = false;
		// }
		// else if (Controller1.ButtonL2.pressing())
		// {
		// 	arm.set(-100);
		// 	macroRunning = false;
		// }
		// else if (Controller1.ButtonUp.pressing())
		// {
		// 	arm.set(30);
		// 	macroRunning = false;
		// }else
		// if (Controller1.ButtonDown.pressing())
		// {
		// 	arm.set(-30);
		// 	macroRunning = false;
		// }
		// else if (!macroRunning)
		// {
		// 	arm.set(0);
		// 	arm.stop(vex::hold);
		// }

		if (Controller1.ButtonL2.pressing())
		{
			macroRunning = false;
			arm.set(-100);
		}
		else if (Controller1.ButtonR2.pressing())
		{
			macroRunning = false;
			arm.set(100);
		}

		if (Controller1.ButtonUp.PRESSED)
		{
			macroRunning = true;
			armTarget = art::Degrees(10);
		}

		if (macroRunning && abs(shortestTurnPath(armTarget - art::Degrees(armRot.angle())).degrees()) >= 0.5)
		{
			if (shortestTurnPath(armTarget - art::Degrees(armRot.angle())).degrees() > 30 && armTarget.degrees() < 50)
            {
                armOut = armPID.calculate(shortestTurnPath(armTarget - art::Degrees(armRot.angle())));
                arm.set(-armOut);
            }
            else
            {
                armOut = armPID.calculate(shortestTurnPath(armTarget - art::Degrees(armRot.angle())));
                arm.set(armOut);
            };
		}
		else if (!(Controller1.ButtonL2.pressing() || Controller1.ButtonR2.pressing()))
		{
			arm.set(0);
			arm.stop(vex::hold);
		}

		// if (Controller1.ButtonDown.pressing())
		// {
		// 	smartDrive.arcade(-100, 0);
		// }
		// else if (Controller1.ButtonUp.pressing())
		// {
		// 	smartDrive.arcade(100, 0);
		// }
		// else
		// {
		// 	smartDrive.LeftSplitArcadeCurved(Controller1);
		// }

		if (Controller1.ButtonDown.PRESSED)
		{
			// smartDrive.turnToPID(art::Degrees(0));

			// smartDrive.driveForPID(art::Inches(30));
			// smartDrive.turnToPID(art::Degrees(180));
			// smartDrive.driveForPID(art::Inches(30));
			// smartDrive.turnToPID(art::Degrees(0));

			// followPath(testPath, art::Inches(5));
			// driveTowardPoint(art::Vec2::XandY(art::Tiles(1), art::Tiles(1)));
			skills();
		}

		vex::wait(20, vex::msec);
	}
}

vex::thread trackingThread;
vex::thread displayThread;
vex::thread loggingThread;

int tracking()
{
	// logger.logStringEntry(100, timePassed(), "Tracking Thread Started");
	smartDrive.track();
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

	logger.logHeader();

	logger.logStringEntry(console, "Code Started");

	// logger.startStringEntry("Console", 100);

	// Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	// Run the pre-autonomous function.
	pre_auton();

	vex::wait(0.25, vex::sec);

	trackingThread = vex::thread(tracking);
	displayThread = vex::thread(displayLoopFunction);
	loggingThread = vex::thread(logLoopFunction);

	vex::wait(0.25, vex::sec);

	// logger.logStringEntry(100, timePassed(), "Robot Fully Configured");
	logger.logStringEntry(console, "Robot Fully Configured");

	// Prevent main from exiting with an infinite loop.
	while (true)
	{
		vex::wait(100, vex::msec);
	}
}
