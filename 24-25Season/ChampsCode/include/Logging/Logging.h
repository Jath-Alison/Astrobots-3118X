#pragma once

#include "WPILogger.h"
#include "vex.h"

namespace logging
{

    extern WPILogger logger;

    /**
     * Entry Planning
     *
     * - Robot
     *      - Subsystems
     *          - Base
     *              - X, Y, Rot Commands
     *              - X, Y, Rot Vel
     *              - X, Y, Rot Pos
     *              - Left, Right Command
     *              - Left, Right Vel
     *              - Left, Right "Swerve States" (V + Angle)
     *              - Motors:
     *                  - Voltage
     *                  - Current
     *                  - Temperature
     *                  - Velocity
     *                  - Position
     *          - Intake
     *              - Cmd
     *              - Voltage
     *              - Current
     *              - Velocity
     *              - Temperature
     *              - Position
     *          - Arm?
     *              - Cmd
     *              - Voltage
     *              - Current
     *              - Velocity
     *              - Temperature
     *              - Position
     *      - Robot State
     *      - Pose
     *      -
     * - Auton
     *      - Target Point
     * - Match
     *      - Match State
     *      - Competition State
     * - Controller
     *      - Buttons
     *      - Joystick Values
     * - General?
     *      - Errors
     *      - Console
     * - Logger
     *      - Size
     *      - Capacity
     *      - Time since last Logged
     */

    // General Entries
    extern StringLogEntry console;
    extern StringLogEntry errors;
    extern StringLogEntry competitionState;
    extern StringLogEntry robotState;

    // Driver Entries
    extern Int64ArrayLogEntry Controller1_Axes;
    extern BooleanArrayLogEntry Controller1_Buttons;
    extern Int64ArrayLogEntry Controller1_Povs;

    // Logger Related Entries
    extern Int64LogEntry Logger_Size;
    extern Int64LogEntry Logger_Capacity;
    extern DoubleLogEntry Logger_TimeSinceLastLogged;

    // Robot Entries
    // SmartDrive
    extern DoubleArrayLogEntry Base_XYR_Cmd;
    extern DoubleArrayLogEntry Base_XYR_Vel;
    extern DoubleArrayLogEntry Base_XYR_Pos;
    extern DoubleArrayLogEntry Base_XYR_Pos_Blue;
    extern DoubleArrayLogEntry Base_LeftRight_Cmd;
    extern DoubleArrayLogEntry Base_LeftRight_Vel;
    extern DoubleArrayLogEntry Base_VelSwerveState;

    extern DoubleArrayLogEntry Base_LR_SwerveState;

    extern DoubleArrayLogEntry Base_Motors_Voltage;
    extern DoubleArrayLogEntry Base_Motors_Current;
    extern Int64ArrayLogEntry Base_Motors_Temperature;
    extern DoubleArrayLogEntry Base_Motors_Velocity;
    extern DoubleArrayLogEntry Base_Motors_Position;

    // SmartDrivePIDs

    extern DoubleLogEntry Base_DriveTo_PID_P;
    extern DoubleLogEntry Base_DriveTo_PID_I;
    extern DoubleLogEntry Base_DriveTo_PID_D;

    extern DoubleLogEntry Base_DriveTo_PID_kP;
    extern DoubleLogEntry Base_DriveTo_PID_kI;
    extern DoubleLogEntry Base_DriveTo_PID_kD;
    extern DoubleLogEntry Base_Driveto_PID_ff;

    extern DoubleLogEntry Base_DriveTo_PID_target;
    extern DoubleLogEntry Base_DriveTo_PID_feedback;
    extern DoubleLogEntry Base_DriveTo_PID_error;
    extern DoubleLogEntry Base_DriveTo_PID_integral;
    extern DoubleLogEntry Base_DriveTo_PID_derivative;
    extern DoubleLogEntry Base_DriveTo_PID_output;

