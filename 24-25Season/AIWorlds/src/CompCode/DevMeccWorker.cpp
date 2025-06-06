#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Mecc_Worker

#define HEADING_TOLERANCE 100

void localize(double scale)
{
  art::Vec2 leftGPSPos = art::Vec2::XandY(art::Inches(leftGps.xPosition(vex::inches)), art::Inches(leftGps.yPosition(vex::inches)));
  art::Vec2 rightGPSPos = art::Vec2::XandY(art::Inches(rightGps.xPosition(vex::inches)), art::Inches(rightGps.yPosition(vex::inches)));

  art::Vec2 avgPos = pos;

  if (fabs(leftGps.heading(vex::degrees) - inert.heading(vex::degrees)) < (HEADING_TOLERANCE) && fabs(rightGps.heading(vex::degrees) - inert.heading(vex::degrees)) < (HEADING_TOLERANCE) &&
      leftGps.quality() == 100 &&
      leftGps.xPosition() != 0.0 && leftGps.yPosition() != 0.0 &&
      rightGps.quality() == 100 &&
      rightGps.xPosition() != 0.0 && rightGps.yPosition() != 0.0)
  {
    avgPos = (leftGPSPos + rightGPSPos) * 0.5;
  }
  else if (fabs(leftGps.heading(vex::degrees) - inert.heading(vex::degrees)) < (HEADING_TOLERANCE) &&
           leftGps.quality() == 100 &&
           leftGps.xPosition() != 0.0 && leftGps.yPosition() != 0.0)
  {
    avgPos = leftGPSPos;
  }
  else 
  if (fabs(rightGps.heading(vex::degrees) - inert.heading(vex::degrees)) < HEADING_TOLERANCE &&
           rightGps.quality() == 100 &&
           rightGps.xPosition() != 0.0 && rightGps.yPosition() != 0.0)
  {
    avgPos = rightGPSPos;
  }

  avgPos = avgPos * scale + pos * (1.0 - scale);

  pos = avgPos;
}

void pre_auton(void)
{
  RobotName = "Dev_Mecc_Worker";
  link.received(receive_message);
}

void autonomous(void)
{
}

std::string currentCmd = "";
void receive_message(const char *message, const char *linkname, int32_t index, double value)
{
  // message is the received message
  // linkname is the link name for the message_link that received the message
  // index is optional int32_t variable
  // value is optional double variable

  currentCmd = message;
}

int counter = 0;

void usercontrol(void)
{
  while (1)
  {

    if (Controller1.ButtonA.pressing())
    {

      art::Vec2 travel = art::Vec2(art::Vec2::XandY(art::Tiles(2), art::Tiles(0)) - pos);

      travel = art::Vec2::dirAndMag(travel.direction() - art::Degrees(inert.heading(vex::degrees)), travel.magnitude());

      holoDrive.arcade(travel.x * 0.5, travel.y * 0.5, Controller1.Axis1.position());
    }
    else
    {
      holoDrive.LeftSplitArcadeCurved(Controller1);
      holoDrive.rotateCommand(art::Degrees(inert.heading(vex::degrees)));
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

    Brain.Screen.setCursor(3, 1); // position
    Brain.Screen.print("Position: (%.2f, %.2f)", art::Length(pos.x).inches(), art::Length(pos.y).inches());

    Brain.Screen.setCursor(4, 1); // inertial heading
    Brain.Screen.print("Inertial Heading: %.2f", inert.heading(vex::degrees));

    //gps pos
    Brain.Screen.setCursor(5, 1); // position
    Brain.Screen.print("gpsPosition%: (%.2f, %.2f) @ %.2f", rightGps.xPosition(vex::inches), rightGps.yPosition(vex::inches), rightGps.heading(vex::degrees));

    //gps pos 2
    Brain.Screen.setCursor(6, 1); // position
    Brain.Screen.print("gpsPositionL: (%.2f, %.2f) @ %.2f", leftGps.xPosition(vex::inches), leftGps.yPosition(vex::inches), leftGps.heading(vex::degrees));

    localize(0.05);

    vex::wait(20, vex::msec);
  }
}
#endif
