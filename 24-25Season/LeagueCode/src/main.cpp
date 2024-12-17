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

#include "Shades/Shades.h"

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

	coolBeansRushRed();

	// if (isBlue)
	// {
	// 	Brain.Screen.setCursor(10, 1);
	// 	// blueSoloAWP();
	// 	// blueElims();

	// 	// Brain.Screen.print("BlueAuto- Rush");
	// 	// blueRushAWP();

	// 	// blueAWPGoalFirstNeg();
	// 	// Brain.Screen.print("BlueAuto- Goal First AWPNeg");

	// 	// Brain.Screen.print("BlueAuto- Stake First AWPPos");
	// 	// blueAWPStakeFirstPos();

	// 	// winfred_blueAWPStakeFirstPos();
	// 	JathsSketchyFullFlippingAWP();
	// }
	// else
	// {
	// 	Brain.Screen.setCursor(10, 1);
	// 	// redSoloAWP();
	// 	// redElims();

	// 	// Brain.Screen.print("RedAuto- Rush");
	// 	// redRushAWP();

	// 	// Brain.Screen.print("RedAuto- Goal First AWPNeg");
	// 	// redAWPGoalFirstNeg();

	// 	// Brain.Screen.print("RedAuto- Stake First AWPPos");
	// 	// redAWPStakeFirstPos();

	// 	// winfred_redAWPStakeFirstPos();
	// 	// negStackedRings();
	// 	negStackedRingsStakeFirst();
	// }

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
	// displayThread = vex::thread(displayLoopFunction);
	loggingThread = vex::thread(logLoopFunction);

	vex::wait(0.25, vex::sec);

	const char *xml = R"(
    <?xml version="1.0" encoding="utf-8"?>
    <root>
      <shades>
        <screen id="home">
          <box id="box" x="0" y="0" width="480" height="240" callback="" color="0x4287F5FF"/>
          <text id="title" x="15" y="15" text="3118B - Astrobots" color="0xFCB040FF" />
          <text id="title" x="15" y="45" text="Shades" color="0xFCB040FF" />

          <image id="0" x="7" y="107" src="AstrobotsLogo.png" callback="" />

          <box id="auton_button" x="260" y="15" width="200" height="60" color="0xFFFFFFFF" callback="auton" />
          <text id="0" x="275" y="25" text="Auton Select" color="0x000000FF" callback="" />

          <box id="stats_home_button" x="260" y="90" width="200" height="60" color="0xFFFFFFFF" callback="stats_home" />
          <text id="0" x="275" y="100" text="Robot Stats" color="0x000000FF" callback="" />

          <box id="0" x="260" y="165" width="200" height="60" color="0xFFFFFFFF" callback="" />
          <text id="programData" x="260" y="175" text="" color="0x000000FF" callback="" />
        </screen>
        
        <screen id="auton">
          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <text id="autonDisplay" x="55" y="5" text="Auton Selector" color="0xFCB040FF" callback="" />

          <box id="0" x="15" y="65" width="130" height="72" color="0xFF0000FF" callback="" />
          <box id="0" x="15" y="152" width="130" height="72" color="0xFF0000FF" callback="" />

          <image id="fieldImage" x="160" y="65" src="Over Under field.png" callback="" />

          <box id="0" x="335" y="65" width="130" height="72" color="0x0000FFFF" callback="" />
          <box id="0" x="335" y="152" width="130" height="72" color="0x0000FFFF" callback="" />
        </screen>

        <screen id="stats_home">
          <box id="0" x="0" y="0" width="480" height="50" color="0xFF0000FF" callback="" />
          <text id="0" x="65" y="15" text="Motor Temperature" color="0x000000FF" callback="" />

          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <image id="Motor1" x="17" y="50" src="Motor.png" callback="" />
          <image id="Motor2" x="125" y="50" src="Motor.png" callback="" />
          <image id="Motor3" x="234" y="50" src="Motor.png" callback="" />
          <image id="Motor4" x="343" y="50" src="Motor.png" callback="" />

          <image id="Motor5" x="17" y="144" src="Motor.png" callback="" />
          <image id="Motor6" x="125" y="144" src="Motor.png" callback="" />
          <image id="Motor7" x="234" y="144" src="Motor.png" callback="" />
          <image id="Motor8" x="343" y="144" src="Motor.png" callback="" />
          
          <text id="0" x="20" y="110" text="Left-F" color="0xFFFFFFFF" callback="" />
          <text id="0" x="128" y="110" text="Right-F" color="0xFFFFFFFF" callback="" />
          <text id="0" x="237" y="110" text="Intake-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="346" y="110" text="Intake-L" color="0xFFFFFFFF" callback="" />
          
          <text id="0" x="20" y="204" text="Left-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="128" y="204" text="Right-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="237" y="204" text="Catapult" color="0xFFFFFFFF" callback="" />
          <text id="0" x="346" y="204" text="Climb" color="0xFFFFFFFF" callback="" />

          <box id="0" x="450" y="60" width="30" height="120" color="0xFFFFFFFF" callback="stats_extend" />

        </screen>
        <screen id="stats_extend">
          <box id="0" x="0" y="0" width="480" height="50" color="0xFF0000FF" callback="" />
          <text id="0" x="65" y="15" text="Location Stats" color="0x000000FF" callback="" />

          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <box id="0" x="0" y="60" width="30" height="120" color="0xFFFFFFFF" callback="stats_home" />
        </screen>
      </shades>
    </root>    
  )";

	if (Brain.SDcard.isInserted())
	{
		sds::Screen::initialize();
	}
	else
	{
		sds::Screen::initialize(xml);
	}

	vex::thread eventThread2(sds::Screen::eventLoop);
	vex::thread displayThread2(sds::Screen::displayLoop);

	// logger.logStringEntry(100, timePassed(), "Robot Fully Configured");
	logger.logStringEntry(console, "Robot Fully Configured");

	// Prevent main from exiting with an infinite loop.
	while (true)
	{
		vex::wait(100, vex::msec);
	}
}
