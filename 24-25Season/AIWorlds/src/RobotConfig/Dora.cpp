#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dora

art::PID oldDrivePID = art::PID()
    .withConstants(10, 0.06, -5.0)//Somehow already in 1/(1inch) P * 3, D * 4
    .withIntegralZone(art::Revolutions(art::Inches(2) / (M_PI * art::Inches(2.75) * (36.f/48.f))))//still need conversion from inches to revolutions
    .withTimeout(7.5)   
    .withSettleZone(art::Revolutions(art::Inches(1) / (M_PI * art::Inches(2.75) * (36.f/48.f))))
    .withSettleTimeout(0.1);

art::PID oldTurnPID = art::PID()
    .withConstants(3/(art::Degrees(1)), 3.0, -750)
    .withIntegralZone(art::Degrees(10))
    .withTimeout(2)
    .withSettleZone(art::Degrees(3))
    .withSettleTimeout(0.1);

vex::message_link link( vex::PORT17, "linkA", vex::linkType::manager);

// vex::gps gpsSensorL(vex::PORT20, -5.0, 0, vex::inches, 270);
// vex::gps gpsSensorR(vex::PORT14, 6.0, 6.0, vex::inches, 90);

vex::motor leftMotorA(vex::PORT1, vex::gearSetting::ratio6_1, !true);
vex::motor leftMotorB(vex::PORT2, vex::gearSetting::ratio6_1, true);
vex::motor leftMotorC(vex::PORT11, vex::gearSetting::ratio6_1, true);
vex::motor_group leftMotors(leftMotorB, leftMotorA, leftMotorC);

vex::motor rightMotorA(vex::PORT10, vex::gearSetting::ratio6_1, !false);
vex::motor rightMotorB(vex::PORT9, vex::gearSetting::ratio6_1, false);
vex::motor rightMotorC(vex::PORT16, vex::gearSetting::ratio6_1, false);//20->16
vex::motor_group rightMotors(rightMotorC, rightMotorA, rightMotorB);

vex::inertial inert(vex::PORT14);

art::TankDrive drive = art::TankDrive(leftMotors, rightMotors);
AsyncDrive asyncDrive = AsyncDrive(drive, inert)
                            .withGearRatio(36.f / 48.f)
                            .withWheelSize(art::Inches(2.75))
                            .withDefaultPIDs(oldDrivePID, oldTurnPID);

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

vex::motor intakeMotorA(vex::PORT3, vex::gearSetting::ratio6_1, false);
vex::motor intakeMotorB(vex::PORT8, vex::gearSetting::ratio6_1, !false);
vex::motor_group intakeMotors(intakeMotorB, intakeMotorA);

Intake intake(intakeMotorA, intakeMotorB, vex::optical(vex::PORT9));

vex::digital_out clamp(Brain.ThreeWirePort.G);
vex::digital_out clamp2(Brain.ThreeWirePort.H);
bool clampState = false;

vex::motor armMotorA(vex::PORT12, vex::gearSetting::ratio6_1, true);
vex::motor armMotorB(vex::PORT19, vex::gearSetting::ratio6_1, false);
vex::rotation armRot = vex::rotation(vex::PORT13, true);

Arm arm = Arm(
    armMotorA,
    armMotorB,
     art::PID()
      .withConstants(1 / (art::Degrees(1)), 0, -100)
      .withSettleZone(art::Degrees(5))
      .withSettleTimeout(0.07)
      .withTimeout(1)

);

vex::digital_out pto(Brain.ThreeWirePort.E);
bool ptoState = false;
bool climbControls = false;

vex::digital_out climbDeploy(Brain.ThreeWirePort.A);
vex::digital_out climbDeploy2(Brain.ThreeWirePort.B);
bool climbDeployState = false;
#endif
