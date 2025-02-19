#include "Subsystems/AsyncDrive.h"
#include <iostream>

AsyncDrive::AsyncDrive(art::TankDrive drive, vex::inertial inert) : art::TankDrive(drive), m_inert(inert)
{
    m_inert.calibrate();
}

AsyncDrive &AsyncDrive::withWheelSize(art::Length size)
{
    m_wheelSize = size;
    return *this;
}

AsyncDrive &AsyncDrive::withGearRatio(double ratio)
{
    m_gearRatio = ratio;
    return *this;
}

AsyncDrive &AsyncDrive::withDefaultPIDs(art::PID drivePid, art::PID turnPid)
{
    m_drivePID = drivePid;
    m_turnPID = turnPid;
    return *this;
}
AsyncDrive &AsyncDrive::withHorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio)
{
    m_tracker = HorizontalTracker(rotation, wheelSize, gearRatio);
    return *this;
}

AsyncDrive &AsyncDrive::withHorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio, art::Length wheelOffset)
{
    m_tracker = HorizontalTracker(rotation, wheelSize, gearRatio, wheelOffset);
    return *this;
}

void AsyncDrive::setXFlip(bool flip)
{
    m_flipX = flip;
}
void AsyncDrive::setYFlip(bool flip)
{
    m_flipY = flip;
}
int AsyncDrive::track()
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
        static art::Angle prevDir;
        if (m_dir != prevDir)
        {
            m_inert.setHeading(m_dir.degrees(), vex::deg);
        }
        m_dir = art::Degrees(m_inert.heading(vex::degrees));

        art::Angle leftTravel = getLeftTravel();
        art::Angle rightTravel = getRightTravel();

        m_leftTravel = art::Length(leftTravel.revolutions() * getWheelTravel());
        m_rightTravel = art::Length(rightTravel.revolutions() * getWheelTravel());

        art::Angle wheelTravel = art::Angle((leftTravel + rightTravel) / 2.0);
        art::Length travel = art::Length(wheelTravel.revolutions() * getWheelTravel());

        // Distance travel = Inches(change*((3.25 * 3.1415)/360.f) / (72.f/48.f));
        art::Vec2 posChange = art::Vec2::dirAndMag(m_dir, travel);

        if (m_tracker.m_rotation != nullptr)
        {
            art::Length hTravel = m_tracker.getTravel();

            art::Vec2 trackerTravel = art::Vec2::dirAndMag(m_dir + art::Degrees(90), hTravel);

            posChange = posChange + trackerTravel;
        }

        m_vel = posChange * (50.0);
        m_rotVel = art::Angle(m_dir - prevDir) * 50.0;

        m_pos = m_pos + posChange;
        m_centerPos = m_pos + art::Vec2::dirAndMag(m_dir, m_tracker.m_offset);

        prevDir = m_dir;

        vex::wait(20, vex::msec);
    }
}

