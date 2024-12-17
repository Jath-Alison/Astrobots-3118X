/**
 * @file SmartDrive.cpp
 * @author Jath Alison (Jath.Alison@gmail.com)
 * @brief Source containing the SmartDrive class
 * @version 1.0-beta
 * @date 09-25-2024
 *
 * @copyright Copyright (c) 2024
 *
 * This is the source file defining the SmartDrive
 * class. The class aims to package more complex base controls, making it
 * easier to write autos by providing consistant high-level controls for
 * more complex tasks.
 */

#include "ART/SmartDrive.h"
#include "robotConfig.h"
#include <sstream>
#include "logging.h"

namespace art
{

    SmartDrive::SmartDrive(TankDrive drive, vex::inertial inert) : TankDrive(drive), m_inert(inert)
    {
        m_inert.calibrate();
    }

    SmartDrive &SmartDrive::withWheelSize(Length size)
    {
        m_wheelSize = size;
        return *this;
    }

    SmartDrive &SmartDrive::withGearRatio(double ratio)
    {
        m_gearRatio = ratio;
        return *this;
    }

    SmartDrive &SmartDrive::withHorizontalTracker(vex::rotation rotation, Length wheelSize, double gearRatio)
    {
        m_tracker = HorizontalTracker(rotation, wheelSize, gearRatio);
        return *this;
    }

    SmartDrive &SmartDrive::withHorizontalTracker(vex::rotation rotation, Length wheelSize, double gearRatio, Length wheelOffset)
    {
        m_tracker = HorizontalTracker(rotation, wheelSize, gearRatio, wheelOffset);
        return *this;
    }

    int SmartDrive::track()
    {
        if (m_tracker.m_rotation)
        {
            m_tracker.m_rotation->setPosition(0, vex::deg);
        }
        while (m_inert.isCalibrating())
        {
            vex::wait(5, vex::msec);
        }

        while (true)
        {
            static Angle prevDir;
            if (m_dir != prevDir)
            {
                m_inert.setHeading(m_dir.degrees(), vex::deg);
            }
            m_dir = Degrees(m_inert.heading(vex::degrees));
            prevDir = m_dir;

            Angle leftTravel = getLeftTravel();
            Angle rightTravel = getRightTravel();

            m_leftTravel = Length(leftTravel.revolutions() * getWheelTravel());
            m_rightTravel = Length(rightTravel.revolutions() * getWheelTravel());

            Angle wheelTravel = Angle((leftTravel + rightTravel) / 2.0);
            Length travel = Length(wheelTravel.revolutions() * getWheelTravel());

            // Distance travel = Inches(change*((3.25 * 3.1415)/360.f) / (72.f/48.f));
            Vec2 posChange = Vec2::dirAndMag(m_dir, travel);

            if (m_tracker.m_rotation != nullptr)
            {
                Length hTravel = m_tracker.getTravel();

                Vec2 trackerTravel = Vec2::dirAndMag(m_dir + Degrees(90), hTravel);

                posChange = posChange + trackerTravel;
            }

            m_vel = posChange * (50.0);
            m_rotVel = Angle(m_dir - prevDir) * 50.0;

            m_pos = m_pos + posChange;
            m_centerPos = m_pos + Vec2::dirAndMag(m_dir, m_tracker.m_offset);

            vex::wait(20, vex::msec);
        }
    }

    void SmartDrive::driveFor(Length target, double speed)
    {

        std::stringstream ss;
        ss << "SmartDrive::driveFor(" << target.inches() << "{in}, " << speed << ")";

        logger.logStringEntry(Auton_Console, ss.str());

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        int dir = std::abs(target) / target;

        Angle pos = offset;

        while ((targetRot - pos) * dir > 0)
        {
            pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);

            arcade(speed, 0);

            wait(20, vex::msec);
        }

