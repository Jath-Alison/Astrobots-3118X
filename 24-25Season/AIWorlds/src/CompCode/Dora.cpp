#include "RobotConfig/RobotConfig.h"
#include "ART/Jath/Path.h"

#if CURRENT_ROBOT == Dora

std::vector<Jath::Point> testPathUPoints = {Jath::Point(-120.904,-0.989,89.4), Jath::Point(-120.205,0.885,89.4), Jath::Point(-119.511,2.76,89.4), Jath::Point(-118.825,4.639,89.4), Jath::Point(-118.146,6.52,89.4), Jath::Point(-117.476,8.405,89.4), Jath::Point(-116.815,10.292,89.4), Jath::Point(-116.165,12.184,89.4), Jath::Point(-115.527,14.079,89.4), Jath::Point(-114.902,15.979,89.4), Jath::Point(-114.293,17.884,89.4), Jath::Point(-113.702,19.795,89.4), Jath::Point(-113.131,21.712,89.4), Jath::Point(-112.584,23.635,88.862), Jath::Point(-112.063,25.566,87.597), Jath::Point(-111.573,27.505,85.375), Jath::Point(-111.121,29.453,83.646), Jath::Point(-110.713,31.411,80.627), Jath::Point(-110.356,33.379,77.033), Jath::Point(-110.063,35.357,72.801), Jath::Point(-109.846,37.345,67.891), Jath::Point(-109.721,39.341,62.314), Jath::Point(-109.71,41.341,54.005), Jath::Point(-109.836,43.336,45.204), Jath::Point(-110.125,45.315,36.866), Jath::Point(-110.603,47.256,29.086), Jath::Point(-111.286,49.134,26.519), Jath::Point(-112.176,50.924,28.889), Jath::Point(-113.257,52.605,36.69), Jath::Point(-114.5,54.172,45.334), Jath::Point(-115.87,55.628,57.039), Jath::Point(-117.336,56.988,65.955), Jath::Point(-118.87,58.27,73.889), Jath::Point(-120.455,59.491,80.642), Jath::Point(-121.96,60.79,88.201), Jath::Point(-123.257,62.313,86.431), Jath::Point(-124.526,63.858,85.097), Jath::Point(-125.765,65.429,82.839), Jath::Point(-126.966,67.027,81.15), Jath::Point(-128.124,68.658,78.321), Jath::Point(-129.232,70.323,75.123), Jath::Point(-130.28,72.026,71.559), Jath::Point(-131.257,73.771,67.658), Jath::Point(-132.15,75.56,63.488), Jath::Point(-132.943,77.396,57.721), Jath::Point(-133.62,79.278,53.48), Jath::Point(-134.162,81.202,48.396), Jath::Point(-134.554,83.163,44.561), Jath::Point(-134.779,85.15,42.559), Jath::Point(-134.831,87.148,42.729), Jath::Point(-134.707,89.144,45.039), Jath::Point(-134.413,91.121,47.955), Jath::Point(-133.962,93.069,52.948), Jath::Point(-133.372,94.98,58.613), Jath::Point(-132.66,96.849,62.955), Jath::Point(-131.845,98.675,68.528), Jath::Point(-130.941,100.458,72.393), Jath::Point(-129.963,102.203,75.919), Jath::Point(-128.922,103.911,79.079), Jath::Point(-127.83,105.586,81.876), Jath::Point(-126.693,107.231,84.328), Jath::Point(-125.519,108.85,85.783), Jath::Point(-124.313,110.445,87.722), Jath::Point(-123.08,112.02,88.865), Jath::Point(-121.824,113.577,89.4), Jath::Point(-120.548,115.117,89.4), Jath::Point(-119.255,116.643,89.4), Jath::Point(-117.974,118.179,82.571), Jath::Point(-116.659,119.685,81.779), Jath::Point(-115.307,121.159,80.933), Jath::Point(-113.916,122.596,80.027), Jath::Point(-112.484,123.992,78.553), Jath::Point(-111.011,125.345,77.489), Jath::Point(-109.494,126.648,75.764), Jath::Point(-107.933,127.899,74.526), Jath::Point(-106.327,129.09,72.536), Jath::Point(-104.675,130.216,70.388), Jath::Point(-102.976,131.271,68.874), Jath::Point(-101.229,132.245,66.495), Jath::Point(-99.436,133.131,64.013), Jath::Point(-97.599,133.92,61.473), Jath::Point(-95.719,134.602,58.938), Jath::Point(-93.801,135.167,56.487), Jath::Point(-91.85,135.606,54.213), Jath::Point(-89.873,135.908,51.639), Jath::Point(-87.88,136.064,50.187), Jath::Point(-85.88,136.07,49.25), Jath::Point(-83.886,135.922,48.896), Jath::Point(-81.91,135.621,49.158), Jath::Point(-79.963,135.165,50.449), Jath::Point(-78.056,134.563,52.058), Jath::Point(-76.199,133.823,54.122), Jath::Point(-74.398,132.955,56.533), Jath::Point(-72.658,131.968,59.181), Jath::Point(-70.984,130.876,61.956), Jath::Point(-69.375,129.688,64.765), Jath::Point(-67.833,128.414,66.616), Jath::Point(-66.358,127.064,69.315), Jath::Point(-64.945,125.649,71.881), Jath::Point(-63.596,124.173,73.502), Jath::Point(-62.303,122.646,75.045), Jath::Point(-61.07,121.072,77.205), Jath::Point(-59.89,119.458,78.541), Jath::Point(-59.06,117.647,75.671), Jath::Point(-58.365,115.772,73.684), Jath::Point(-57.741,113.872,71.783), Jath::Point(-57.194,111.949,70.055), Jath::Point(-56.731,110.003,68.593), Jath::Point(-56.359,108.038,67.493), Jath::Point(-56.08,106.058,66.845), Jath::Point(-55.897,104.067,66.724), Jath::Point(-55.815,102.069,67.633), Jath::Point(-55.83,100.069,68.993), Jath::Point(-55.937,98.072,72.128), Jath::Point(-56.128,96.081,74.885), Jath::Point(-56.393,94.099,79.869), Jath::Point(-56.716,92.125,85.669), Jath::Point(-57.081,90.159,89.4), Jath::Point(-57.471,88.197,89.4), Jath::Point(-57.867,86.237,89.4), Jath::Point(-58.248,84.273,85.74), Jath::Point(-58.594,82.304,79.143), Jath::Point(-58.887,80.325,73.127), Jath::Point(-59.106,78.338,69.615), Jath::Point(-59.237,76.342,65.363), Jath::Point(-59.267,74.343,62.606), Jath::Point(-59.186,72.344,61.695), Jath::Point(-58.991,70.354,61.727), Jath::Point(-58.681,68.379,62.607), Jath::Point(-58.263,66.423,64.974), Jath::Point(-57.736,64.494,67.065), Jath::Point(-57.114,62.594,69.412), Jath::Point(-56.405,60.724,71.888), Jath::Point(-55.616,58.886,74.387), Jath::Point(-54.757,57.08,76.825), Jath::Point(-53.834,55.306,78.002), Jath::Point(-52.853,53.563,80.24), Jath::Point(-51.824,51.848,82.302), Jath::Point(-50.748,50.163,83.263), Jath::Point(-49.635,48.501,85.039), Jath::Point(-48.482,46.867,85.856), Jath::Point(-47.3,45.254,86.625), Jath::Point(-46.087,43.663,88.03), Jath::Point(-44.847,42.094,88.669), Jath::Point(-43.584,40.544,89.267), Jath::Point(-42.299,39.011,89.4), Jath::Point(-40.994,37.495,89.4), Jath::Point(-39.671,35.996,89.4), Jath::Point(-38.33,34.512,89.4), Jath::Point(-36.973,33.043,89.4), Jath::Point(-35.602,31.586,89.4), Jath::Point(-34.218,30.143,89.4), Jath::Point(-32.821,28.711,89.4), Jath::Point(-31.413,27.291,89.4), Jath::Point(-29.733,26.207,87.155), Jath::Point(-28.064,25.106,86.017), Jath::Point(-26.411,23.98,84.747), Jath::Point(-24.785,22.815,84.747), Jath::Point(-23.184,21.616,83.331), Jath::Point(-21.608,20.386,81.756), Jath::Point(-20.06,19.12,80.007), Jath::Point(-18.545,17.814,80.007), Jath::Point(-17.074,16.459,78.075), Jath::Point(-15.645,15.06,75.949), Jath::Point(-14.264,13.614,73.625), Jath::Point(-12.937,12.118,71.106), Jath::Point(-11.673,10.568,68.401), Jath::Point(-10.481,8.963,65.533), Jath::Point(-9.369,7.301,62.54), Jath::Point(-8.349,5.581,59.472), Jath::Point(-7.44,3.8,53.41), Jath::Point(-6.656,1.961,50.601), Jath::Point(-6.003,0.072,48.082), Jath::Point(-5.49,-1.861,45.958), Jath::Point(-5.148,-3.83,43.256), Jath::Point(-4.975,-5.822,42.797), Jath::Point(-4.964,-7.821,42.959), Jath::Point(-5.147,-9.812,45.011), Jath::Point(-5.486,-11.782,46.766), Jath::Point(-5.987,-13.717,51.272), Jath::Point(-6.642,-15.606,53.83), Jath::Point(-7.421,-17.447,56.474), Jath::Point(-8.329,-19.229,61.741), Jath::Point(-9.344,-20.952,64.262), Jath::Point(-10.448,-22.619,66.664), Jath::Point(-11.634,-24.229,71.036), Jath::Point(-12.9,-25.777,72.992), Jath::Point(-14.227,-27.273,74.794), Jath::Point(-15.609,-28.718,76.447), Jath::Point(-17.041,-30.115,77.959), Jath::Point(-18.516,-31.465,79.337), Jath::Point(-20.032,-32.769,81.729), Jath::Point(-21.586,-34.029,82.763), Jath::Point(-23.17,-35.249,83.7), Jath::Point(-24.783,-36.431,84.549), Jath::Point(-26.422,-37.577,85.318), Jath::Point(-28.085,-38.688,86.014), Jath::Point(-29.769,-39.767,86.643), Jath::Point(-31.473,-40.813,87.212), Jath::Point(-33.196,-41.83,87.725), Jath::Point(-34.935,-42.817,88.188), Jath::Point(-36.69,-43.777,88.605), Jath::Point(-38.459,-44.709,88.98), Jath::Point(-40.242,-45.615,89.315), Jath::Point(-42.038,-46.496,89.4), Jath::Point(-43.845,-47.352,89.4), Jath::Point(-45.664,-48.184,89.4), Jath::Point(-47.493,-48.993,89.4), Jath::Point(-49.332,-49.779,89.4), Jath::Point(-51.181,-50.542,89.4), Jath::Point(-53.039,-51.282,89.4), Jath::Point(-54.905,-52,89.4), Jath::Point(-56.78,-52.697,89.4), Jath::Point(-58.662,-53.373,89.4), Jath::Point(-60.552,-54.028,89.4), Jath::Point(-62.449,-54.661,89.4), Jath::Point(-64.353,-55.274,89.4), Jath::Point(-66.263,-55.865,89.4), Jath::Point(-68.18,-56.436,89.4), Jath::Point(-70.103,-56.985,89.4), Jath::Point(-72.033,-57.512,89.4), Jath::Point(-73.968,-58.017,89.4), Jath::Point(-75.908,-58.5,89.4), Jath::Point(-77.855,-58.961,89.4), Jath::Point(-79.806,-59.398,89.4), Jath::Point(-81.763,-59.81,89.4), Jath::Point(-83.725,-60.198,89.4), Jath::Point(-85.692,-60.559,89.116), Jath::Point(-87.664,-60.894,88.686), Jath::Point(-89.64,-61.2,88.19), Jath::Point(-91.621,-61.476,87.618), Jath::Point(-93.606,-61.721,86.958), Jath::Point(-95.595,-61.932,86.196), Jath::Point(-97.587,-62.105,84.295), Jath::Point(-99.583,-62.235,83.11), Jath::Point(-101.581,-62.322,81.729), Jath::Point(-103.581,-62.361,80.115), Jath::Point(-105.58,-62.346,75.987), Jath::Point(-107.579,-62.262,73.343), Jath::Point(-109.573,-62.111,70.2), Jath::Point(-111.557,-61.866,61.947), Jath::Point(-113.528,-61.524,50.006), Jath::Point(-115.468,-61.044,42.126), Jath::Point(-117.36,-60.399,25), Jath::Point(-118.548,-59.875,25), Jath::Point(-118.548,-59.875,0)};
Jath::Path testPathU = Jath::Path::cm(testPathUPoints);

