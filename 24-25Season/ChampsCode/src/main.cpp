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
#include "SubAutons.h"

#include "ART/Jath/Path.h"
#include <vector>

std::vector<Jath::Point> testPathPoints = {Jath::Point(-118.548, 56.718, 7), Jath::Point(-118.625, 58.717, 75), Jath::Point(-118.698, 60.716, 74.056), Jath::Point(-118.768, 62.714, 73.684), Jath::Point(-118.834, 64.713, 72.369), Jath::Point(-118.895, 66.712, 71.053), Jath::Point(-118.95, 68.712, 69.738), Jath::Point(-118.998, 70.711, 68.422), Jath::Point(-119.037, 72.711, 67.107), Jath::Point(-119.067, 74.71, 65.791), Jath::Point(-119.084, 76.71, 64.476), Jath::Point(-119.089, 78.71, 63.16), Jath::Point(-119.076, 80.71, 63.16), Jath::Point(-119.046, 82.71, 63.16), Jath::Point(-118.993, 84.709, 63.16), Jath::Point(-118.915, 86.708, 63.16), Jath::Point(-118.807, 88.705, 63.16), Jath::Point(-118.661, 90.7, 63.16), Jath::Point(-118.474, 92.691, 62.29), Jath::Point(-118.236, 94.676, 59.76), Jath::Point(-117.937, 96.654, 56.813), Jath::Point(-117.567, 98.619, 53.42), Jath::Point(-117.109, 100.566, 47.489), Jath::Point(-116.547, 102.485, 43.042), Jath::Point(-115.863, 104.364, 35.946), Jath::Point(-115.037, 106.184, 31.265), Jath::Point(-114.049, 107.922, 25.138), Jath::Point(-112.889, 109.55, 22), Jath::Point(-111.558, 111.041, 22), Jath::Point(-110.066, 112.372, 23.021), Jath::Point(-108.44, 113.534, 28.313), Jath::Point(-106.707, 114.53, 35.11), Jath::Point(-104.895, 115.375, 39.885), Jath::Point(-103.024, 116.082, 46.753), Jath::Point(-101.115, 116.677, 50.903), Jath::Point(-99.178, 117.173, 56.307), Jath::Point(-97.222, 117.589, 59.349), Jath::Point(-95.253, 117.938, 61.969), Jath::Point(-93.274, 118.232, 63.16), Jath::Point(-91.29, 118.478, 63.16), Jath::Point(-89.3, 118.686, 63.16), Jath::Point(-87.308, 118.861, 63.16), Jath::Point(-85.313, 119.008, 63.16), Jath::Point(-83.317, 119.132, 63.16), Jath::Point(-81.32, 119.237, 63.16), Jath::Point(-79.322, 119.325, 63.16), Jath::Point(-77.323, 119.399, 63.16), Jath::Point(-75.324, 119.462, 63.16), Jath::Point(-73.325, 119.515, 63.16), Jath::Point(-71.326, 119.56, 63.16), Jath::Point(-69.326, 119.599, 63.16), Jath::Point(-67.326, 119.632, 63.16), Jath::Point(-65.327, 119.661, 63.16), Jath::Point(-63.327, 119.686, 63.16), Jath::Point(-61.327, 119.709, 63.1), Jath::Point(-59.327, 119.728, 63.16), Jath::Point(-57.327, 119.731, 63.16), Jath::Point(-55.327, 119.709, 63.16), Jath::Point(-53.328, 119.658, 63.16), Jath::Point(-51.33, 119.567, 63.16), Jath::Point(-49.334, 119.437, 62.333), Jath::Point(-47.343, 119.253, 58.439), Jath::Point(-45.358, 119.009, 53.061), Jath::Point(-43.385, 118.683, 45.556), Jath::Point(-41.433, 118.25, 35.015), Jath::Point(-39.518, 117.674, 22), Jath::Point(-37.679, 116.894, 22), Jath::Point(-35.999, 115.817, 22), Jath::Point(-34.676, 114.33, 22), Jath::Point(-33.995, 112.464, 22), Jath::Point(-34.017, 110.472, 22), Jath::Point(-34.513, 108.538, 22), Jath::Point(-35.293, 106.698, 35.917), Jath::Point(-36.238, 104.935, 49.335), Jath::Point(-37.286, 103.232, 55.604), Jath::Point(-38.405, 101.575, 62.418), Jath::Point(-39.57, 99.949, 63.16), Jath::Point(-40.767, 98.347, 63.16), Jath::Point(-41.984, 96.76, 63.16), Jath::Point(-43.213, 95.182, 63.16), Jath::Point(-44.448, 93.609, 63.16), Jath::Point(-45.683, 92.036, 63.16), Jath::Point(-46.913, 90.459, 63.16), Jath::Point(-48.133, 88.874, 63.16), Jath::Point(-49.339, 87.278, 63.16), Jath::Point(-50.525, 85.668, 63.16), Jath::Point(-51.688, 84.041, 63.16), Jath::Point(-52.821, 82.393, 63.16), Jath::Point(-53.919, 80.721, 62.229), Jath::Point(-54.975, 79.023, 60.234), Jath::Point(-55.981, 77.295, 58.01), Jath::Point(-56.929, 75.534, 55.525), Jath::Point(-57.808, 73.737, 52.753), Jath::Point(-58.607, 71.904, 49.68), Jath::Point(-59.311, 70.033, 46.316), Jath::Point(-59.906, 68.123, 42.705), Jath::Point(-60.369, 66.178, 37.046), Jath::Point(-60.683, 64.204, 33.366), Jath::Point(-60.833, 62.21, 30.05), Jath::Point(-60.833, 60.211, 42.406), Jath::Point(-60.708, 58.215, 33.841), Jath::Point(-60.413, 56.238, 22), Jath::Point(-59.88, 54.312, 22), Jath::Point(-59.015, 52.514, 22), Jath::Point(-57.727, 50.993, 22), Jath::Point(-56.034, 49.943, 22), Jath::Point(-54.113, 49.41, 22), Jath::Point(-52.119, 49.285, 22), Jath::Point(-50.126, 49.434, 34.728), Jath::Point(-48.154, 49.765, 46.006), Jath::Point(-46.206, 50.218, 54.205), Jath::Point(-44.28, 50.757, 61.882), Jath::Point(-42.372, 51.356, 63.16), Jath::Point(-40.477, 51.996, 63.16), Jath::Point(-38.592, 52.664, 63.16), Jath::Point(-36.713, 53.35, 63.16), Jath::Point(-34.839, 54.046, 63.16), Jath::Point(-32.965, 54.747, 63.16), Jath::Point(-31.091, 55.445, 63.16), Jath::Point(-29.214, 56.136, 63.16), Jath::Point(-27.333, 56.815, 63.16), Jath::Point(-25.447, 57.479, 63.16), Jath::Point(-23.553, 58.122, 63.16), Jath::Point(-21.651, 58.74, 63.16), Jath::Point(-19.74, 59.33, 63.16), Jath::Point(-17.819, 59.888, 63.16), Jath::Point(-15.888, 60.407, 63.16), Jath::Point(-13.946, 60.884, 63.023), Jath::Point(-11.993, 61.315, 61.918), Jath::Point(-10.029, 61.694, 60.767), Jath::Point(-8.055, 62.015, 59.571), Jath::Point(-6.072, 62.273, 57.7), Jath::Point(-4.081, 62.461, 56.412), Jath::Point(-2.084, 62.574, 55.108), Jath::Point(-0.777, 62.607, 54.45), Jath::Point(-0.777, 62.607, -1), };
Jath::Path testPath = Jath::Path::cm(testPathPoints);

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

	while (asyncDrive.isCalibrating())
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
	while (asyncDrive.isCalibrating())
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

		asyncDrive.handleInputs(Controller1.Axis3.position(), Controller1.Axis1.position());

		if (Controller1.ButtonR1.PRESSED)
		{
			// intake.handleInput(100);
			intake.setState(Intake::REJECT_BLUE);
		}
		else if (Controller1.ButtonA.pressing())
		{
			intake.setState(Intake::CONTROL);
			intake.handleInput(-100);
		}
		else if (Controller1.ButtonR1.RELEASED ||
				 Controller1.ButtonA.RELEASED)
		{
			intake.setState(Intake::CONTROL);
			intake.handleInput(0);
		}else{
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
			// doinkerDeployLState = !doinkerDeployLState;
			// doinkerDeployL.set(doinkerDeployLState);
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
		}
		else
		{
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

		if (Controller1.ButtonY.PRESSED)
		{
			intake.setAntiJam(!intake.getAntiJam());
		}

		if (Controller1.ButtonRight.PRESSED)
		{
			// flippingAWPAuton();
			// centerRings();
			// ringSideToCorner();

			// skills();

			asyncDrive.followPathS(testPath);

			// waitUntil(Controller1.ButtonRight.PRESSED);

			asyncDrive.setState(AsyncDrive::CONTROL);
		}

		vex::wait(20, vex::msec);
	}
}

vex::thread trackingThread;

int tracking()
{
	asyncDrive.track();
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
