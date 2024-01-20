#include "RobotConfig.h"

vex::brain Brain;
vex::controller Controller(vex::primary);
RotationSensor Rotation(vex::PORT8);
SmartMotor Motor = SmartMotor("testSmartMotor",vex::PORT15)
    .withConstants(75, 1, 25)
    .withControlMode(SmartMotor::Angle)
    .withFollower(vex::PORT10)
    .withSensor(&Rotation)
;