#include "Jath\Drives\SmartDrive.h"
#include "Jath\PID.h"
#include <cmath>

namespace Jath
{

    SmartDrive::HorizontalTracker::HorizontalTracker() : m_wheelSize(0), m_gearRatio(0) {}
    SmartDrive::HorizontalTracker::HorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio) : m_wheelSize(wheelSize), m_gearRatio(gearRatio)
    {
        m_rotation = std::make_shared<vex::rotation>(rotation);
    }

    Distance SmartDrive::HorizontalTracker::getTravel()
    {
        Angle currentAngle = Degrees(m_rotation->position(vex::degrees));

        m_travelAngle = Angle(currentAngle - m_lastAngle);
        m_lastAngle = currentAngle;

        m_travelDistance = Distance(m_travelAngle * (m_wheelSize / 2.0) * m_gearRatio);

        return m_travelDistance;
    }

    SmartDrive::SmartDrive(TankDrive drive, vex::inertial inert) : TankDrive(drive), m_inert(inert)
    {
        m_inert.calibrate();
    }

    SmartDrive &SmartDrive::withWheelSize(Distance size)
    {
        m_wheelSize = size;
        return *this;
    }

    SmartDrive &SmartDrive::withGearRatio(double ratio)
    {
        m_gearRatio = ratio;
        return *this;
    }

    SmartDrive &SmartDrive::withHorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio)
    {
        m_tracker = HorizontalTracker(rotation, wheelSize, gearRatio);
        return *this;
    }

    int SmartDrive::track()
    {
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

            Angle wheelTravel = Angle((m_left.travel() + m_right.travel()) / 2.0);
            Distance travel = Distance(wheelTravel.revolutions() * getWheelTravel());

            // Distance travel = Inches(change*((3.25 * 3.1415)/360.f) / (72.f/48.f));
            Vec2 posChange = dirAndMag(m_dir, travel);

            if (m_tracker.m_rotation != nullptr)
            {
                Distance hTravel = m_tracker.getTravel();

                posChange = posChange + dirAndMag(m_dir + Degrees(90), hTravel);
            }

            m_pos = m_pos + posChange;

            vex::wait(20, vex::msec);
        }
    }

    void SmartDrive::driveTo(Distance target)
    {
        Jath::PID pid = Jath::PID()
                            .withConstants(25 / Jath::Inches(1), 0.0, 2)
                            .withIntegralZone(Jath::Inches(3))
                            .withTimeout(50)
                            .withSettleZone(Jath::Inches(0.5))
                            .withSettleTimeout(0.5);

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        pid.reset();
        while (!pid.isCompleted())
        {
            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            double out = pid.calculate(targetRot - pos);

            // std::cout << "targetRot :" << Jath::Distance(targetRot.revolutions() * getWheelTravel()).inches() << "\n"
            //           << "\tpos :" << Jath::Distance(pos.revolutions() * getWheelTravel()).inches() << "\n"
            //           << "\tout: " << out << "\n";

            arcade(0, out, 0);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    
    void SmartDrive::driveToTuned(Angle target, Distance settleRange, double timeout, double totalTimeout){
        Jath::PID pid = Jath::PID()
                            .withConstants(25 / Jath::Inches(1), 0.0, 2)
                            .withIntegralZone(Jath::Inches(3))
                            .withTimeout(totalTimeout)
                            .withSettleZone(settleRange)
                            .withSettleTimeout(timeout);

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        pid.reset();
        while (!pid.isCompleted())
        {
            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            double out = pid.calculate(targetRot - pos);

            // std::cout << "targetRot :" << Jath::Distance(targetRot.revolutions() * getWheelTravel()).inches() << "\n"
            //           << "\tpos :" << Jath::Distance(pos.revolutions() * getWheelTravel()).inches() << "\n"
            //           << "\tout: " << out << "\n";

            arcade(0, out, 0);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::driveToFast(Distance target)//drivesTo a distance, but freaky!
    {
        Jath::PID pid = Jath::PID()
                            .withConstants(25 / Jath::Inches(1), 0.01, 2)
                            .withIntegralZone(Revolutions(Inches(6)/ getWheelTravel()))
                            .withTimeout(6)
                            .withSettleZone(Revolutions(Jath::Inches(3)/ getWheelTravel()))
                            .withSettleTimeout(0.25);

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        pid.reset();
        while (!pid.isCompleted())
        {
            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            double out = pid.calculate(targetRot - pos);

            std::cout << "targetRot :" << Distance(Angle(targetRot - pos).revolutions()*getWheelTravel()).inches() << "\n"
                      << "\tout: " << out << "\n";

            arcade(0, out, 0);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::turnTo(Angle target)
    {
        Jath::PID pid = Jath::PID()
                            .withConstants(1 / Jath::Degrees(1), 3, 5)
                            .withIntegralZone(Jath::Degrees(20))
                            .withTimeout(5)
                            .withSettleZone(Jath::Degrees(3))
                            .withSettleTimeout(0.25);

        pid.reset();
        while (!pid.isCompleted())
        {
            Angle error = shortestTurnPath(Degrees(target.degrees() - m_inert.heading(vex::degrees)));

            double out = pid.calculate(error);

            arcade(0, 0, out);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::turnToFast(Angle target)
    {
        Jath::PID pid = Jath::PID()
                            .withConstants(1 / Jath::Degrees(1), 3, 2)
                            .withIntegralZone(Jath::Degrees(20))
                            .withTimeout(5)
                            .withSettleZone(Jath::Degrees(7.5))
                            .withSettleTimeout(0.10);

        pid.reset();
        while (!pid.isCompleted())
        {
            Angle error = shortestTurnPath(Degrees(target.degrees() - m_inert.heading(vex::degrees)));

            double out = pid.calculate(error);

            arcade(0, 0, out);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }

    void SmartDrive::turnToTuned(Angle target, Angle settleRange, double totalTimeout){
        Jath::PID pid = Jath::PID()
                            .withConstants(2 / Jath::Degrees(1), 3, 5)
                            .withIntegralZone(Jath::Degrees(20))
                            .withTimeout(totalTimeout)
                            .withSettleZone(settleRange)
                            .withSettleTimeout(0.25);

        int errorSign = 0;

        pid.reset();
        while (!pid.isCompleted())
        {
            Angle error = shortestTurnPath(Degrees(target.degrees() - m_inert.heading(vex::degrees)));

            if(errorSign != 0 && errorSign != getSign(error)){
                turnTo(m_dir);

            }

            double out = pid.calculate(error);

            arcade(0, 0, out);

            errorSign = getSign(error);
            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }

    void SmartDrive::turnToPoint(Vec2 target)
    {
        Jath::PID pid = Jath::PID()
                            .withConstants(1 / Jath::Degrees(1), 3, 5)
                            .withIntegralZone(Jath::Degrees(20))
                            .withTimeout(5)
                            .withSettleZone(Jath::Degrees(3))
                            .withSettleTimeout(0.25);

        Angle targetA = m_pos.angleTo(target);

        pid.reset();
        while (!pid.isCompleted())
        {
            targetA = m_pos.angleTo(target);
            Angle error = shortestTurnPath(Degrees(targetA.degrees() - m_inert.heading(vex::degrees)));

            double out = pid.calculate(error);

            arcade(0, 0, out);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }

    Distance SmartDrive::driveToPoint(Vec2 target)
    {

        Jath::PID pidr = Jath::PID()
                             .withConstants(1 / Jath::Degrees(1), 3, 5)
                             .withIntegralZone(Jath::Degrees(20))
                             .withTimeout(5)
                             .withSettleZone(Jath::Degrees(3))
                             .withSettleTimeout(0.25);

        Jath::PID pidd = Jath::PID()
                             .withConstants(20 / Jath::Inches(5), 0.0, 2)
                             .withIntegralZone(Jath::Inches(3))
                             .withTimeout(50)
                             .withSettleZone(Jath::Inches(2))
                             .withSettleTimeout(0.5);
        pidr.reset();
        pidd.reset();
        while (!pidd.isCompleted())
        {

            Angle angle = Angle(m_pos.angleTo(target) - m_dir);
            angle = Angle(shortestTurnPath(angle));
            Distance dist = m_pos.distTo(target);

            double rotOut = pidr.calculate(angle);
            double driveOut = pidd.calculate(dist);

            if (std::abs(angle.degrees()) > 15)
            {
                arcade(0, 0, Jath::cap<double>(rotOut, 100));
            }
            else
            {
                arcade(0, Jath::cap<double>(driveOut,100), Jath::cap<double>(rotOut, 100));
            }

            // std::cout << "angle :" << (std::abs(dist.inches()) < 5) << "\n"
            //           << "\tdist: " << dist.inches() << "\n";
            if (std::abs(dist.inches()) < 5)
            {
                arcade(0, 0, 0);
                driveTo(0);
                return 0;
            }

            wait(20, vex::msec);
        }
        return 0;
    }
    void SmartDrive::driveToPointStoopid(Vec2 target)
    {
        Angle angle = Angle(m_pos.angleTo(target) - m_dir);
        angle = Angle(shortestTurnPath(angle));
        Distance dist = m_pos.distTo(target);

        turnTo(m_pos.angleTo(target));
        driveTo(m_pos.distTo(target));
    }
    void SmartDrive::driveToPointTuned(Vec2 target, double settleRange, double totalTimeout ){
        
        Jath::PID pidr = Jath::PID()
                             .withConstants(1 / Jath::Degrees(1), 3, 5)
                             .withIntegralZone(Jath::Degrees(20))
                             .withTimeout(5)
                             .withSettleZone(Jath::Degrees(3))
                             .withSettleTimeout(0.25);

        Jath::PID pidd = Jath::PID()
                             .withConstants(20 / Jath::Inches(5), 0.0, 2)
                             .withIntegralZone(Jath::Inches(3))
                             .withTimeout(50)
                             .withSettleZone(Jath::Inches(2))
                             .withSettleTimeout(0.5);
        pidr.reset();
        pidd.reset();
        while (!pidd.isCompleted())
        {

            Angle angle = Angle(m_pos.angleTo(target) - m_dir);
            angle = Angle(shortestTurnPath(angle));
            Distance dist = m_pos.distTo(target);

            double rotOut = pidr.calculate(angle);
            double driveOut = pidd.calculate(dist);

            if (std::abs(angle.degrees()) > 15)
            {
                arcade(0, 0, Jath::cap<double>(rotOut, 100));
            }
            else
            {
                arcade(0, Jath::cap<double>(driveOut, 40), Jath::cap<double>(rotOut, 100));
            }

            // std::cout << "angle :" << (std::abs(dist.inches()) < 5) << "\n"
            //           << "\tdist: " << dist.inches() << "\n";
            if (std::abs(dist.inches()) < settleRange)
            {
                arcade(0, 0, 0);
                driveTo(0);
            }

            wait(20, vex::msec);
        }
    }

    Angle SmartDrive::shortestTurnPath(Angle target)
    {
        target.constrain();
        Angle angle = target;
        if (std::abs(angle.revolutions()) < .5)
        {
            return angle;
        }
        else
        {
            if (angle.revolutions() > 0)
            {
                return Revolutions(1 - angle.revolutions());
            }
            else
            {
                return Revolutions(1 + angle.revolutions());
            }
        }
        return Angle();
    }

    Distance Jath::SmartDrive::getWheelTravel()
    {
        return Distance(M_PI * m_wheelSize * m_gearRatio);
    }
}
