#include "RobotConfig/RobotConfig.h"
#include <iostream>

#if CURRENT_ROBOT == Backpack_Red

double armCmd = 0.0;

void pre_auton(void)
{
  RobotName = "Backpack_Red";
  armCmd = 0.0;

  link.received(receive_message);
}

void deployArm()
{
  while (armDeployMotor.position(vex::degrees) < 3750)
  {
    armCmd = 10.0;
    vex::wait(20, vex::msec);
  }
  armCmd = 0.0;
}

std::string currentCmd = "";
void receive_message(const char *message, const char *linkname, int32_t index, double value)
{
  std::cout << "messag Recieved";
  currentCmd = message;
  std::cout << message;
}

void autonomous(void)
{
}

void usercontrol(void)
{
  while (1)
  {

    if (Controller1.ButtonA.pressing() && armDeployMotor.position(vex::degrees) < 3750)
    {
      deployArm();
    }
    else
    {
      armCmd = Controller1.Axis2.position();
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

    Brain.Screen.setCursor(2, 1); // time
    Brain.Screen.print("Time: %d:%02d", (int)vex::timer::system() / (60 * 1000), (int)vex::timer::system() % (60 * 1000));

    Brain.Screen.setCursor(3, 1); // cmd
    Brain.Screen.print("Arm Cmd: %.2f", armCmd);

    Brain.Screen.setCursor(4, 1); // cmd
    Brain.Screen.print("Arm Pos: %.2f", armDeployMotor.position(vex::degrees));
    
    Brain.Screen.setCursor(5, 1); // cmd
    Brain.Screen.print("currentCmd");

    Brain.Screen.setCursor(5, 15); // cmd
    Brain.Screen.print(currentCmd.c_str());


    armDeployMotor.set(armCmd);

    vex::wait(20, vex::msec);
  }
}
#endif
