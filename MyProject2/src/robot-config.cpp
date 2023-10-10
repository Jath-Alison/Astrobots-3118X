#include "vex.h"
#include "robot-config.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);

motor RightFront = motor(PORT9, ratio6_1, true);
motor RightMiddle = motor(PORT17, ratio6_1, true);
motor RightBack = motor(PORT7, ratio6_1, false);
motor_group RightWheels = motor_group(RightFront, RightMiddle, RightBack);

motor LeftFront = motor(PORT13, ratio6_1, true);
motor LeftMiddle = motor(PORT2, ratio6_1, true);
motor LeftBack = motor(PORT3, ratio6_1, false);
motor_group LeftWheels = motor_group(LeftFront, LeftMiddle, LeftBack);
Jath::TankDrive base(LeftWheels, RightWheels);

motor intakeLeft(PORT5, true);
motor intakeRight(PORT18, false);
motor_group intake(intakeLeft, intakeRight);

pneumatics wings(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}