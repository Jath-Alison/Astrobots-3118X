#include "Logging/Logging.h"
#include "RobotConfig.h"

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

    auto last_logged = std::chrono::high_resolution_clock::now();
    auto current_time_logLoop = std::chrono::high_resolution_clock::now();

    uint64_t logTimePassed()
    {
        current_time_logLoop = std::chrono::high_resolution_clock::now();
        return uint64_t(std::chrono::duration_cast<std::chrono::microseconds>(current_time_logLoop - last_logged).count());
    }

    int logLoop()
    {
        logger.clearFile("ChampsCodelog.wpilog");

        logger.logStringEntry(console, "Log Loop Started");

        logger.clearFile("TestLog.wpilog");
        logger.logStringEntry(console, "LogFile Cleared");

        std::vector<vex::motor *> baseMotors = {
            &leftMotorA, &leftMotorB, &leftMotorC,
            &rightMotorA, &rightMotorB, &rightMotorC};

        while (true)
        {
            std::vector<int64_t> axesStates = {
                Controller1.Axis1.position(),
                Controller1.Axis2.position(),
                Controller1.Axis3.position(),
                Controller1.Axis4.position()};
            std::vector<bool> buttonStates = {
                Controller1.ButtonUp.pressing(),
                Controller1.ButtonRight.pressing(),
                Controller1.ButtonDown.pressing(),
                Controller1.ButtonLeft.pressing(),
                Controller1.ButtonX.pressing(),
                Controller1.ButtonA.pressing(),
                Controller1.ButtonB.pressing(),
                Controller1.ButtonY.pressing(),
                Controller1.ButtonL1.pressing(),
                Controller1.ButtonL2.pressing(),
                Controller1.ButtonR1.pressing(),
                Controller1.ButtonR2.pressing(),
            };
            std::vector<int64_t> povStates = {
                int64_t(art::Vec2::XandY(Controller1.Axis1.position(), Controller1.Axis2.position()).direction()),
                int64_t(art::Vec2::XandY(Controller1.Axis4.position(), Controller1.Axis3.position()).direction()),
            };

            logger.logInt64ArrayEntry(Controller1_Axes, axesStates);
            logger.logBooleanArrayEntry(Controller1_Buttons, buttonStates);
            logger.logInt64ArrayEntry(Controller1_Povs, povStates);

            std::vector<double> baseXYRCmd = {
                asyncDrive.m_cmdX, asyncDrive.m_cmdY, asyncDrive.m_cmdRot};
            logger.logDoubleArrayEntry(Base_XYR_Cmd, baseXYRCmd);

            std::vector<double> baseXYRVel = {
                art::Length(asyncDrive.m_vel.x).meters(), art::Length(asyncDrive.m_vel.y).meters(), asyncDrive.m_rotVel};
            logger.logDoubleArrayEntry(Base_XYR_Vel, baseXYRVel);

            std::vector<double> baseLRCmd = {
                asyncDrive.m_left.get(), asyncDrive.m_right.get()};
            logger.logDoubleArrayEntry(Base_LeftRight_Cmd, baseLRCmd);

            std::vector<double> baseLRVel = {
                asyncDrive.m_leftTravel.meters(), asyncDrive.m_rightTravel.meters()};
            logger.logDoubleArrayEntry(Base_LeftRight_Vel, baseLRVel);

            std::vector<double> baseVelSwerveState = {
                asyncDrive.m_dir - asyncDrive.m_vel.direction(),
                art::Length(asyncDrive.m_vel.magnitude()).meters(),
                asyncDrive.m_dir - asyncDrive.m_vel.direction(),
                art::Length(asyncDrive.m_vel.magnitude()).meters(),
                asyncDrive.m_dir - asyncDrive.m_vel.direction(),
                art::Length(asyncDrive.m_vel.magnitude()).meters(),
                asyncDrive.m_dir - asyncDrive.m_vel.direction(),
                art::Length(asyncDrive.m_vel.magnitude()).meters(),
            };
            logger.logDoubleArrayEntry(Base_VelSwerveState, baseVelSwerveState);

            std::vector<double> baseLRSwerveState = {
                0,
                asyncDrive.m_leftTravel.meters() * 50,
                0,
                asyncDrive.m_rightTravel.meters() * 50,
                0,
                asyncDrive.m_leftTravel.meters() * 50,
                0,
                asyncDrive.m_rightTravel.meters() * 50,
            };
            logger.logDoubleArrayEntry(Base_LR_SwerveState, baseLRSwerveState);

            std::vector<double> baseMotorsVoltage{};
            std::vector<double> baseMotorsCurrent{};
            std::vector<int64_t> baseMotorsTemperature{};
            std::vector<double> baseMotorsVelocity{};
            std::vector<double> baseMotorsPosition{};
            for (auto motor : baseMotors)
            {
                baseMotorsVoltage.push_back(motor->voltage());
                baseMotorsCurrent.push_back(motor->current());
                baseMotorsTemperature.push_back(motor->temperature(vex::celsius));
                baseMotorsVelocity.push_back(motor->velocity(vex::velocityUnits::pct));
                baseMotorsPosition.push_back(motor->position(vex::rotationUnits::deg));
            }

            logger.logDoubleEntry(Intake_Cmd, intake.getMotor().get());
            logger.logDoubleEntry(Intake_Voltage, intake.getMotor().voltage());
            logger.logDoubleEntry(Intake_Current, intake.getMotor().current());
            logger.logDoubleEntry(Intake_Velocity, intake.getMotor().velocity(vex::velocityUnits::pct));
            logger.logDoubleEntry(Intake_Temperature, intake.getMotor().temperature(vex::celsius));
            logger.logDoubleEntry(Intake_Position, intake.getMotor().position(vex::rotationUnits::deg));

            logger.logDoubleEntry(Arm_Cmd, arm.getMotor().get());
            logger.logDoubleEntry(Arm_Voltage, arm.getMotor().voltage());
            logger.logDoubleEntry(Arm_Current, arm.getMotor().current());
            logger.logDoubleEntry(Arm_Velocity, arm.getMotor().velocity(vex::velocityUnits::pct));
            logger.logDoubleEntry(Arm_Temperature, arm.getMotor().temperature(vex::celsius));
            logger.logDoubleEntry(Arm_Position, arm.getMotor().position(vex::rotationUnits::deg));
            logger.logDoubleEntry(Arm_RotAngle, arm.getRotation().angle());
            logger.logDoubleEntry(Arm_TargetAngle, arm.getPosCmd());

            logger.logDoubleArrayEntry(Base_Motors_Voltage, baseMotorsVoltage);
            logger.logDoubleArrayEntry(Base_Motors_Current, baseMotorsCurrent);
            logger.logInt64ArrayEntry(Base_Motors_Temperature, baseMotorsTemperature);
            logger.logDoubleArrayEntry(Base_Motors_Velocity, baseMotorsVelocity);
            logger.logDoubleArrayEntry(Base_Motors_Position, baseMotorsPosition);

            std::vector<double> robotPose = {
                art::Length(asyncDrive.m_pos.x).meters(),
                art::Length(asyncDrive.m_pos.y).meters(),
                art::Angle(asyncDrive.m_dir).degrees()};
            logger.logDoubleArrayEntry(Pose_TrackingPose, robotPose);
            logger.logDoubleArrayEntry(Base_XYR_Pos, robotPose);

            std::vector<double> robotPoseBlue = {
                1.8 + art::Length(asyncDrive.m_pos.x).meters(),
                1.8 + art::Length(asyncDrive.m_pos.y).meters(),
                -(asyncDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
            };
            logger.logDoubleArrayEntry(Pose_TrackingPose_Blue, robotPoseBlue);
            logger.logDoubleArrayEntry(Base_XYR_Pos_Blue, robotPoseBlue);

            std::vector<double> robotCentersPose = {
                art::Length(asyncDrive.m_centerPos.x).meters(),
                art::Length(asyncDrive.m_centerPos.y).meters(),
                art::Angle(asyncDrive.m_dir).degrees()};
            logger.logDoubleArrayEntry(Pose_CenterPose, robotCentersPose);

            std::vector<double> robotCentersPoseBlue = {
                1.8 + art::Length(asyncDrive.m_centerPos.x).meters(),
                1.8 + art::Length(asyncDrive.m_centerPos.y).meters(),
                -(asyncDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
            };
            logger.logDoubleArrayEntry(Pose_CenterPose_Blue, robotCentersPoseBlue);

            std::vector<double> robotGPSPose_L = {
                art::Inches(gpsSensorL.xPosition(vex::inches)).meters(),
                art::Inches(gpsSensorL.yPosition(vex::inches)).meters(),
                art::Degrees(gpsSensorL.heading(vex::degrees)).degrees()};
            logger.logDoubleArrayEntry(Pose_GPSPose_L, robotGPSPose_L);

            std::vector<double> robotGPSPoseBlue_L = {
                1.8 + art::Inches(gpsSensorL.xPosition(vex::inches)).meters(),
                1.8 + art::Inches(gpsSensorL.yPosition(vex::inches)).meters(),
                -(art::Degrees(gpsSensorL.heading(vex::degrees)) - art::Degrees(90)) // converted to FRC scheme
            };
            logger.logDoubleArrayEntry(Pose_GPSPose_Blue_L, robotGPSPoseBlue_L);
            logger.logInt64Entry(Pose_GPSAccuracy_L, gpsSensorL.quality());

            std::vector<double> robotGPSPose_R = {
                art::Inches(gpsSensorR.xPosition(vex::inches)).meters(),
                art::Inches(gpsSensorR.yPosition(vex::inches)).meters(),
                art::Degrees(gpsSensorR.heading(vex::degrees)).degrees()};
            logger.logDoubleArrayEntry(Pose_GPSPose_R, robotGPSPose_R);

            std::vector<double> robotGPSPoseBlue_R = {
                1.8 + art::Inches(gpsSensorR.xPosition(vex::inches)).meters(),
                1.8 + art::Inches(gpsSensorR.yPosition(vex::inches)).meters(),
                -(art::Degrees(gpsSensorR.heading(vex::degrees)) - art::Degrees(90)) // converted to FRC scheme
            };
            logger.logDoubleArrayEntry(Pose_GPSPose_Blue_R, robotGPSPoseBlue_R);
            logger.logInt64Entry(Pose_GPSAccuracy_R, gpsSensorR.quality());

            // std::vector<double> targetPose = {
            //     art::Length(target.x).meters(),
            //     art::Length(target.y).meters(),
            //     art::Angle(asyncDrive.m_dir).degrees() // converted to FRC scheme
            // };
            // logger.logDoubleArrayEntry(Auton_TargetPoint, targetPose);

            // std::vector<double> targetPoseBlue = {
            //     1.8 + art::Length(target.x).meters(),
            //     1.8 + art::Length(target.y).meters(),
            //     -(asyncDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
            // };
            // logger.logDoubleArrayEntry(Auton_TargetPoint_Blue, targetPoseBlue);

            if (Competition.AUTONOMOUS)
            {
                logger.logStringEntry(competitionState, "Auton Started");
            }
            if (Competition.DRIVER_CONTROL)
            {
                logger.logStringEntry(competitionState, "Driver Control Started");
            }
            if (Competition.DISABLED)
            {
                logger.logStringEntry(competitionState, "Robot Disabled");
            }

            if (logger.getDataSize() > 5000)
            {
                last_logged = std::chrono::high_resolution_clock::now();
                logger.writeToFile("ChampsCodeLog.wpilog");
            }
            logger.logInt64Entry(Logger_Capacity, logger.getCapacity());
            logger.logInt64Entry(Logger_Size, logger.getDataSize());
            logger.logDoubleEntry(Logger_TimeSinceLastLogged, logTimePassed());

            vex::wait(20, vex::msec);
        }

        return 0;
    }
    vex::thread logThread;

} // namespace logging