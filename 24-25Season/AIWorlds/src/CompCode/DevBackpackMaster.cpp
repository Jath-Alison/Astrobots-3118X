#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Backpack_Master

double armCmd = 0.0;

void pre_auton(void)
{
  RobotName = "Dev_Backpack_Master";
  armCmd = 0.0;
}

void autonomous(void)
{
  armCmd = 0.0;
  vex::wait(0.25, vex::sec);
  armCmd = 50.0;
  vex::wait(1.0, vex::sec);
  armCmd = 0.0;
}

void usercontrol(void)
{
  while (1)
  {

    if (Brain.Screen.pressing())
    {
      armCmd = 75.0;
    }
    else
    {
      armCmd = 0.0;
    }

    vex::wait(20, vex::msec);
  }
}

void periodic(void)
{
  while (1)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(RobotName.c_str());

    Brain.Screen.setCursor(2, 1);//time
    Brain.Screen.print("Time: %d:%02d", (int)vex::timer::system() / (60 * 1000), (int)vex::timer::system() % (60 * 1000));

    Brain.Screen.setCursor(3, 1);//cmd
    Brain.Screen.print("Arm Cmd: %.2f", armCmd);

    armDeployMotor.spin(vex::fwd, armCmd * 12.0/100.0, vex::volt);

    vex::wait(20, vex::msec);
  }
}
#endif
