#include "robotConfig.h"

vex::brain Brain;
vex::controller controller1(vex::primary);

// x::Leds xleds(36);
// addressable_led leds(Brain.ThreeWirePort.B, 36);

vex::motor leftMotorF(vex::PORT11, vex::gearSetting::ratio6_1, !false);
vex::motor leftMotorM(vex::PORT12, vex::gearSetting::ratio6_1, !false);
vex::motor leftMotorB(vex::PORT13, vex::gearSetting::ratio6_1, !false);
vex::motor_group leftMotors(leftMotorF, leftMotorM, leftMotorB);

vex::motor rightMotorF(vex::PORT18, vex::gearSetting::ratio6_1, !true);
vex::motor rightMotorM(vex::PORT19, vex::gearSetting::ratio6_1, !true);
vex::motor rightMotorB(vex::PORT20, vex::gearSetting::ratio6_1, !true);
vex::motor_group rightMotors(rightMotorF, rightMotorM, rightMotorB);

vex::inertial inert(vex::PORT5);

Jath::TankDrive drive = Jath::TankDrive(leftMotors, rightMotors).withScales(1, 1, 1);
Jath::SmartDrive smartDrive = Jath::SmartDrive(drive, inert)
    .withWheelSize(Jath::Inches(2.75))
    .withGearRatio(1.0)
    .withHorizontalTracker(
        vex::rotation(vex::PORT2, true),
        Jath::Inches(2.75),
        3.f/5.f
    )
    ;

vex::motor a = vex::motor(vex::PORT1, vex::gearSetting::ratio6_1, true);
vex::motor b = vex::motor(vex::PORT8, vex::gearSetting::ratio6_1, false);

Jath::jMotorGroup intake = Jath::jMotorGroup(
        std::string("intake"), 
        vex::motor_group(
            a,b
        )
    ).withSpeedMode(false);
// x::xMotor flywheel = x::xMotor( "flywheel", vex::motor(vex::PORT5, vex::gearSetting::ratio6_1, true)).withSpeedMode(false);

vex::pneumatics climbUp(Brain.ThreeWirePort.F);
vex::pneumatics climbDown(Brain.ThreeWirePort.B);

vex::pneumatics park(Brain.ThreeWirePort.C);
vex::pneumatics odomRetract(Brain.ThreeWirePort.D);

vex::pneumatics leftWing(Brain.ThreeWirePort.A);
vex::pneumatics rightWing(Brain.ThreeWirePort.E);

vex::limit climblimit = vex::limit(Brain.ThreeWirePort.G);

//wing left - a
//climb down - b


Jath::Vec2 initPos = Jath::XandY(0, 0);
Jath::Angle initDir = Jath::Angle(0);

// vex::gps GPS = vex::gps(vex::PORT14, -76.20, -127.00, vex::mm, 180);

std::string AllianceColor = "no color";