void pre_auton(void)
{
	RobotName = "Dora";
}

void autonomous(void)
{
	asyncDrive.driveForS(art::Inches(10));
	asyncDrive.turnToS(art::Degrees(90));
	asyncDrive.turnToS(art::Degrees(180));
	asyncDrive.driveForS(art::Inches(10));
	asyncDrive.turnToS(art::Degrees(0));

	intake.setState(intake.CONTROL);
	intake.handleInput(100);

	asyncDrive.setPos(testPathUPoints.front().m_pos);

	asyncDrive.setState(AsyncDrive::DriveState::PATH);
	asyncDrive.followPathS(testPathU, art::Inches(15));
	intake.handleInput(0);
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

		if (Controller1.ButtonB.pressing() && Controller1.ButtonRight.pressing())
		{
			autonomous();
			asyncDrive.setState(AsyncDrive::CONTROL);
			intake.setState(Intake::CONTROL);
		}

		vex::wait(20, vex::msec);
	}
}

int trackingFunction()
{
	asyncDrive.track();
	return 0;
}

void periodic(void)
{
	vex::thread trackingThread(trackingFunction);
	while (1)
	{
		clamp.set(clampState);
		clamp2.set(clampState);
		pto.set(ptoState);
		climbDeploy.set(climbDeployState);
		climbDeploy2.set(climbDeployState);

		intake.periodic();
		arm.periodic();
		asyncDrive.periodic();

		arm.resetPos(armRot.angle(vex::deg));

		Brain.Screen.clearScreen();
		Brain.Screen.setCursor(1, 1);
		Brain.Screen.print(RobotName.c_str());

		Brain.Screen.setCursor(2, 1); // time
		Brain.Screen.print("Time: %d:%02d", (int)vex::timer::system() / (60 * 1000), (int)vex::timer::system() % (60 * 1000));

		Brain.Screen.setCursor(3, 1); // pos
		Brain.Screen.print("Pos: %d,%d", (int)art::Length(asyncDrive.getPos().x).inches(), (int)art::Length(asyncDrive.getPos().y).inches());

		vex::wait(20, vex::msec);
	}
}
#endif
