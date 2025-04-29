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

vex::gps gpsSensorL(vex::PORT20, -5.0, 0, vex::inches, 270);
vex::gps gpsSensorR(vex::PORT20, 5.0, 0, vex::inches, 90);

vex::motor leftMotorA(vex::PORT1, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorB(vex::PORT2, vex::gearSetting::ratio6_1, !true);
vex::motor leftMotorC(vex::PORT3, vex::gearSetting::ratio6_1, true);//not front?
vex::motor_group leftMotors(leftMotorA, leftMotorB, leftMotorC);

vex::motor rightMotorA(vex::PORT11, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorB(vex::PORT12, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorC(vex::PORT13, vex::gearSetting::ratio6_1, !false);
vex::motor_group rightMotors(rightMotorA, rightMotorB, rightMotorC);

vex::inertial inert(vex::PORT20);

art::TankDrive drive = art::TankDrive(leftMotors, rightMotors);
AsyncDrive asyncDrive = AsyncDrive(drive, inert)
                            .withGearRatio(36.f / 48.f)
                            .withWheelSize(art::Inches(2.75))
                            .withDefaultPIDs(oldDrivePID, oldTurnPID)
                            .withHorizontalTracker(
                                vex::rotation(vex::PORT20, false),
                                art::Inches(2),
                                1.0);

// .withDriveForPID(art::PID()
//         .withConstants(10, 0.06, -5.0)//Somehow already in 1/(1inch) P * 3, D * 4
//         .withIntegralZone(art::Revolutions(art::Inches(2) / (M_PI * art::Inches(2.75) * (36.f/48.f))))//still need conversion from inches to revolutions
//         .withTimeout(7.5)
//         .withSettleZone(art::Revolutions(art::Inches(1) / (M_PI * art::Inches(2.75) * (36.f/48.f))))
//         .withSettleTimeout(0.25)
//     )
//     .withTurnForPID(art::PID()
//         .withConstants(3/(art::Degrees(1)), 3.0, -750)
//         .withIntegralZone(art::Degrees(10))
//         .withTimeout(2)
//         .withSettleZone(art::Degrees(3))
//         .withSettleTimeout(0.25)
//     )
//     .withTurnToPID(art::PID()
//         .withConstants(3/(art::Degrees(1)), 3.0, -750)// / by 2, 10, -500
//         .withIntegralZone(art::Degrees(15))
//         .withTimeout(3)
//         .withSettleZone(art::Degrees(3))
//         .withSettleTimeout(0.25)//Lowkey could be turned down to 0.25
//     )

// art::SimpleMotor intake  = art::SimpleMotor(vex::motor(vex::PORT3, vex::gearSetting::ratio6_1, false))
//     .withSpeedMode(false);

vex::motor intakeMotorA(vex::PORT5, vex::gearSetting::ratio6_1, false);
vex::motor intakeMotorB(vex::PORT7, vex::gearSetting::ratio6_1, false);
vex::motor_group intakeMotors(intakeMotorA, intakeMotorB);

Intake intake(intakeMotors, vex::optical(vex::PORT17));

vex::digital_out clamp(Brain.ThreeWirePort.A);
bool clampState = false;
;

vex::motor armMotorA(vex::PORT6, vex::gearSetting::ratio6_1, true);
vex::motor armMotorB(vex::PORT16, vex::gearSetting::ratio6_1, false);
vex::motor_group armMotors(armMotorA, armMotorB);

Arm arm = Arm(
    armMotors,
     art::PID()
      .withConstants(3 / (art::Degrees(1)), 0, -100)
      .withSettleZone(art::Degrees(5))
      .withSettleTimeout(0.07)
      .withTimeout(1)

);

// art::SimpleMotor arm = art::SimpleMotor(vex::motor(vex::PORT4, vex::gearSetting::ratio36_1, false))
//     .withSpeedMode(true);
// vex::rotation armRot = vex::rotation(vex::PORT14, true);

// art::PID armPID = art::PID()
//         .withConstants(1/(art::Degrees(1)), 0, -200)
//         // .withIntegralZone(art::Degrees(15))
//         // .withTimeout(10)
//         // .withSettleZone(art::Degrees(3))
//         // .withSettleTimeout(0.75)
//         ;

vex::digital_out doinkerDeployR(Brain.ThreeWirePort.B);
bool doinkerDeployRState = false;
vex::digital_out doinkerDeployL(Brain.ThreeWirePort.H);
bool doinkerDeployLState = false;

vex::aivision FrontVision(vex::PORT20);
// vex::optical intakeOptical(vex::PORT17);
// vex::optical outtakeOptical(vex::PORT15);