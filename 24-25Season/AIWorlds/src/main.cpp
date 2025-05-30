/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      5/29/2025, 3:27:48 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "Logging/Logging.h"

vex::competition Competition;
vex::brain Brain;
vex::controller Controller1;

vex::thread periodicThread;
std::string RobotName;

int main() {
  logging::logger.logHeader();

	// Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	// Run the pre-autonomous function.
	pre_auton();

	vex::wait(0.25, vex::sec);

	// trackingThread = vex::thread(tracking);
	periodicThread = vex::thread(periodic);
	logging::logThread = vex::thread(logging::logLoop);

	vex::wait(0.25, vex::sec);

	// sds::shadesInit();

	// Prevent main from exiting with an infinite loop.
	while (true)
	{
		vex::wait(100, vex::msec);
	}
}
