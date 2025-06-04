#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dora
void pre_auton(void)
{
	RobotName = "Dora";
}

void autonomous(void)
{
}

void usercontrol(void)
{
	while (1)
	{
		if (Controller1.ButtonX.PRESSED && !climbControls)
		{
			oldDrivePID.withSettleZone(art::Revolutions(art::Inches(1.5) / (M_PI * art::Inches(2.75) * (36.f / 48.f))))
				.withSettleTimeout(0.0625);
			asyncDrive.driveForA(art::Inches(-7));
		}
		if (Controller1.ButtonX.pressing() && !climbControls)
		{
			if (asyncDrive.driveComplete())
			{
				Controller1.rumble(".");
			}
		}
		else
		{
			if (!climbControls)
			{
				asyncDrive.setState(AsyncDrive::CONTROL);
				asyncDrive.handleInputs(Controller1.Axis3.position(), Controller1.Axis1.position());
			}
			else
			{
				asyncDrive.setState(AsyncDrive::CONTROL);
				asyncDrive.handleInputs(Controller1.Axis3.position() + Controller1.Axis2.position(), Controller1.Axis3.position() - Controller1.Axis2.position());
			}
		}

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
		else if (Controller1.ButtonRight.PRESSED)
		{
			arm.setState(Arm::POSITION);
			arm.handlePosInput(art::Degrees(arm.getPos() - 1));
		}

		vex::wait(20, vex::msec);
	}
}

int trackingFunction(){
	asyncDrive.track();
	return 0;
}

void periodic(void)
{
	vex::thread trackingThread(trackingFunction);
	while (1)
	{
		clamp.set(clampState);

		intake.periodic();
		arm.periodic();
		asyncDrive.periodic();

		arm.resetPos(armRot.angle(vex::deg));

		Brain.Screen.clearScreen();
		Brain.Screen.setCursor(1, 1);
		Brain.Screen.print(RobotName.c_str());

		Brain.Screen.setCursor(2, 1); // time
		Brain.Screen.print("Time: %d:%02d", (int)vex::timer::system() / (60 * 1000), (int)vex::timer::system() % (60 * 1000));

		vex::wait(20, vex::msec);
	}
}
#endif
