#include "Threads.h"
#include "SubAutons.h"

void displayLoopFunction()
{
    logger.logStringEntry(console, "Display Loop Task Started");

    Brain.Screen.setPenWidth(3);

    while (1)
    {
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("X: %f", art::Length(smartDrive.m_pos.x).inches());
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Y: %f", art::Length(smartDrive.m_pos.y).inches());
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Rot: %f", art::Angle(smartDrive.m_dir).degrees());
        Brain.Screen.setCursor(4, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Arm_Angle: %f", armRot.angle(vex::degrees));
        Brain.Screen.setCursor(5, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("ArmTarget: %f", armTarget.degrees());
        Brain.Screen.setCursor(6, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Intake Temp: %u \370 ", int(intake.temperature(vex::celsius)));

        Brain.Screen.setFillColor(vex::color::blue);
        Brain.Screen.drawRectangle(480 - 5 - 80, 5, 80, 120 - 10);
        Brain.Screen.setFillColor(vex::color::red);
        Brain.Screen.drawRectangle(480 - 5 - 80, 125, 80, 120 - 10);
        Brain.Screen.setFillColor(vex::color::black);

        Brain.Screen.setCursor(8, 1);
        Brain.Screen.clearLine();
        if (isBlue)
        {
            Brain.Screen.print("Blue Auton Selected");
        }
        else
        {
            Brain.Screen.print("Red Auton Selected");
        }

        if (Brain.Screen.PRESSED)
        {
            if (Brain.Screen.xPosition() > 480 - 5 - 80 && Brain.Screen.xPosition() < 480 - 5 - 80 + 120 - 10 && Brain.Screen.yPosition() > 5 && Brain.Screen.yPosition() < 5 + 120 - 10)
            {
                isBlue = true;

                // Only for Stake First autos
                // smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2), art::Tiles(-1));
                // smartDrive.m_dir = art::Degrees(90);
                resetPositionFromGPS();
            }
            if (Brain.Screen.xPosition() > 480 - 5 - 80 && Brain.Screen.xPosition() < 480 - 5 - 80 + 120 - 10 && Brain.Screen.yPosition() > 120 + 5 && Brain.Screen.yPosition() < 5 + 120 - 10 + 120)
            {
                isBlue = false;

                // Only for Stake First autos
                // smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2), art::Tiles(-1));
                // smartDrive.m_dir = art::Degrees(-90);
                resetPositionFromGPS();
            }
            // isBlue = !isBlue;
        }

        vex::this_thread::sleep_for(20);
    }
}

auto last_logged = std::chrono::high_resolution_clock::now();
auto current_time_logLoop = std::chrono::high_resolution_clock::now();

uint64_t logTimePassed()
{
    current_time_logLoop = std::chrono::high_resolution_clock::now();
    return uint64_t(std::chrono::duration_cast<std::chrono::microseconds>(current_time_logLoop - last_logged).count());
}

void logLoopFunction()
{

    logger.logStringEntry(console, "Log Loop Started");

    logger.clearFile("TestLog.wpilog");
    logger.logStringEntry(console, "LogFile Cleared");

    std::vector<vex::motor *> baseMotors = {
        &leftMotorA, &leftMotorB, &leftMotorC,
        &rightMotorA, &rightMotorB, &rightMotorC};

    FrontVision.modelDetection(true);

    while (1)
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
            smartDrive.m_cmdX, smartDrive.m_cmdY, smartDrive.m_cmdRot};
        logger.logDoubleArrayEntry(Base_XYR_Cmd, baseXYRCmd);

        std::vector<double> baseXYRVel = {
            art::Length(smartDrive.m_vel.x).meters(), art::Length(smartDrive.m_vel.y).meters(), smartDrive.m_rotVel};
        logger.logDoubleArrayEntry(Base_XYR_Vel, baseXYRVel);

        std::vector<double> baseLRCmd = {
            smartDrive.m_left.get(), smartDrive.m_right.get()};
        logger.logDoubleArrayEntry(Base_LeftRight_Cmd, baseLRCmd);

        std::vector<double> baseLRVel = {
            smartDrive.m_leftTravel.meters(), smartDrive.m_rightTravel.meters()};
        logger.logDoubleArrayEntry(Base_LeftRight_Vel, baseLRVel);

        std::vector<double> baseVelSwerveState = {
            smartDrive.m_dir - smartDrive.m_vel.direction(), art::Length(smartDrive.m_vel.magnitude()).meters(),
            smartDrive.m_dir - smartDrive.m_vel.direction(), art::Length(smartDrive.m_vel.magnitude()).meters(),
            smartDrive.m_dir - smartDrive.m_vel.direction(), art::Length(smartDrive.m_vel.magnitude()).meters(),
            smartDrive.m_dir - smartDrive.m_vel.direction(), art::Length(smartDrive.m_vel.magnitude()).meters(),
        };
        logger.logDoubleArrayEntry(Base_VelSwerveState, baseVelSwerveState);

        std::vector<double> baseLRSwerveState = {
            0, smartDrive.m_leftTravel.meters() * 50,
            0, smartDrive.m_rightTravel.meters() * 50,
            0, smartDrive.m_leftTravel.meters() * 50,
            0, smartDrive.m_rightTravel.meters() * 50,
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

        logger.logDoubleEntry(Intake_Cmd, intake.get());
        logger.logDoubleEntry(Intake_Voltage, intake.voltage());
        logger.logDoubleEntry(Intake_Current, intake.current());
        logger.logDoubleEntry(Intake_Velocity, intake.velocity(vex::velocityUnits::pct));
        logger.logDoubleEntry(Intake_Temperature, intake.temperature(vex::celsius));
        logger.logDoubleEntry(Intake_Position, intake.position(vex::rotationUnits::deg));

        logger.logDoubleEntry(Arm_Cmd, arm.get());
        logger.logDoubleEntry(Arm_Voltage, arm.voltage());
        logger.logDoubleEntry(Arm_Current, arm.current());
        logger.logDoubleEntry(Arm_Velocity, arm.velocity(vex::velocityUnits::pct));
        logger.logDoubleEntry(Arm_Temperature, arm.temperature(vex::celsius));
        logger.logDoubleEntry(Arm_Position, arm.position(vex::rotationUnits::deg));
        logger.logDoubleEntry(Arm_RotAngle, armRot.angle());
        logger.logDoubleEntry(Arm_TargetAngle, armTarget);

        logger.logDoubleArrayEntry(Base_Motors_Voltage, baseMotorsVoltage);
        logger.logDoubleArrayEntry(Base_Motors_Current, baseMotorsCurrent);
        logger.logInt64ArrayEntry(Base_Motors_Temperature, baseMotorsTemperature);
        logger.logDoubleArrayEntry(Base_Motors_Velocity, baseMotorsVelocity);
        logger.logDoubleArrayEntry(Base_Motors_Position, baseMotorsPosition);

        std::vector<double> robotPose = {
            art::Length(smartDrive.m_pos.x).meters(),
            art::Length(smartDrive.m_pos.y).meters(),
            art::Angle(smartDrive.m_dir).degrees()};
        logger.logDoubleArrayEntry(Pose_TrackingPose, robotPose);
        logger.logDoubleArrayEntry(Base_XYR_Pos, robotPose);

        std::vector<double> robotPoseBlue = {
            1.8 + art::Length(smartDrive.m_pos.x).meters(),
            1.8 + art::Length(smartDrive.m_pos.y).meters(),
            -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
        };
        logger.logDoubleArrayEntry(Pose_TrackingPose_Blue, robotPoseBlue);
        logger.logDoubleArrayEntry(Base_XYR_Pos_Blue, robotPoseBlue);

        std::vector<double> robotCentersPose = {
            art::Length(smartDrive.m_centerPos.x).meters(),
            art::Length(smartDrive.m_centerPos.y).meters(),
            art::Angle(smartDrive.m_dir).degrees()};
        logger.logDoubleArrayEntry(Pose_CenterPose, robotCentersPose);

        std::vector<double> robotCentersPoseBlue = {
            1.8 + art::Length(smartDrive.m_centerPos.x).meters(),
            1.8 + art::Length(smartDrive.m_centerPos.y).meters(),
            -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
        };
        logger.logDoubleArrayEntry(Pose_CenterPose_Blue, robotCentersPoseBlue);

        std::vector<double> robotGPSPose = {
            art::Inches(gpsSensor.xPosition(vex::inches)).meters(),
            art::Inches(gpsSensor.yPosition(vex::inches)).meters(),
            art::Degrees(gpsSensor.heading(vex::degrees)).degrees()};
        logger.logDoubleArrayEntry(Pose_GPSPose, robotGPSPose);

        std::vector<double> robotGPSPoseBlue = {
            1.8 + art::Inches(gpsSensor.xPosition(vex::inches)).meters(),
            1.8 + art::Inches(gpsSensor.yPosition(vex::inches)).meters(),
            -(art::Degrees(gpsSensor.heading(vex::degrees)) - art::Degrees(90)) // converted to FRC scheme
        };
        logger.logDoubleArrayEntry(Pose_GPSPose_Blue, robotGPSPoseBlue);
        logger.logInt64Entry(Pose_GPSAccuracy, gpsSensor.quality());

        std::vector<double> targetPose = {
            art::Length(target.x).meters(),
            art::Length(target.y).meters(),
            art::Angle(smartDrive.m_dir).degrees() // converted to FRC scheme
        };
        logger.logDoubleArrayEntry(Auton_TargetPoint, targetPose);

        std::vector<double> targetPoseBlue = {
            1.8 + art::Length(target.x).meters(),
            1.8 + art::Length(target.y).meters(),
            -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
        };
        logger.logDoubleArrayEntry(Auton_TargetPoint_Blue, targetPoseBlue);

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

        if (logger.getDataSize() > 10000)
        {
            last_logged = std::chrono::high_resolution_clock::now();
            logger.writeToFile("TestLog.wpilog");
        }
        logger.logInt64Entry(Logger_Capacity, logger.getCapacity());
        logger.logInt64Entry(Logger_Size, logger.getDataSize());
        logger.logDoubleEntry(Logger_TimeSinceLastLogged, logTimePassed());

        FrontVision.takeSnapshot(FrontVision.ALL_AIOBJS);

        std::vector<double> blueObjectPos;
        std::vector<double> blueObjectDim;
        for (size_t i = 0; i < FrontVision.objects.getLength(); i++)
        {
            blueObjectPos.push_back(FrontVision.objects[i].originX);
            blueObjectPos.push_back(FrontVision.objects[i].originY);

            blueObjectPos.push_back(FrontVision.objects[i].width);
            blueObjectPos.push_back(FrontVision.objects[i].height);
        }
        logger.logDoubleArrayEntry(Vision_BlueObjectPos,blueObjectPos);
        logger.logDoubleArrayEntry(Vision_BlueObjectDim,blueObjectDim);

        vex::this_thread::sleep_for(20);
    }
}