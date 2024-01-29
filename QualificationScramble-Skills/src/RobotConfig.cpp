#include "RobotConfig.h"

std::vector< jwb::SmartMotor* > jwb::SmartMotor::m_allMotors;

vex::brain Brain;
vex::controller Controller(vex::primary);

jwb::SmartMotor LeftMotors = jwb::SmartMotor("LeftMotors", vex::motor(vex::PORT1, true))
    .withFollower(vex::motor(vex::PORT2, false))
    .withFollower(vex::motor(vex::PORT3, true))
    .withControlMode(jwb::SmartMotor::ControlMode::DutyCycle)
;
jwb::SmartMotor RightMotors = jwb::SmartMotor("RightMotors", vex::motor(vex::PORT6, false))
    .withFollower(vex::motor(vex::PORT16, true))
    .withFollower(vex::motor(vex::PORT9, false))
    .withControlMode(jwb::SmartMotor::ControlMode::DutyCycle)
;

jwb::SmartMotor Flywheel = jwb::SmartMotor("Flywheel", vex::motor(vex::PORT19, true))
    .withControlMode(jwb::SmartMotor::ControlMode::DutyCycle)
;
jwb::SmartMotor Intake = jwb::SmartMotor("Intake", vex::motor(vex::PORT5, true))
    .withControlMode(jwb::SmartMotor::ControlMode::DutyCycle)
;

vex::pneumatics wings(Brain.ThreeWirePort.A);
vex::pneumatics climb(Brain.ThreeWirePort.H);

vex::gps GPS = vex::gps(vex::PORT14, -76.20, -127.00, vex::mm, 180);