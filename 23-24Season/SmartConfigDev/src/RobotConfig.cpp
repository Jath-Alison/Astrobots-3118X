#include "RobotConfig.h"

vex::brain Brain;
vex::controller Controller(vex::primary);
RotationSensor Rotation(vex::PORT8);
SmartMotor Motor = SmartMotor("testSmartMotor",vex::motor(vex::PORT15,true))
    .withConstants(75, 1, 25)
    .withControlMode(SmartMotor::Angle)
    .withFollower(vex::motor(vex::PORT12,true))
    .withFollower(vex::PORT11)
    // .withSensor(&Rotation)
;