        arcade(0, 0);
    }
    void SmartDrive::driveForPID(Length target)
    {
        std::stringstream ss;
        ss << "SmartDrive::driveForPID(" << target.inches() << "{in})";

        logger.logStringEntry(Auton_Console, ss.str());

        logger.logDoubleEntry(Base_DriveTo_PID_kP, m_driveForPID.getkp());
        logger.logDoubleEntry(Base_DriveTo_PID_kI, m_driveForPID.getki());
        logger.logDoubleEntry(Base_DriveTo_PID_kD, m_driveForPID.getkd());
        logger.logDoubleEntry(Base_Driveto_PID_ff, m_driveForPID.getff());
        // logger.logDoubleEntry(Base_DriveTo_PID_settleZone, art::Revolutions(art::Inches(1) / (M_PI * art::Inches(2.75) * (36.f/48.f))));

        double out = 0;

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        m_driveForPID.reset();
        while (!m_driveForPID.isCompleted())
        {
            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            out = m_driveForPID.calculate(targetRot - pos);

            arcade(out, 0);

            logger.logDoubleEntry(Base_DriveTo_PID_P, m_driveForPID.getProportional());
            logger.logDoubleEntry(Base_DriveTo_PID_I, m_driveForPID.getIntegral());
            logger.logDoubleEntry(Base_DriveTo_PID_D, m_driveForPID.getDerivative());
            logger.logDoubleEntry(Base_DriveTo_PID_target, targetRot);
            logger.logDoubleEntry(Base_DriveTo_PID_feedback, pos);
            logger.logDoubleEntry(Base_DriveTo_PID_error, targetRot - pos);
            logger.logDoubleEntry(Base_DriveTo_PID_integral, m_driveForPID.getIntegral() / m_driveForPID.getki());
            logger.logDoubleEntry(Base_DriveTo_PID_derivative, m_driveForPID.getDerivative() / m_driveForPID.getkd());
            logger.logDoubleEntry(Base_DriveTo_PID_output, out);
            // logger.logDoubleEntry(Base_DriveTo_PID_timePassed, m_driveForPID.timePassed());
            // logger.logDoubleEntry(Base_DriveTo_PID_timeSettled, m_driveForPID.settledTimePassed());

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    bool SmartDrive::driveTowardPID(Length target, bool reset)
    {
        if (reset)
        {
            std::stringstream ss;
            ss << "SmartDrive::DriveToward(" << target << ")";

            logger.logStringEntry(Auton_Console, ss.str());

            m_driveForPID.reset();

            return false;
        }

        double out = 0;

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        m_driveForPID.reset();

        Angle dirCopy = m_dir;

        Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        out = m_driveForPID.calculate(targetRot - pos);

        smartDrive.m_cmdY = out;
        smartDrive.update();

        return m_turnToPID.settledTimePassed() > 1.f;
    }
    SmartDrive &SmartDrive::withDriveForPID(PID pid)
    {
        m_driveForPID = pid;
        return *this;
    }

    void SmartDrive::turnFor(Angle target, double speed)
    {

        std::stringstream ss;
        ss << "SmartDrive::turnFor(" << target << ", " << speed << ")";

        logger.logStringEntry(Auton_Console, ss.str());

        Angle targetAngle = Degrees(target.degrees() + m_inert.rotation(vex::degrees));

        int dir = double(std::abs(target) / target);

        while (Degrees(targetAngle.degrees() - m_inert.rotation(vex::degrees)) * dir > 0)
        {
            arcade(0, speed);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::turnForPID(Angle target)
    {

        std::stringstream ss;
        ss << "SmartDrive::turnForPID(" << target << ")";

        logger.logStringEntry(Auton_Console, ss.str());

        // static bool turnForPIDinit = false;
        // if (!turnForPIDinit)
        // {
        //     turnForPIDinit = true;
        //     logger.startDoubleEntry("TurnFor/Target", 111);
        //     logger.startDoubleEntry("TurnFor/Current", 112);
        //     logger.startDoubleEntry("TurnFor/Error", 113);
        //     logger.startDoubleEntry("TurnFor/P", 114);
        //     logger.startDoubleEntry("TurnFor/I", 115);
        //     logger.startDoubleEntry("TurnFor/D", 116);
        //     logger.startDoubleEntry("TurnFor/Out", 117);
        // }

        double out = 0;

        Angle targetAngle = Degrees(m_inert.rotation(vex::degrees) + target.degrees());

        m_turnForPID.reset();
        while (!m_turnForPID.isCompleted())
        {
            Angle error = Degrees(targetAngle.degrees() - m_inert.rotation(vex::degrees));

            out = m_turnForPID.calculate(error);

            arcade(0, out);

            // logger.logDoubleEntry(111, timePassed(), targetAngle);
            // logger.logDoubleEntry(112, timePassed(), art::Angle(m_inert.rotation(vex::degrees)));
            // logger.logDoubleEntry(113, timePassed(), error);
            // logger.logDoubleEntry(114, timePassed(), m_turnToPID.getProportional());
            // logger.logDoubleEntry(115, timePassed(), m_turnToPID.getIntegral());
            // logger.logDoubleEntry(116, timePassed(), m_turnToPID.getDerivative());
            // logger.logDoubleEntry(117, timePassed(), out);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    SmartDrive &SmartDrive::withTurnForPID(PID pid)
    {
        m_turnForPID = pid;
        return *this;
    }

    void SmartDrive::turnTo(Angle target, double speed)
    {

        std::stringstream ss;
        ss << "SmartDrive::turnTo(" << target << ", " << speed << ")";

        logger.logStringEntry(Auton_Console, ss.str());

        Angle error = shortestTurnPath(Degrees(target.degrees() - m_inert.heading(vex::degrees)));
        int errorSign = std::abs(error) / error;

        while (!(std::abs(error.degrees()) < 10) || errorSign == std::abs(error) / error)
        {
            error = shortestTurnPath(Degrees(target.degrees() - m_inert.heading(vex::degrees)));

            arcade(0, speed);

            if ((std::abs(error.degrees()) < 5))
            {
                arcade(0, 0, 0);
                return;
            }

            errorSign = std::abs(error) / error;
            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::turnToPID(Angle target)
    {
        std::stringstream ss;
        ss << "SmartDrive::turnTo(" << target << ")";

        logger.logStringEntry(Auton_Console, ss.str());

        logger.logDoubleEntry(Base_TurnTo_PID_kP, m_turnToPID.getkp());
        logger.logDoubleEntry(Base_TurnTo_PID_kI, m_turnToPID.getki());
        logger.logDoubleEntry(Base_TurnTo_PID_kD, m_turnToPID.getkd());
        logger.logDoubleEntry(Base_TurnTo_PID_ff, m_turnToPID.getff());
        logger.logDoubleEntry(Base_TurnTo_PID_settleZone, art::Degrees(3));

        double out = 0;

        Angle dirCopy = m_dir;

        m_turnToPID.reset();
        while (!m_turnToPID.isCompleted())
        {
            Angle error = shortestTurnPath(art::Angle(target - m_dir)); // once removed shortest path, added back

            out = m_turnToPID.calculate(error);

            dirCopy = m_dir;
            dirCopy.constrain();

            arcade(0, out);

            logger.logDoubleEntry(Base_TurnTo_PID_P, m_turnForPID.getProportional());
            logger.logDoubleEntry(Base_TurnTo_PID_I, m_turnForPID.getIntegral());
            logger.logDoubleEntry(Base_TurnTo_PID_D, m_turnForPID.getDerivative());
            logger.logDoubleEntry(Base_TurnTo_PID_target, target);
            logger.logDoubleEntry(Base_TurnTo_PID_feedback, m_dir);
            logger.logDoubleEntry(Base_TurnTo_PID_error, error);
            logger.logDoubleEntry(Base_TurnTo_PID_integral, m_turnForPID.getIntegral() / m_turnForPID.getki());
            logger.logDoubleEntry(Base_TurnTo_PID_derivative, m_turnForPID.getDerivative() / m_turnForPID.getkd());
            logger.logDoubleEntry(Base_TurnTo_PID_output, out);
            // logger.logDoubleEntry(Base_TurnTo_PID_timePassed, m_turnToPID.timePassed());
            // logger.logDoubleEntry(Base_TurnTo_PID_timeSettled, m_turnToPID.settledTimePassed());

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    bool SmartDrive::turnTowardPID(Angle target, bool reset)
    {
        if (reset)
        {
            logger.logDoubleEntry(Base_TurnTo_PID_kP, m_turnToPID.getkp());
            logger.logDoubleEntry(Base_TurnTo_PID_kI, m_turnToPID.getki());
            logger.logDoubleEntry(Base_TurnTo_PID_kD, m_turnToPID.getkd());
            logger.logDoubleEntry(Base_TurnTo_PID_ff, m_turnToPID.getff());
            logger.logDoubleEntry(Base_TurnTo_PID_settleZone, art::Degrees(3));

            std::stringstream ss;
            ss << "SmartDrive::turnToward(" << target << ")";

            logger.logStringEntry(Auton_Console, ss.str());

            m_turnToPID.reset();

            return false;
        }

        double out = 0;

        Angle dirCopy = m_dir;

        Angle error = shortestTurnPath(art::Angle(target - m_dir)); // once removed shortest path, added back

        out = m_turnToPID.calculate(error);

        dirCopy = m_dir;
        dirCopy.constrain();

        arcade(0, out);

        logger.logDoubleEntry(Base_TurnTo_PID_P, m_turnForPID.getProportional());
        logger.logDoubleEntry(Base_TurnTo_PID_I, m_turnForPID.getIntegral());
        logger.logDoubleEntry(Base_TurnTo_PID_D, m_turnForPID.getDerivative());
        logger.logDoubleEntry(Base_TurnTo_PID_target, target);
        logger.logDoubleEntry(Base_TurnTo_PID_feedback, m_dir);
        logger.logDoubleEntry(Base_TurnTo_PID_error, error);
        logger.logDoubleEntry(Base_TurnTo_PID_integral, m_turnForPID.getIntegral() / m_turnForPID.getki());
        logger.logDoubleEntry(Base_TurnTo_PID_derivative, m_turnForPID.getDerivative() / m_turnForPID.getkd());
        logger.logDoubleEntry(Base_TurnTo_PID_output, out);
        // logger.logDoubleEntry(Base_TurnTo_PID_timePassed, m_turnToPID.timePasssed());
        // logger.logDoubleEntry(Base_TurnTo_PID_timeSettled, m_turnToPID.settledTimePsassed());

        return m_turnToPID.settledTimePassed() > 1.f;
    }

    SmartDrive &SmartDrive::withTurnToPID(PID pid)
    {
        m_turnToPID = pid;
        return *this;
    }

    Length SmartDrive::getWheelTravel()
    {
        return Length(M_PI * m_wheelSize * m_gearRatio);
    }

    SmartDrive::HorizontalTracker::HorizontalTracker() {}
    SmartDrive::HorizontalTracker::HorizontalTracker(vex::rotation rotation, Length wheelSize, double gearRatio) : m_wheelSize(wheelSize), m_gearRatio(gearRatio)
    {
        m_rotation = std::make_shared<vex::rotation>(rotation);
    }
    SmartDrive::HorizontalTracker::HorizontalTracker(vex::rotation rotation, Length wheelSize, double gearRatio, Length wheelOffset) : m_wheelSize(wheelSize), m_gearRatio(gearRatio), m_offset(wheelOffset)
    {
        m_rotation = std::make_shared<vex::rotation>(rotation);
    }
    Length SmartDrive::HorizontalTracker::getTravel()
    {
        Angle currentAngle = Degrees(m_rotation->position(vex::degrees));

        m_travelAngle = Angle(currentAngle - m_lastAngle);
        m_lastAngle = currentAngle;

        m_travelDistance = Length(m_travelAngle * (m_wheelSize / 2.0) * m_gearRatio);

        return m_travelDistance;
    }

    Angle SmartDrive::getLeftTravel()
    {
        Angle currentAngle = Degrees(m_left.position(vex::degrees));

        Angle tempAngle = Angle(currentAngle - m_LastLeftPos);
        m_LastLeftPos = currentAngle;

        return tempAngle;
    }
    Angle SmartDrive::getRightTravel()
    {
        Angle currentAngle = Degrees(m_right.position(vex::degrees));

        Angle tempAngle = Angle(currentAngle - m_LastRightPos);
        m_LastRightPos = currentAngle;

        return tempAngle;
    }

} // namespace art
