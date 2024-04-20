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
            Distance travel = Distance(wheelTravel * getWheelTravel());

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
        static Jath::PID pid = Jath::PID()
                                   .withConstants(0.5 / Jath::Inches(0), 10, 2)
                                   .withIntegralZone(Jath::Inches(1))
                                   .withTimeout(50)
                                   .withSettleZone(Jath::Inches(1))
                                   .withSettleTimeout(5);

        Angle offset = Degrees( (m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel());

        while (!pid.isCompleted())
        {
            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            double out = pid.calculate(target - pos);

            arcade(0, out, 0);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::turnTo(Angle target)
    {
        Jath::PID pid = Jath::PID()
                            .withConstants(0.75 / Jath::Degrees(1), 10, 10)
                            .withIntegralZone(Jath::Degrees(15))
                            .withTimeout(5)
                            .withSettleZone(Jath::Degrees(1))
                            .withSettleTimeout(1);

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
    Distance SmartDrive::driveToPoint(Vec2 target)
    {

        static Jath::PID pidr = Jath::PID()
                                    .withConstants(0.75 / Jath::Degrees(1), 10, 10)
                                    .withIntegralZone(Jath::Degrees(15))
                                    .withTimeout(5)
                                    .withSettleZone(Jath::Degrees(1))
                                    .withSettleTimeout(1);

        static Jath::PID pidd = Jath::PID()
                                    .withConstants(0.5 / Jath::Inches(0), 10, 2)
                                    .withIntegralZone(Jath::Inches(1))
                                    .withTimeout(50)
                                    .withSettleZone(Jath::Inches(1))
                                    .withSettleTimeout(5);
        pidr.reset();
        pidd.reset();
        while (!pidd.isCompleted())
        {

            Angle angle = Angle(m_pos.angleTo(target) - m_dir);
            angle = Angle(shortestTurnPath(angle));
            Distance dist = m_pos.distTo(target);

            if (std::abs(angle.degrees()) > 15)
            {
                arcade(0, 0, pidr.calculate(angle));
            }
            else
            {
                arcade(0, pidd.calculate(dist), pidr.calculate(angle));
            }

            std::cout << "angle :" << angle.degrees() << "\n"
                      << "\tdist: " << dist.inches() << "\n";

            update();
        }
        return 0;
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
        return Distance((m_wheelSize / 2.0) * m_gearRatio);
    }
}
