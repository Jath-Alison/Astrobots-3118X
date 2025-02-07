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
#include "Autons.h"

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

	while (smartDrive.m_inert.isCalibrating())
	{
		vex::wait(10, vex::msec);
	}

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

	clampState;
	doinkerDeployRState = false;
	doinkerDeployR.set(false);
	doinkerDeployLState = false;
	doinkerDeployL.set(false);

	while (1)
	{

		// smartDrive.LeftSplitArcadeCurved(Controller1);
		// smartDrive.curvatureDrive(Controller1.Axis3.position(), Controller1.Axis1.position(), 25.0);

		asyncDrive.handleInputs(Controller1.Axis3.position(), Controller1.Axis1.position());

		if (Controller1.ButtonR1.pressing())
		{
			intake.handleInput(100);
		}
		else if (Controller1.ButtonA.pressing())
		{
			intake.handleInput(-100);
		}
		else
		{
			intake.handleInput(0);
		}

		if (Controller1.ButtonL1.PRESSED)
		{
			clampState = !clampState;
			clamp.set(clampState);
		}

		if (Controller1.ButtonLeft.PRESSED)
		{
			doinkerDeployRState = !doinkerDeployRState;
			doinkerDeployR.set(doinkerDeployRState);
		}

		if (Controller1.ButtonL2.pressing())
		{
			arm.setState(Arm::CONTROL);
			arm.handleCmdInput(-100);
		}
		else if (Controller1.ButtonR2.pressing())
		{
			arm.setState(Arm::CONTROL);
			arm.handleCmdInput(100);

			intake.handleInput(-30);
		}else{
			arm.handleCmdInput(0);
		}

		if (Controller1.ButtonUp.pressing())
		{
			arm.setState(Arm::POSITION);
			arm.handlePosInput(art::Degrees(10));

		}
		else if (Controller1.ButtonDown.pressing())
		{
			arm.setState(Arm::POSITION);
			arm.handlePosInput(art::Degrees(135));

			intake.handleInput(-30);
		}

		if (Controller1.ButtonRight.PRESSED){
			// flippingAWPAuton();
			centerRings();
			// asyncDrive.setTurnTarget(art::Degrees(0));
			// asyncDrive.setState(AsyncDrive::TURN);
			// waitUntil(asyncDrive.turnComplete());

			asyncDrive.setState(AsyncDrive::CONTROL);
		}

		vex::wait(20, vex::msec);
	}
}

vex::thread trackingThread;

int tracking()
{
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

	logging::logger.logHeader();

	// Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	// Run the pre-autonomous function.
	pre_auton();

	vex::wait(0.25, vex::sec);

	trackingThread = vex::thread(tracking);
	periodicThread = vex::thread(periodicLoop);
	logging::logThread = vex::thread(logging::logLoop);

	vex::wait(0.25, vex::sec);

	sds::shadesInit();

	// Prevent main from exiting with an infinite loop.
	while (true)
	{
		vex::wait(100, vex::msec);
	}
}
