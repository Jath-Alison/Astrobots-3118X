#include "Jath\Drives\SmartDrive.h"
#include "Jath\PID.h"
#include "Jath\PIDs\QPID.h"
#include <cmath>

namespace Jath
{

    SmartDrive::HorizontalTracker::HorizontalTracker() : m_wheelSize(0), m_gearRatio(0) {}
    SmartDrive::HorizontalTracker::HorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio) : m_wheelSize(wheelSize), m_gearRatio(gearRatio)
    {
        m_rotation = std::make_shared<vex::rotation>(rotation);
    }

    SmartDrive::HorizontalTracker::HorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio, Distance wheelOffset) : m_wheelSize(wheelSize), m_gearRatio(gearRatio), m_offset(wheelOffset)
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

    SmartDrive &SmartDrive::withHorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio, Distance wheelOffset)
    {
        m_tracker = HorizontalTracker(rotation, wheelSize, gearRatio, wheelOffset);
        return *this;
    }

    int SmartDrive::track()
    {
        if(m_tracker.m_rotation){
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

            Angle wheelTravel = Angle((m_left.travel() + m_right.travel()) / 2.0);
            Distance travel = Distance(wheelTravel.revolutions() * getWheelTravel());

            // Distance travel = Inches(change*((3.25 * 3.1415)/360.f) / (72.f/48.f));
            Vec2 posChange = Vec2::dirAndMag(m_dir, travel);

            if (m_tracker.m_rotation != nullptr)
            {
                Distance hTravel = m_tracker.getTravel();

                Vec2 trackerTravel = Vec2::dirAndMag(m_dir + Degrees(90), hTravel);

                posChange = posChange + trackerTravel;
            }else{
            }

            m_pos = m_pos + posChange;
            m_centerPos = m_pos + Vec2::dirAndMag(m_dir, m_tracker.m_offset);

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
        double out= 0;

        driveToGraph = Jath::Graph()
            .addDataset("time", [&](){return pid.timePassed() * 100;})
            .addDataset("sTime", [&](){return pid.settledTimePassed() * 100;})
            .addDataset("error", [&](){return Distance(pid.getProportional()/pid.getkp()).inches();})
            .addDataset("out", [&](){return out/10.f;})
            .addDataset("p", [&](){return pid.getProportional()/10.f;})
            .addDataset("i", [&](){return pid.getIntegral()/10.f;})
            .addDataset("d", [&](){return pid.getDerivative()/10.f;})
            .addDataset("set", [&](){return 1;})
            .addDataset("set", [&](){return -1;})
            ;

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetRot = Revolutions(target / getWheelTravel()) + offset;

        pid.reset();
        while (!pid.isCompleted())
        {
            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            out = pid.calculate(targetRot - pos);

            driveToGraph.getData();

            Brain.Screen.clearScreen();
            	driveToGraph.drawGraph(
                    Jath::Vec2::XandY(0,100),
                    Jath::Vec2::XandY(400,200)
                );

            arcade(0, out, 0);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    
    
    void SmartDrive::turnTo(Angle target)
    {
        Jath::PID pid = Jath::QPID()
                            .withConstants(2.5/(Degrees(1)), 20, -650)
                            .withIntegralZone(Jath::Degrees(10))
                            .withTimeout(2)
                            .withSettleZone(Jath::Degrees(2))
                            .withSettleTimeout(0.125);

        double out = 0;

        turnToGraph = Jath::Graph()
            .addDataset("time", [&](){return pid.timePassed() * 100;})
            .addDataset("sTime", [&](){return pid.settledTimePassed() * 100;})
            .addDataset("error", [&](){return Angle(pid.getProportional()/pid.getkp()).degrees();})
            .addDataset("out", [&](){return out/10.f;})
            .addDataset("p", [&](){return pid.getProportional()/10.f;})
            .addDataset("i", [&](){return pid.getIntegral()/10.f;})
            .addDataset("d", [&](){return pid.getDerivative()/10.f;})
            .addDataset("set", [&](){return 1;})
            .addDataset("set", [&](){return -1;})
            ;
        pid.reset();
        while (!pid.isCompleted())
        {
            Angle error = shortestTurnPath(Degrees(target.degrees() - m_inert.heading(vex::degrees)));

            out = pid.calculate(error);

            arcade(0, 0, out);

            turnToGraph.getData();

            Brain.Screen.clearScreen();
            	turnToGraph.drawGraph(
                    Jath::Vec2::XandY(0,100),
                    Jath::Vec2::XandY(400,200)
                );

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }

    void SmartDrive::driveToHoldAngle(Distance target)
    {
        Jath::PID pidd = Jath::PID()
                            .withConstants(25 / Jath::Inches(1), 0.0, 2)
                            .withIntegralZone(Jath::Inches(3))
                            .withTimeout(50)
                            .withSettleZone(Jath::Inches(0.5))
                            .withSettleTimeout(0.5);
        double driveOut = 0;

        Jath::PID pidr = Jath::QPID()
                            .withConstants(2.5/(Degrees(1)), 20, -650)
                            .withIntegralZone(Jath::Degrees(10))
                            .withTimeout(2)
                            .withSettleZone(Jath::Degrees(2))
                            .withSettleTimeout(0.125);
        double rotOut = 0;

        pidd.reset();
        pidr.reset();

        Angle targetRot = m_dir;

        Angle offset = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        Angle targetTravelRot = Revolutions(target / getWheelTravel()) + offset;

        while (!pidd.isCompleted())
        {
            Angle error = shortestTurnPath(Degrees(targetRot.degrees() - m_inert.heading(vex::degrees)));
            rotOut = pidr.calculate(error);

            Angle pos = Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
            driveOut = pidd.calculate(targetTravelRot - pos);

            arcade(0, driveOut, rotOut);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }


    void SmartDrive::turnToPoint(Vec2 target)
    {
        Jath::PID pid = Jath::QPID()
                            .withConstants(2.5/(Degrees(1)), 20, -650)
                            .withIntegralZone(Jath::Degrees(10))
                            .withTimeout(2)
                            .withSettleZone(Jath::Degrees(2))
                            .withSettleTimeout(0.125);

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
                             .withConstants(1 / Jath::Degrees(1), 3, -5)
                             .withIntegralZone(Jath::Degrees(20))
                             .withTimeout(5)
                             .withSettleZone(Jath::Degrees(3))
                             .withSettleTimeout(0.25);

        Jath::PID pidd = Jath::PID()
                             .withConstants(20 / Jath::Inches(5), 0.0, 2)
                             .withIntegralZone(Jath::Inches(3))
                             .withTimeout(50)
                             .withSettleZone(Jath::Inches(2))
                             .withSettleTimeout(0.05);
        pidr.reset();
        pidd.reset();
        while (!pidd.isCompleted())
        {

            Angle angle = Angle(m_pos.angleTo(target) - m_dir);
            angle = Angle(shortestTurnPath(angle));
            Distance dist = m_pos.distTo(target);

            double rotOut = pidr.calculate(angle);
            double driveOut = pidd.calculate(dist);

            if (std::abs(angle.degrees()) > 25)
            {
                arcade(0, 0, Jath::cap<double>(rotOut, 100));
            }
            else
            {
                arcade(0, Jath::cap<double>(driveOut, 60), Jath::cap<double>(rotOut, 100));
            }

            // std::cout << "angle :" << (std::abs(dist.inches()) < 5) << "\n"
            //           << "\tdist: " << dist.inches() << "\n";
            if (std::abs(dist.inches()) < settleRange)
            {
                arcade(0, 0, 0);
                // driveTo(0);
                return;
            }

            wait(20, vex::msec);
        }
    }

    Distance SmartDrive::driveTowardPoint(Vec2 target, double speedCap, bool clear)
    {
        Distance dist = m_pos.distTo(target);

        static Jath::PID pidr = Jath::QPID()
                            .withConstants(1/(Degrees(1)), 10, -400)
                            .withIntegralZone(Jath::Degrees(10))
                            .withTimeout(2)
                            .withSettleZone(Jath::Degrees(2))
                            .withSettleTimeout(0.125);

        Angle rotAngle = shortestTurnPath( m_pos.angleTo(target) - m_dir);
        double rotOut = pidr.calculate(rotAngle);

        if(clear){
            driveTowardPointGraph = Jath::Graph()
            .addDataset("S-x", [&](){return Distance(m_pos.x).inches();})
            .addDataset("S-y", [&](){return Distance(m_pos.y).inches();})
            .addDataset("T-x", [&](){return Distance(target.x).inches();})
            .addDataset("T-y", [&](){return Distance(target.y).inches();})
            .addDataset("dir-T", [&](){return rotAngle.degrees();})
            // .addDataset("time", [&](){return pidr.timePassed() * 100;})
            // .addDataset("sTime", [&](){return pidr.settledTimePassed() * 100;})
            // .addDataset("error", [&](){return Angle(pidr.getProportional()/pidr.getkp()).degrees();})
            // .addDataset("out", [&](){return rotOut/10.f;})
            // .addDataset("p", [&](){return pidr.getProportional()/10.f;})
            // .addDataset("i", [&](){return pidr.getIntegral()/10.f;})
            // .addDataset("d", [&](){return pidr.getDerivative()/10.f;})
            // .addDataset("set", [&](){return 1;})
            // .addDataset("set", [&](){return -1;})
            ;
            pidr.reset();
        }

        driveTowardPointGraph.getData();
        

        arcade(0,speedCap, rotOut);

        return dist;
    }

    void SmartDrive::turnToPointR(Vec2 target)
    {
        Jath::PID pid = Jath::PID()
                            .withConstants(1 / Jath::Degrees(1), 3, 5)
                            .withIntegralZone(Jath::Degrees(20))
                            .withTimeout(5)
                            .withSettleZone(Jath::Degrees(3))
                            .withSettleTimeout(0.25);

        Angle targetA = Angle(m_pos.angleTo(target) - Revolutions(0.5));

        pid.reset();
        while (!pid.isCompleted())
        {
            targetA = Angle(m_pos.angleTo(target) - Revolutions(0.5));
            Angle error = shortestTurnPath(Degrees(targetA.degrees() - m_inert.heading(vex::degrees)));

            double out = pid.calculate(error);

            arcade(0, 0, out);

            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }

    Distance SmartDrive::driveToPointR(Vec2 target)
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

            Angle angle = Angle(m_pos.angleTo(target) - m_dir - Revolutions(0.5));
            angle = Angle(shortestTurnPath(angle));
            Distance dist = m_pos.distTo(target);

            double rotOut = pidr.calculate(angle);
            double driveOut = -pidd.calculate(dist);

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
    void SmartDrive::driveToPointStoopidR(Vec2 target)
    {
        Angle angle = Angle(m_pos.angleTo(target) - m_dir - Revolutions(0.5));
        angle = Angle(shortestTurnPath(angle));
        Distance dist = m_pos.distTo(target);

        turnTo(m_pos.angleTo(target));
        driveTo(-m_pos.distTo(target));
    }
    void SmartDrive::driveToPointTunedR(Vec2 target, double settleRange, double totalTimeout ){
        
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

            Angle angle = Angle(m_pos.angleTo(target) - (m_dir - Revolutions(0.5)));
            angle = Angle(shortestTurnPath(angle));
            Distance dist = m_pos.distTo(target);

            double rotOut = pidr.calculate(angle);
            double driveOut = -pidd.calculate(dist);

            if (std::abs(angle.degrees()) > 15)
            {
                arcade(0, driveOut, rotOut);
            // std::cout << "out: " << driveOut << "\n";
            }
            else
            {
                arcade(0, Jath::floor<double>(driveOut, -60), rotOut);
            }

            // std::cout << "angle :" << (std::abs(dist.inches()) < 5) << "\n"
            //           << "\tdist: " << dist.inches() << "\n";
            if (std::abs(dist.inches()) < settleRange)
            {
                // std::cout << "-----finished -----\n";
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
