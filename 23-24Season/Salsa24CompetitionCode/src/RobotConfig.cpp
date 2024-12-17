#include "RobotConfig.h"

//intake 1& 10(r&l)
//flappers 16&18 (l&r)
//rightwheels 2,4,5 abc c reversed
//leftwheels 17,18,19 abc c reversed
//inert 8
//shooter 7 & 9

vex::brain Brain;
vex::controller controller1(vex::primary);

vex::motor leftMotorA(vex::PORT17, vex::gearSetting::ratio6_1, !true);
vex::motor leftMotorB(vex::PORT18, vex::gearSetting::ratio6_1, !true);
vex::motor leftMotorC(vex::PORT19, vex::gearSetting::ratio6_1, !false);
vex::motor_group leftMotors(leftMotorA, leftMotorB, leftMotorC);

vex::motor rightMotorA(vex::PORT2, vex::gearSetting::ratio6_1, !false);
vex::motor rightMotorB(vex::PORT4, vex::gearSetting::ratio6_1, !false);
vex::motor rightMotorC(vex::PORT5, vex::gearSetting::ratio6_1, !true);
vex::motor_group rightMotors(rightMotorA, rightMotorB, rightMotorC);

vex::inertial inert(vex::PORT8);

Jath::TankDrive drive = Jath::TankDrive(leftMotors, rightMotors).withScales(1, 1, 1);
Jath::SmartDrive smartDrive = Jath::SmartDrive(drive, inert)
    .withWheelSize(Jath::Inches(4))
    .withGearRatio(24.f/48.f)
    // .withHorizontalTracker(
    //     vex::rotation(vex::PORT19, true),
    //     Jath::Inches(2.75),
    //     3.f/5.f,
    //     Jath::Inches(3)
    // )
    ;

vex::motor intake_a = vex::motor(vex::PORT1, vex::gearSetting::ratio6_1, true);
vex::motor intake_b = vex::motor(vex::PORT10, vex::gearSetting::ratio6_1, false);

Jath::jMotorGroup intake = Jath::jMotorGroup(
        std::string("intake"), 
        vex::motor_group(
            intake_a,intake_b
        )
    ).withSpeedMode(false);

vex::motor flapper_a = vex::motor(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor flapper_b = vex::motor(vex::PORT12, vex::gearSetting::ratio18_1, false);

Jath::jMotor leftFlapper("leftFlapper", flapper_a);
Jath::jMotor rightFlapper("rightFlapper", flapper_b);

vex::motor shooter_a = vex::motor(vex::PORT7, vex::gearSetting::ratio6_1, true);
vex::motor shooter_b = vex::motor(vex::PORT9, vex::gearSetting::ratio6_1, true);
Jath::jMotorGroup shooter = Jath::jMotorGroup(
        std::string("shooter"), 
        vex::motor_group(
            shooter_a,shooter_b
        )   
    ).withSpeedMode(false);


#pragma message("building for the worker")
vex::message_link link( vex::PORT20, "linkA", vex::linkType::worker );


//// vex::message_link link( vex::PORT11, "linkA", vex::linkType::manager );
//// vex::message_link link( vex::PORT1, "linkA", vex::linkType::worker );