#include "Subsystems/AsyncDrive.h"

AsyncDrive::AsyncDrive(art::SmartDrive &drive) : m_smartDrive(drive)
{
}
void AsyncDrive::periodic()
{

    double a = 0;
    art::Angle error;
    art::Angle pos;

    switch (m_state)
    {
    case CONTROL:
        m_smartDrive.arcade(drive_input, rot_input);
        break;
    case DRIVE:

        pos = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
        a = m_smartDrive.m_driveForPID.calculate(m_driveTarget - pos);

        m_smartDrive.arcade(a, 0);

        break;
    case DRIVE_HEADING_CORRECTED:
        pos = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
        a = m_smartDrive.m_driveForPID.calculate(m_driveTarget - pos);

        error = art::Degrees(m_turnTarget.degrees() - m_smartDrive.m_inert.rotation(vex::degrees));

        m_smartDrive.arcade(a, m_smartDrive.m_turnForPID.calculate(error));
        break;
    case TURN:

        error = art::Degrees(m_turnTarget.degrees() - m_smartDrive.m_inert.rotation(vex::degrees));
        m_smartDrive.arcade(0, m_smartDrive.m_turnForPID.calculate(error));

        break;
    case PATH:
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
    rot_input =  rot * rot * rot * 0.01 * 0.01;
}
void AsyncDrive::setDriveTarget(art::Length target)
{
    m_driveOffset = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
    m_driveTarget = art::Angle(art::Revolutions(target / m_smartDrive.getWheelTravel()) + m_driveOffset);
}
void AsyncDrive::setTurnTarget(art::Angle target)
{
    m_turnTarget = target;
}
bool AsyncDrive::driveComplete()
{
    return m_smartDrive.m_driveForPID.isCompleted();
}
bool AsyncDrive::turnComplete()
{
    return m_smartDrive.m_turnForPID.isCompleted();
}

double AsyncDrive::driveError(){
    return m_smartDrive.m_driveForPID.getProportional()/m_smartDrive.m_driveForPID.getkp();
}
double AsyncDrive::turnError(){
    return m_smartDrive.m_turnForPID.getProportional()/m_smartDrive.m_turnForPID.getkp();
}