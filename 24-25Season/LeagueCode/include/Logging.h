#pragma once

#include "WPILogger.h"

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

extern StringLogEntry console;
extern StringLogEntry errors;
extern StringLogEntry competitionState;
extern StringLogEntry robotState;

extern FloatArrayLogEntry Controller_Axes;
extern BooleanArrayLogEntry Controller_Buttons;
