#include "RobotConfig.h"

vex::brain Brain;
vex::controller controller1(vex::primary);

vex::motor leftMotorA(vex::PORT11, vex::gearSetting::ratio6_1, !false);
vex::motor leftMotorB(vex::PORT12, vex::gearSetting::ratio6_1, !false);
vex::motor leftMotorC(vex::PORT13, vex::gearSetting::ratio6_1, !false);
vex::motor_group leftMotors(leftMotorA, leftMotorB, leftMotorC);

vex::motor rightMotorA(vex::PORT18, vex::gearSetting::ratio6_1, !true);
vex::motor rightMotorB(vex::PORT19, vex::gearSetting::ratio6_1, !true);
vex::motor rightMotorC(vex::PORT20, vex::gearSetting::ratio6_1, !true);
vex::motor_group rightMotors(rightMotorA, rightMotorB, rightMotorC);

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

vex::pneumatics climbUp(Brain.ThreeWirePort.F);
vex::pneumatics climbDown(Brain.ThreeWirePort.B);

vex::pneumatics park(Brain.ThreeWirePort.C);
vex::pneumatics odomRetract(Brain.ThreeWirePort.D);

vex::pneumatics leftWing(Brain.ThreeWirePort.A);
vex::pneumatics rightWing(Brain.ThreeWirePort.E);

vex::limit climblimit = vex::limit(Brain.ThreeWirePort.G);

#pragma message("building for the manager")
vex::message_link link( vex::PORT11, "linkA", vex::linkType::manager );


//// vex::message_link link( vex::PORT11, "linkA", vex::linkType::manager );
//// vex::message_link link( vex::PORT1, "linkA", vex::linkType::worker );