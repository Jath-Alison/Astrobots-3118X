#include "Logging.h"

WPILogger logger;

StringLogEntry console("General/Console");
StringLogEntry errors("General/Errors");
StringLogEntry competitionState("General/CompetitionState");
StringLogEntry robotState("General/RobotState");

Int64ArrayLogEntry Controller1_Axes("DS:joystick0/axes");//
BooleanArrayLogEntry Controller1_Buttons("DS:joystick0/buttons");//
Int64ArrayLogEntry Controller1_Povs("DS:joystick0/povs");//

Int64LogEntry Logger_Size("Logger/loggerSize");//
Int64LogEntry Logger_Capacity("Logger/loggerCapacity");//
DoubleLogEntry Logger_TimeSinceLastLogged("Logger/loggerTimeSinceLastLogged");//

DoubleArrayLogEntry Base_XYR_Cmd("Base/cmd(x-y-r)");//
DoubleArrayLogEntry Base_XYR_Vel("Base/vel(x-y-r)");//
DoubleArrayLogEntry Base_XYR_Pos("Base/pos");//
DoubleArrayLogEntry Base_XYR_Pos_Blue("Base/pos(blue)");//
DoubleArrayLogEntry Base_LeftRight_Cmd("Base/cmd(l-r)");//
DoubleArrayLogEntry Base_LeftRight_Vel("Base/vel(l-r)");//

// DoubleArrayLogEntry Base_LeftRight_SwerveStates("Base/swerveStates");//
DoubleArrayLogEntry Base_L_SwerveState("Base/SwerveState-L");
DoubleArrayLogEntry Base_R_SwerveState("Base/SwerveState-R");

DoubleArrayLogEntry Base_Motors_Voltage("Base/Motors/voltage");//
DoubleArrayLogEntry Base_Motors_Current("Base/Motors/current");//
Int64ArrayLogEntry Base_Motors_Temperature("Base/Motors/temperature");//
DoubleArrayLogEntry Base_Motors_Velocity("Base/Motors/velocity");//
DoubleArrayLogEntry Base_Motors_Position("Base/Motors/position");//

DoubleLogEntry Intake_Cmd("Intake/cmd");
DoubleLogEntry Intake_Voltage("Intake/voltage");
DoubleLogEntry Intake_Current("Intake/current");
DoubleLogEntry Intake_Velocity("Intake/temperature");
DoubleLogEntry Intake_Temperature("Intake/velocity");
DoubleLogEntry Intake_Position("Intake/position");

DoubleLogEntry Arm_Cmd("Arm/cmd");
DoubleLogEntry Arm_Voltage("Arm/voltage");
DoubleLogEntry Arm_Current("Arm/current");
DoubleLogEntry Arm_Velocity("Arm/temperature");
DoubleLogEntry Arm_Temperature("Arm/velocity");
DoubleLogEntry Arm_Position("Arm/position");
DoubleLogEntry Arm_RotAngle("Arm/rotAngle");
DoubleLogEntry Arm_TargetAngle("Arm/targetAngle");

DoubleArrayLogEntry Pose_TrackingPose("Pose/trackingPose");//
DoubleArrayLogEntry Pose_TrackingPose_Blue("Pose/trackingPose(blue)");//
DoubleArrayLogEntry Pose_CenterPose("Pose/centerPose");//
DoubleArrayLogEntry Pose_CenterPose_Blue("Pose/centerPose(blue)");//
DoubleArrayLogEntry Pose_GPSPose("Pose/GPSPose");
DoubleArrayLogEntry Pose_GPSPose_Blue("Pose/GPSPose(blue)");
Int64LogEntry Pose_GPSAccuracy("Pose/GPSAccuracy");

StringLogEntry Auton_Console("Auton/Console");
DoubleArrayLogEntry Auton_TargetPoint("Auton/targetPoint");//
DoubleArrayLogEntry Auton_TargetPoint_Blue("Auton/targetPoint(blue)");//
DoubleArrayLogEntry Auton_CurrentPath("Auton/currentPath");
DoubleArrayLogEntry Auton_CurrentPath_Blue("Auton/currentPath(blue)");