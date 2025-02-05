#include "Subsystems/AsyncDrive.h"
#include <iostream>

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

        m_driveTarget;

        pos = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
        a = m_smartDrive.m_driveForPID.calculate(m_driveTarget - pos);

        m_smartDrive.arcade(a, 0);

        break;
    case DRIVE_HEADING_CORRECTED:
        break;
    case TURN:

        error = art::Degrees(m_turnTarget.degrees() - m_smartDrive.m_inert.rotation(vex::degrees));

        m_smartDrive.arcade(0,m_smartDrive.m_turnForPID.calculate(error));

        break;
    case PATH:
        break;
    default:
        break;
    }
}
void AsyncDrive::setState(DriveState state){
    m_state = state;
}
void AsyncDrive::handleInputs(double drive, double rot)
{
    drive_input = drive;
    rot_input = rot;
}
void AsyncDrive::setDriveTarget(art::Length target)
{
    m_driveOffset = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
    m_driveTarget = art::Angle(art::Revolutions(target / m_smartDrive.getWheelTravel()) + m_driveOffset);

    std::cout << art::Revolutions(target / m_smartDrive.getWheelTravel()) + m_driveOffset << "," << m_driveTarget << std::endl;
}