bool AsyncDrive::isCalibrating()
{
    return m_inert.isCalibrating();
}
art::Angle AsyncDrive::getDir()
{
    return m_dir;
}
art::Vec2 AsyncDrive::getPos()
{
    return m_pos;
}
art::Vec2 AsyncDrive::getVel()
{
    return m_vel;
}
void AsyncDrive::periodic()
{

    double a = 0;
    art::Angle error;
    art::Angle pos;

    art::Vec2 travel;

    switch (m_state)
    {
    case WAIT:
        arcade(0, 0);
    case CONTROL:
        arcade(drive_input, rot_input);
        break;
    case DRIVE:

        pos = art::Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        a = m_drivePID.calculate(m_driveTarget - pos);

        arcade(a, 0);

        break;
    case DRIVE_HEADING_CORRECTED:
        pos = art::Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
        a = m_drivePID.calculate(m_driveTarget - pos);

        error = shortestTurnPath(art::Degrees(m_turnTarget.degrees() - m_dir.degrees()));

        if (abs(a) > 100)
        {
            a *= 100.0 / fabs(a);
        }

        arcade(a, m_turnPID.calculate(error));

        break;
    case TURN:

        error = shortestTurnPath(art::Degrees(m_turnTarget.degrees() - m_dir.degrees()));
        arcade(0, m_turnPID.calculate(error));

        break;
    case SWING_ABOUT_LEFT:
        error = shortestTurnPath(art::Degrees(m_turnTarget.degrees() - m_dir.degrees()));
        a = m_turnPID.calculate(error);
        m_right.set(-a);
        break;
    case SWING_ABOUT_RIGHT:
        error = shortestTurnPath(art::Degrees(m_turnTarget.degrees() - m_dir.degrees()));
        a = m_turnPID.calculate(error);
        m_left.set(a);
        break;
    case PATH:
        
        m_lookahead = m_path.getLookahead(m_centerPos, m_lookaheadDist);
        
        // m_closest = m_path.getClosestPoint(m_centerPos);
        

        travel = art::Vec2(m_lookahead.m_pos - m_centerPos);

        error = shortestTurnPath(art::Degrees(art::Angle(travel.direction()).degrees() - m_dir.degrees()));
        arcade(m_lookahead.m_speed, m_turnPID.calculate(error));
        
        break;
    default:
        break;
    }
}
void AsyncDrive::setState(DriveState state)
{
    m_state = state;
}
void AsyncDrive::handleInputs(double drive, double rot)
{
    drive_input = drive * drive * drive * 0.01 * 0.01;
    rot_input = rot * rot * rot * 0.01 * 0.01;
}
void AsyncDrive::setDriveTarget(art::Length target)
{
    m_driveOffset = art::Degrees((m_left.position(vex::degrees) + m_right.position(vex::degrees)) / 2.f);
    m_driveTarget = art::Angle(art::Revolutions(target / getWheelTravel()) + m_driveOffset);
    m_drivePID.reset();
}
void AsyncDrive::setTurnTarget(art::Angle target)
{
    art::Angle targetCopy = art::Angle(target);
    if (m_flipX)
    {
        targetCopy = art::Angle(targetCopy * -1);
    }
    if (m_flipY)
    {
        targetCopy = art::Angle(art::Degrees(180) - targetCopy);
    }

    std::cout << "target: " << target.degrees() << ", Converted: " << targetCopy.degrees() <<std::endl; 

    m_turnTarget = targetCopy;
    
    m_turnPID.reset();
}
void AsyncDrive::zeroGyro()
{
    m_dir = art::Angle(0);
}
bool AsyncDrive::driveComplete()
{
    return m_drivePID.isCompleted();
}
bool AsyncDrive::turnComplete()
{
    return m_turnPID.isCompleted();
}

bool AsyncDrive::pathComplete()
{
    return m_lookahead.m_speed == -1;
}
double AsyncDrive::driveError()
{
    return m_drivePID.getProportional() / m_drivePID.getkp();
}
double AsyncDrive::turnError()
{
    return m_turnPID.getProportional() / m_turnPID.getkp();
}

art::Angle AsyncDrive::getLeftTravel()
{
    art::Angle currentAngle = art::Degrees(m_left.position(vex::degrees));

    art::Angle tempAngle = art::Angle(currentAngle - m_LastLeftPos);
    m_LastLeftPos = currentAngle;

    return tempAngle;
}
art::Angle AsyncDrive::getRightTravel()
{
    art::Angle currentAngle = art::Degrees(m_right.position(vex::degrees));

    art::Angle tempAngle = art::Angle(currentAngle - m_LastRightPos);
    m_LastRightPos = currentAngle;

    return tempAngle;
}

art::Length AsyncDrive::getWheelTravel()
{
    return art::Length(M_PI * m_wheelSize * m_gearRatio);
}

AsyncDrive::HorizontalTracker::HorizontalTracker() {}
AsyncDrive::HorizontalTracker::HorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio) : m_wheelSize(wheelSize), m_gearRatio(gearRatio)
{
    m_rotation = std::make_shared<vex::rotation>(rotation);
}
AsyncDrive::HorizontalTracker::HorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio, art::Length wheelOffset) : m_wheelSize(wheelSize), m_gearRatio(gearRatio), m_offset(wheelOffset)
{
    m_rotation = std::make_shared<vex::rotation>(rotation);
}
art::Length AsyncDrive::HorizontalTracker::getTravel()
{
    art::Angle currentAngle = art::Degrees(m_rotation->position(vex::degrees));

    m_travelAngle = art::Angle(currentAngle - m_lastAngle);
    m_lastAngle = currentAngle;

    m_travelDistance = art::Length(m_travelAngle * (m_wheelSize / 2.0) * m_gearRatio);

    return m_travelDistance;
}