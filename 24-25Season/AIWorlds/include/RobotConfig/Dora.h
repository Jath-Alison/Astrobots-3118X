#pragma once
#include "vex.h"
#include "ART/ART.h"
#include "Subsystems/AsyncDrive.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Intake.h"

// extern vex::gps gpsSensorL;
// extern vex::gps gpsSensorR;

extern art::PID oldDrivePID;
extern art::PID oldTurnPID;

extern vex::motor leftMotorA;
extern vex::motor leftMotorB;
extern vex::motor leftMotorC;
extern vex::motor_group leftMotors;

extern vex::motor rightMotorA;
extern vex::motor rightMotorB;
extern vex::motor rightMotorC;
extern vex::motor_group rightMotors;

extern vex::inertial inert;

extern art::TankDrive drive;
extern AsyncDrive asyncDrive;

extern Intake intake;

extern vex::digital_out clamp; extern bool clampState;
extern vex::digital_out clamp2;

extern vex::rotation armRot;
extern art::PID armPID;

extern Arm arm;

extern vex::digital_out pto; extern bool ptoState; extern bool climbControls;
extern vex::digital_out climbDeploy; extern bool climbDeployState;
extern vex::digital_out climbDeploy2;
