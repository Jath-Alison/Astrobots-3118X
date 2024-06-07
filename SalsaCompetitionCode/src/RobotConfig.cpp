#include "RobotConfig.h"

vex::brain Brain;
vex::controller controller1(vex::primary);

vex::motor leftMotorA(vex::PORT17, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorB(vex::PORT18, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorC(vex::PORT19, vex::gearSetting::ratio6_1, false);
vex::motor leftMotorD(vex::PORT20, vex::gearSetting::ratio6_1, true);
vex::motor_group leftMotors(leftMotorA, leftMotorB, leftMotorC, leftMotorD);

vex::motor rightMotorA(vex::PORT11, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorB(vex::PORT12, vex::gearSetting::ratio6_1, !false);
vex::motor rightMotorC(vex::PORT13, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorD(vex::PORT14, vex::gearSetting::ratio6_1, false);
vex::motor_group rightMotors(rightMotorA, rightMotorB, rightMotorC, rightMotorD);

vex::inertial inert(vex::PORT15);

Jath::TankDrive drive = Jath::TankDrive(leftMotors, rightMotors).withScales(1, 1, 1);
Jath::SmartDrive smartDrive = Jath::SmartDrive(drive, inert)
    .withWheelSize(Jath::Inches(2.75))
    .withGearRatio(24.f/32.f)
    // .withHorizontalTracker(
    //     vex::rotation(vex::PORT19, true),
    //     Jath::Inches(2.75),
    //     3.f/5.f,
    //     Jath::Inches(3)
    // )
    ;

vex::motor a = vex::motor(vex::PORT1, vex::gearSetting::ratio6_1, true);
vex::motor b = vex::motor(vex::PORT10, vex::gearSetting::ratio6_1, false);

Jath::jMotorGroup intake = Jath::jMotorGroup(
        std::string("intake"), 
        vex::motor_group(
            a,b
        )
    ).withSpeedMode(false);

Jath::Vec2 initPos = Jath::Vec2::XandY(0, 0);
Jath::Angle initDir = Jath::Angle(0);

#pragma message("building for the manager")
vex::message_link link( vex::PORT11, "linkA", vex::linkType::manager );


//// vex::message_link link( vex::PORT11, "linkA", vex::linkType::manager );
//// vex::message_link link( vex::PORT1, "linkA", vex::linkType::worker );