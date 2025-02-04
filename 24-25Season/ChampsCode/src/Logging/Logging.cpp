#include "Logging/Logging.h"

namespace logging
{

    WPILogger logger;

    StringLogEntry console("General/Console");
    StringLogEntry errors("General/Errors");
    StringLogEntry competitionState("General/CompetitionState");
    StringLogEntry robotState("General/RobotState");

    Int64ArrayLogEntry Controller1_Axes("DS:joystick0/axes");         //
    BooleanArrayLogEntry Controller1_Buttons("DS:joystick0/buttons"); //
    Int64ArrayLogEntry Controller1_Povs("DS:joystick0/povs");         //

    Int64LogEntry Logger_Size("Logger/loggerSize");                                //
    Int64LogEntry Logger_Capacity("Logger/loggerCapacity");                        //
    DoubleLogEntry Logger_TimeSinceLastLogged("Logger/loggerTimeSinceLastLogged"); //

    DoubleArrayLogEntry Base_XYR_Cmd("Base/cmd(x-y-r)");     //
    DoubleArrayLogEntry Base_XYR_Vel("Base/vel(x-y-r)");     //
    DoubleArrayLogEntry Base_XYR_Pos("Base/pos");            //
    DoubleArrayLogEntry Base_XYR_Pos_Blue("Base/pos(blue)"); //
    DoubleArrayLogEntry Base_LeftRight_Cmd("Base/cmd(l-r)"); //
    DoubleArrayLogEntry Base_LeftRight_Vel("Base/vel(l-r)"); //
    DoubleArrayLogEntry Base_VelSwerveState("Base/vel(swerveState)");

    // DoubleArrayLogEntry Base_LeftRight_SwerveStates("Base/swerveStates");//
    DoubleArrayLogEntry Base_LR_SwerveState("Base/SwerveState-LR");

    DoubleArrayLogEntry Base_Motors_Voltage("Base/Motors/voltage");        //
    DoubleArrayLogEntry Base_Motors_Current("Base/Motors/current");        //
    Int64ArrayLogEntry Base_Motors_Temperature("Base/Motors/temperature"); //
    DoubleArrayLogEntry Base_Motors_Velocity("Base/Motors/velocity");      //
    DoubleArrayLogEntry Base_Motors_Position("Base/Motors/position");      //

    DoubleLogEntry Base_DriveTo_PID_P("Base/PID/DriveTo/Terms/P");
    DoubleLogEntry Base_DriveTo_PID_I("Base/PID/DriveTo/Terms/I");
    DoubleLogEntry Base_DriveTo_PID_D("Base/PID/DriveTo/Terms/D");

    DoubleLogEntry Base_DriveTo_PID_settleZone("Base/PID/DriveTo/Terms/settleZone");
    DoubleLogEntry Base_DriveTo_PID_timeSettled("Base/PID/DriveTo/Terms/imeSettled");
    DoubleLogEntry Base_DriveTo_PID_timePassed("Base/PID/DriveTo/Terms/timePassed");

    DoubleLogEntry Base_DriveTo_PID_kP("Base/PID/DriveTo/Constants/kP");
    DoubleLogEntry Base_DriveTo_PID_kI("Base/PID/DriveTo/Constants/kI");
    DoubleLogEntry Base_DriveTo_PID_kD("Base/PID/DriveTo/Constants/kD");
    DoubleLogEntry Base_Driveto_PID_ff("Base/PID/DriveTo/Constants/kf");

    DoubleLogEntry Base_DriveTo_PID_target("Base/PID/DriveTo/target");
    DoubleLogEntry Base_DriveTo_PID_feedback("Base/PID/DriveTo/feedback");
    DoubleLogEntry Base_DriveTo_PID_error("Base/PID/DriveTo/error");
    DoubleLogEntry Base_DriveTo_PID_integral("Base/PID/DriveTo/integral");
    DoubleLogEntry Base_DriveTo_PID_derivative("Base/PID/DriveTo/derivative");
    DoubleLogEntry Base_DriveTo_PID_output("Base/PID/DriveTo/output");

