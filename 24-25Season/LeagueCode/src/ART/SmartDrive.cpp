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
            m_leftTravel = Length(rightTravel.revolutions() * getWheelTravel());

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
            m_rotVel = Angle((m_dir - prevDir) * 50.0);

            m_pos = m_pos + posChange;
            m_centerPos = m_pos + Vec2::dirAndMag(m_dir, m_tracker.m_offset);

            vex::wait(20, vex::msec);
        }
    }

    void SmartDrive::driveFor(Length target, double speed)
    {

        std::stringstream ss;
        ss << "SmartDrive::driveFor(" << target.inches() << "{in}, " << speed << ")";

        logger.logStringEntry(100, timePassed(), ss.str());

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

        logger.logStringEntry(100, timePassed(), ss.str());

        static bool driveForPIDinit = false;
        if (!driveForPIDinit)
        {
            driveForPIDinit = true;
            logger.startDoubleEntry("DriveFor/Target", 101);
            logger.startDoubleEntry("DriveFor/Current", 102);
            logger.startDoubleEntry("DriveFor/Error(in)", 103);
            logger.startDoubleEntry("DriveFor/P", 104);
            logger.startDoubleEntry("DriveFor/I", 105);
            logger.startDoubleEntry("DriveFor/D", 106);
            logger.startDoubleEntry("DriveFor/Out", 107);
        }

        double out = 0;

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        m_driveForPID.reset();
        while (!m_driveForPID.isCompleted())
        {
            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            out = m_driveForPID.calculate(targetRot - pos);

            arcade(out, 0);

            // Brain.Screen.setCursor(5, 1);
            // Brain.Screen.print("p: %f", m_driveForPID.getProportional());
            // Brain.Screen.setCursor(6, 1);
            // Brain.Screen.print("i: %f", m_driveForPID.getIntegral());
            // Brain.Screen.setCursor(7, 1);
            // Brain.Screen.print("d: %f", m_driveForPID.getDerivative());

            // Brain.Screen.setCursor(5, 15);
            // Brain.Screen.print("current: %f", pos.degrees());
            // Brain.Screen.setCursor(6, 15);
            // Brain.Screen.print("error: %f", Length(Angle(targetRot - pos).revolutions() * getWheelTravel()).inches());
            // Brain.Screen.setCursor(7, 15);
            // Brain.Screen.print("out: %f", out);

            logger.logDoubleEntry(101, timePassed(), targetRot);
            logger.logDoubleEntry(102, timePassed(), pos);
            logger.logDoubleEntry(103, timePassed(), Length(Angle(targetRot - pos).revolutions() * getWheelTravel()).inches());
            logger.logDoubleEntry(104, timePassed(), m_driveForPID.getProportional());
            logger.logDoubleEntry(105, timePassed(), m_driveForPID.getIntegral());
            logger.logDoubleEntry(106, timePassed(), m_driveForPID.getDerivative());
            logger.logDoubleEntry(107, timePassed(), out);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
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

        logger.logStringEntry(100, timePassed(), ss.str());

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

        logger.logStringEntry(100, timePassed(), ss.str());

        static bool turnForPIDinit = false;
        if (!turnForPIDinit)
        {
            turnForPIDinit = true;
            logger.startDoubleEntry("TurnFor/Target", 111);
            logger.startDoubleEntry("TurnFor/Current", 112);
            logger.startDoubleEntry("TurnFor/Error", 113);
            logger.startDoubleEntry("TurnFor/P", 114);
            logger.startDoubleEntry("TurnFor/I", 115);
            logger.startDoubleEntry("TurnFor/D", 116);
            logger.startDoubleEntry("TurnFor/Out", 117);
        }

        double out = 0;

        Angle targetAngle = Degrees(m_inert.rotation(vex::degrees) + target.degrees());

        m_turnForPID.reset();
        while (!m_turnForPID.isCompleted())
        {
            Angle error = Degrees(targetAngle.degrees() - m_inert.rotation(vex::degrees));

            out = m_turnForPID.calculate(error);

            arcade(0, out);

            logger.logDoubleEntry(111, timePassed(), targetAngle);
            logger.logDoubleEntry(112, timePassed(), art::Angle(m_inert.rotation(vex::degrees)));
            logger.logDoubleEntry(113, timePassed(), error);
            logger.logDoubleEntry(114, timePassed(), m_turnToPID.getProportional());
            logger.logDoubleEntry(115, timePassed(), m_turnToPID.getIntegral());
            logger.logDoubleEntry(116, timePassed(), m_turnToPID.getDerivative());
            logger.logDoubleEntry(117, timePassed(), out);

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

        logger.logStringEntry(100, timePassed(), ss.str());

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

        logger.logStringEntry(100, timePassed(), ss.str());

        static bool turnToPIDinit = false;
        if (!turnToPIDinit)
        {
            turnToPIDinit = true;
            logger.startDoubleEntry("TurnTo/Target", 121);
            logger.startDoubleEntry("TurnTo/Current", 122);
            logger.startDoubleEntry("TurnTo/Error", 123);
            logger.startDoubleEntry("TurnTo/P", 124);
            logger.startDoubleEntry("TurnTo/I", 125);
            logger.startDoubleEntry("TurnTo/D", 126);
            logger.startDoubleEntry("TurnTo/Out", 127);
        }

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

            logger.logDoubleEntry(121, timePassed(), target);
            logger.logDoubleEntry(122, timePassed(), dirCopy);
            logger.logDoubleEntry(123, timePassed(), error);
            logger.logDoubleEntry(124, timePassed(), m_turnToPID.getProportional());
            logger.logDoubleEntry(125, timePassed(), m_turnToPID.getIntegral());
            logger.logDoubleEntry(126, timePassed(), m_turnToPID.getDerivative());
            logger.logDoubleEntry(127, timePassed(), out);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    bool SmartDrive::turnTowardPID(Angle target, bool reset)
    {
        if (reset)
        {
            m_turnToPID.reset();

            return false;
        }

        // std::stringstream ss;
        // ss << "SmartDrive::turnToward(" << target << ")";

        // logger.logStringEntry(100, timePassed(), ss.str());

        static bool turnTowardPIDinit = false;
        if (!turnTowardPIDinit)
        {
            turnTowardPIDinit = true;
            logger.startDoubleEntry("TurnToward/Target", 121);
            logger.startDoubleEntry("TurnToward/Current", 122);
            logger.startDoubleEntry("TurnToward/Error", 123);
            logger.startDoubleEntry("TurnToward/P", 124);
            logger.startDoubleEntry("TurnToward/I", 125);
            logger.startDoubleEntry("TurnToward/D", 126);
            logger.startDoubleEntry("TurnToward/Out", 127);
        }

        double out = 0;

        Angle dirCopy = m_dir;

        Angle error = shortestTurnPath(art::Angle(target - m_dir)); // once removed shortest path, added back

        out = m_turnToPID.calculate(error);

        dirCopy = m_dir;
        dirCopy.constrain();

        arcade(0, out);

        logger.logDoubleEntry(121, timePassed(), target);
        logger.logDoubleEntry(122, timePassed(), dirCopy);
        logger.logDoubleEntry(123, timePassed(), error);
        logger.logDoubleEntry(124, timePassed(), m_turnToPID.getProportional());
        logger.logDoubleEntry(125, timePassed(), m_turnToPID.getIntegral());
        logger.logDoubleEntry(126, timePassed(), m_turnToPID.getDerivative());
        logger.logDoubleEntry(127, timePassed(), out);

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
