/**
 * @file robotConfig.cpp
 * @author Jath Alison (Jath.Alison@gmail.com)
 * @brief Source defining objects that configure the robot such as the Brain,
 * Motors, and additional Devices
 * @version 1.0-beta
 * @date 06-26-2024
 *
 * @copyright Copyright (c) 2024
 *
 * This file will definine all the devices that were delcared in the various
 * headers. Anything that can be defined to change the the configuration of the
 * robot will be put here. This includes, but isn't limited to motors, sensors
 * and important variables.
 */

#include "robotConfig.h"
#include "ART/ART.h"

vex::brain Brain;
vex::controller Controller1;


vex::motor leftMotorA (vex::PORT16, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorB (vex::PORT17, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorC (vex::PORT18, vex::gearSetting::ratio6_1, true);
vex::motor_group leftMotors (leftMotorA, leftMotorB, leftMotorC);

vex::motor rightMotorA (vex::PORT8, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorB (vex::PORT9, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorC (vex::PORT10, vex::gearSetting::ratio6_1, false);
vex::motor_group rightMotors (rightMotorA, rightMotorB, rightMotorC);

vex::inertial inert (vex::PORT1);

art::TankDrive drive = art::TankDrive(leftMotors, rightMotors);
art::SmartDrive smartDrive = art::SmartDrive(drive, inert)
    .withGearRatio(36.f/48.f)
    .withWheelSize(art::Inches(2.75))
    .withHorizontalTracker(
      vex::rotation(vex::PORT2, false),
      art::Inches(2),
      1.0
    )
    .withDriveForPID(art::PID()
        .withConstants(5 * (M_PI * art::Inches(2.75) * (36.f/48.f)) / art::Inches(1), 0.0, 0.5 * (M_PI * art::Inches(2.75) * (36.f/48.f)) / art::Inches(1) )
        .withIntegralZone(art::Inches(3) / (M_PI * art::Inches(2.75) * (36.f/48.f)))
        .withTimeout(7.5)
        .withSettleZone(art::Inches(1) / (M_PI * art::Inches(2.75) * (36.f/48.f)))
        .withSettleTimeout(0.5)
    )
    .withTurnForPID(art::PID()
        .withConstants(2/(art::Degrees(1)), 10, -500)
        .withIntegralZone(art::Degrees(10))
        .withTimeout(2)
        .withSettleZone(art::Degrees(3))
        .withSettleTimeout(0.25)
    )
    .withTurnToPID(art::PID()
        .withConstants(2/(art::Degrees(1)), 10, -500)
        .withIntegralZone(art::Degrees(10))
        .withTimeout(2)
        .withSettleZone(art::Degrees(3))
        .withSettleTimeout(0.25)
    )
    ;

art::SimpleMotor intake  = art::SimpleMotor(vex::motor(vex::PORT14, vex::gearSetting::ratio6_1, false))
    .withSpeedMode(true);
vex::digital_out clamp(Brain.ThreeWirePort.G);