    DoubleLogEntry Base_TurnTo_PID_P("Base/PID/TurnTo/Terms/P");
    DoubleLogEntry Base_TurnTo_PID_I("Base/PID/TurnTo/Terms/I");
    DoubleLogEntry Base_TurnTo_PID_D("Base/PID/TurnTo/Terms/D");

    DoubleLogEntry Base_TurnTo_PID_settleZone("Base/PID/TurnTo/Terms/settleZone");
    DoubleLogEntry Base_TurnTo_PID_timeSettled("Base/PID/TurnTo/Terms/imeSettled");
    DoubleLogEntry Base_TurnTo_PID_timePassed("Base/PID/TurnTo/Terms/timePassed");

    DoubleLogEntry Base_TurnTo_PID_kP("Base/PID/TurnTo/Constants/kP");
    DoubleLogEntry Base_TurnTo_PID_kI("Base/PID/TurnTo/Constants/kI");
    DoubleLogEntry Base_TurnTo_PID_kD("Base/PID/TurnTo/Constants/kD");
    DoubleLogEntry Base_TurnTo_PID_ff("Base/PID/TurnTo/Constants/kf");

    DoubleLogEntry Base_TurnTo_PID_target("Base/PID/TurnTo/target");
    DoubleLogEntry Base_TurnTo_PID_feedback("Base/PID/TurnTo/feedback");
    DoubleLogEntry Base_TurnTo_PID_error("Base/PID/TurnTo/error");
    DoubleLogEntry Base_TurnTo_PID_integral("Base/PID/TurnTo/integral");
    DoubleLogEntry Base_TurnTo_PID_derivative("Base/PID/TurnTo/derivative");
    ;
    DoubleLogEntry Base_TurnTo_PID_output("Base/PID/TurnTo/output");

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

    DoubleArrayLogEntry Pose_TrackingPose("Pose/trackingPose");            //
    DoubleArrayLogEntry Pose_TrackingPose_Blue("Pose/trackingPose(blue)"); //
    DoubleArrayLogEntry Pose_CenterPose("Pose/centerPose");                //
    DoubleArrayLogEntry Pose_CenterPose_Blue("Pose/centerPose(blue)");     //
    DoubleArrayLogEntry Pose_GPSPose_L("Pose/GPSPose-L");
    DoubleArrayLogEntry Pose_GPSPose_Blue_L("Pose/GPSPose(blue)-L");
    Int64LogEntry Pose_GPSAccuracy_L("Pose/GPSAccuracy-L");
    DoubleArrayLogEntry Pose_GPSPose_R("Pose/GPSPose-R");
    DoubleArrayLogEntry Pose_GPSPose_Blue_R("Pose/GPSPose(blue)-R");
    Int64LogEntry Pose_GPSAccuracy_R("Pose/GPSAccuracy-R");

    StringLogEntry Auton_Console("Auton/Console");
    DoubleArrayLogEntry Auton_TargetPoint("Auton/targetPoint");            //
    DoubleArrayLogEntry Auton_TargetPoint_Blue("Auton/targetPoint(blue)"); //
    DoubleArrayLogEntry Auton_CurrentPath("Auton/currentPath");
    DoubleArrayLogEntry Auton_CurrentPath_Blue("Auton/currentPath(blue)");

    DoubleArrayLogEntry Vision_RedObjectPos("Vision/Red/Pos");
    DoubleArrayLogEntry Vision_BlueObjectPos("Vision/Blue/Pos");
    DoubleArrayLogEntry Vision_RedObjectDim("Vision/Red/Dim");
    DoubleArrayLogEntry Vision_BlueObjectDim("Vision/Blue/Dim");

    Int64LogEntry Optics_LowerOpticalHue("Optics/Lower/Hue");
    BooleanLogEntry Optics_LowerOpticalDist("Optics/Lower/Dist");
    Int64LogEntry Optics_UpperOpticalHue("Optics/Upper/Hue");
    BooleanLogEntry Optics_UpperOpticalDist("Optics/Upper/Dist");
} // namespace logging