    extern DoubleLogEntry Base_DriveTo_PID_settleZone;
    extern DoubleLogEntry Base_DriveTo_PID_timeSettled;
    extern DoubleLogEntry Base_DriveTo_PID_timePassed;

    extern DoubleLogEntry Base_TurnTo_PID_P;
    extern DoubleLogEntry Base_TurnTo_PID_I;
    extern DoubleLogEntry Base_TurnTo_PID_D;

    extern DoubleLogEntry Base_TurnTo_PID_kP;
    extern DoubleLogEntry Base_TurnTo_PID_kI;
    extern DoubleLogEntry Base_TurnTo_PID_kD;
    extern DoubleLogEntry Base_TurnTo_PID_ff;

    extern DoubleLogEntry Base_TurnTo_PID_target;
    extern DoubleLogEntry Base_TurnTo_PID_feedback;
    extern DoubleLogEntry Base_TurnTo_PID_error;
    extern DoubleLogEntry Base_TurnTo_PID_integral;
    extern DoubleLogEntry Base_TurnTo_PID_derivative;
    extern DoubleLogEntry Base_TurnTo_PID_output;

    extern DoubleLogEntry Base_TurnTo_PID_settleZone;
    extern DoubleLogEntry Base_TurnTo_PID_timeSettled;
    extern DoubleLogEntry Base_TurnTo_PID_timePassed;

    // Intake
    extern DoubleLogEntry Intake_Cmd;
    extern DoubleLogEntry Intake_Voltage;
    extern DoubleLogEntry Intake_Current;
    extern DoubleLogEntry Intake_Velocity;
    extern DoubleLogEntry Intake_Temperature;
    extern DoubleLogEntry Intake_Position;
    // Arm
    extern DoubleLogEntry Arm_Cmd;
    extern DoubleLogEntry Arm_Voltage;
    extern DoubleLogEntry Arm_Current;
    extern DoubleLogEntry Arm_Velocity;
    extern DoubleLogEntry Arm_Temperature;
    extern DoubleLogEntry Arm_Position;
    extern DoubleLogEntry Arm_RotAngle;
    extern DoubleLogEntry Arm_TargetAngle;

    // Pose
    extern DoubleArrayLogEntry Pose_TrackingPose;
    extern DoubleArrayLogEntry Pose_TrackingPose_Blue;
    extern DoubleArrayLogEntry Pose_CenterPose;
    extern DoubleArrayLogEntry Pose_CenterPose_Blue;
    extern DoubleArrayLogEntry Pose_GPSPose_L;
    extern DoubleArrayLogEntry Pose_GPSPose_Blue_L;
    extern Int64LogEntry Pose_GPSAccuracy_L;
    extern DoubleArrayLogEntry Pose_GPSPose_R;
    extern DoubleArrayLogEntry Pose_GPSPose_Blue_R;
    extern Int64LogEntry Pose_GPSAccuracy_R;

    // Auton Entries
    extern StringLogEntry Auton_Console;
    extern DoubleArrayLogEntry Auton_TargetPoint;
    extern DoubleArrayLogEntry Auton_TargetPoint_Blue;
    extern DoubleArrayLogEntry Auton_CurrentPath;
    extern DoubleArrayLogEntry Auton_CurrentPath_Blue;

    // Vision

    extern DoubleArrayLogEntry Vision_RedObjectPos;
    extern DoubleArrayLogEntry Vision_BlueObjectPos;
    extern DoubleArrayLogEntry Vision_RedObjectDim;
    extern DoubleArrayLogEntry Vision_BlueObjectDim;

    extern Int64LogEntry Optics_LowerOpticalHue;
    extern BooleanLogEntry Optics_LowerOpticalDist;
    extern Int64LogEntry Optics_UpperOpticalHue;
    extern BooleanLogEntry Optics_UpperOpticalDist;

    int logLoop();
    extern vex::thread logThread;

} // namespace logging