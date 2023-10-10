using namespace vex;

#include "JathLib/TankDrive.h"

extern brain Brain;

// VEXcode devices
extern controller Controller1;

extern motor RightFront;
extern motor RightMiddle;
extern motor RightBack;
extern motor_group RightWheels;

extern motor LeftBack;
extern motor LeftFront;
extern motor LeftMiddle;
extern motor_group LeftWheels;

extern Jath::TankDrive base;

extern motor intakeLeft;
extern motor intakeRight;
extern motor_group intake;

extern pneumatics wings;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );