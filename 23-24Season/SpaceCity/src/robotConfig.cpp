#include "robotConfig.h"

vex::brain Brain;
vex::controller controller1(vex::primary);

x::Leds xleds(36);
addressable_led leds(Brain.ThreeWirePort.B, 36);

vex::motor leftMotorF(vex::PORT1, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorM(vex::PORT2, vex::gearSetting::ratio6_1, false);
vex::motor leftMotorB(vex::PORT3, vex::gearSetting::ratio6_1, true);
vex::motor_group leftMotors(leftMotorF, leftMotorM, leftMotorB);

vex::motor rightMotorF(vex::PORT6, vex::gearSetting::ratio6_1, true);
vex::motor rightMotorM(vex::PORT16, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorB(vex::PORT9, vex::gearSetting::ratio6_1, true);
vex::motor_group rightMotors(rightMotorF, rightMotorM, rightMotorB);

vex::inertial inert(vex::PORT11);

x::TankDrive drive = x::TankDrive(leftMotors, rightMotors).withScales(1, 1, 1);
x::SmartDrive smartDrive = x::SmartDrive(drive, inert); 

x::xMotor intake = x::xMotor( "intake", vex::motor(vex::PORT19, vex::gearSetting::ratio6_1, true)).withSpeedMode(false);
x::xMotor flywheel = x::xMotor( "flywheel", vex::motor(vex::PORT5, vex::gearSetting::ratio6_1, true)).withSpeedMode(false);

vex::pneumatics wings(Brain.ThreeWirePort.A);
vex::pneumatics climb(Brain.ThreeWirePort.H);

x::Vec2 initPos = x::XandY(0,0);
x::Angle initDir = x::Angle(0);

vex::gps GPS = vex::gps(vex::PORT14, -76.20, -127.00, vex::mm, 180);

std::string AllianceColor = "no color";