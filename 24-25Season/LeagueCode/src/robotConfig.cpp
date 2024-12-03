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

vex::gps gpsSensor(vex::PORT6, 5.0, 0, vex::inches, 90);

vex::motor leftMotorA (vex::PORT19, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorB (vex::PORT11, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorC (vex::PORT12, vex::gearSetting::ratio6_1, true);
vex::motor_group leftMotors (leftMotorA, leftMotorB, leftMotorC);

vex::motor rightMotorA (vex::PORT9, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorB (vex::PORT1, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorC (vex::PORT2, vex::gearSetting::ratio6_1, false);
vex::motor_group rightMotors (rightMotorA, rightMotorB, rightMotorC);

vex::inertial inert (vex::PORT18);

art::TankDrive drive = art::TankDrive(leftMotors, rightMotors);
art::SmartDrive smartDrive = art::SmartDrive(drive, inert)
    .withGearRatio(36.f/48.f)
    .withWheelSize(art::Inches(2.75))
    .withHorizontalTracker(
      vex::rotation(vex::PORT13, false),
      art::Inches(2),
      1.0
    )
    .withDriveForPID(art::PID()
        .withConstants(5, 0.6, -5.0)//Somehow already in 1/(1inch)
        .withIntegralZone(art::Revolutions(art::Inches(2) / (M_PI * art::Inches(2.75) * (36.f/48.f))))//still need conversion from inches to revolutions
        .withTimeout(7.5)
        .withSettleZone(art::Revolutions(art::Inches(1) / (M_PI * art::Inches(2.75) * (36.f/48.f))))
        .withSettleTimeout(0.25)
    )
    .withTurnForPID(art::PID()
        .withConstants(2/(art::Degrees(1)), 10, -500)
        .withIntegralZone(art::Degrees(10))
        .withTimeout(2)
        .withSettleZone(art::Degrees(3))
        .withSettleTimeout(0.25)
    )
    .withTurnToPID(art::PID()
        .withConstants(2/(art::Degrees(1)), 10, -500)// / by 2, 10, -500
        .withIntegralZone(art::Degrees(15))
        .withTimeout(10)
        .withSettleZone(art::Degrees(3))
        .withSettleTimeout(0.75)
    )
    ;

art::SimpleMotor intake  = art::SimpleMotor(vex::motor(vex::PORT3, vex::gearSetting::ratio6_1, false))
    .withSpeedMode(false);
vex::digital_out clamp(Brain.ThreeWirePort.A); bool clampState = false;;

art::SimpleMotor arm = art::SimpleMotor(vex::motor(vex::PORT4, vex::gearSetting::ratio36_1, false))
    .withSpeedMode(true);
vex::rotation armRot = vex::rotation(vex::PORT14, true);

art::PID armPID = art::PID()
        .withConstants(3/(art::Degrees(1)), 0, -200)
        // .withIntegralZone(art::Degrees(15))
        // .withTimeout(10)
        // .withSettleZone(art::Degrees(3))
        // .withSettleTimeout(0.75)
        ;

art::Angle armTarget = 0;
double armOut = 0;
bool macroRunning=false;

vex::digital_out doinkerDeploy(Brain.ThreeWirePort.D); bool doinkerDeployState = false;;
vex::digital_out doinkerClamp(Brain.ThreeWirePort.E); bool doinkerClampState = false;;


bool isBlue = true;