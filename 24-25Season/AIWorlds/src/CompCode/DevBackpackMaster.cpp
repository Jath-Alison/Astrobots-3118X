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
}

bool sent = false;

void usercontrol(void)
{
  while (1)
  {

    if (Controller1.ButtonA.pressing())
    {
      link.send("Go Time");
sent = true;
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

    if(sent){
      Brain.Screen.drawRectangle(100,100,100,100);
    }

    armDeployMotor.spin(vex::fwd, armCmd * 12.0/100.0, vex::volt);

    vex::wait(20, vex::msec);
  }
}
#endif
