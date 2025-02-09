#include "Subsystems/AsyncDrive.h"

void AsyncDrive::driveForA(art::Length target)
{
    setDriveTarget(target);
    m_state = AsyncDrive::DRIVE;
}
void AsyncDrive::driveForA(art::Length target, art::PID pid)
{
    m_drivePID = pid; m_drivePID.reset();
    driveForA(target);
}
void AsyncDrive::driveForS(art::Length target)
{
    driveForA(target);
    waitUntil(m_drivePID.isCompleted());
}
void AsyncDrive::driveForS(art::Length target, art::PID pid)
{
    m_drivePID = pid; m_drivePID.reset();

    driveForA(target);

    waitUntil(m_drivePID.isCompleted());
}

void AsyncDrive::turnToA(art::Angle target)
{
    setTurnTarget(target);
    m_state = AsyncDrive::TURN;
}
void AsyncDrive::turnToA(art::Angle target, art::PID pid)
{
    m_turnPID = pid; m_turnPID.reset();
    turnToA(target);
}
void AsyncDrive::turnToS(art::Angle target)
{
    turnToA(target);
    waitUntil(m_turnPID.isCompleted());
}
void AsyncDrive::turnToS(art::Angle target, art::PID pid)
{
    m_turnPID = pid; m_turnPID.reset();

    turnToA(target);

    waitUntil(m_turnPID.isCompleted());
}

void AsyncDrive::driveForHeadingCorrectedA(art::Length target, art::Angle heading)
{
    setDriveTarget(target);
    setTurnTarget(heading);
    m_state = AsyncDrive::DRIVE_HEADING_CORRECTED;
}
void AsyncDrive::driveForHeadingCorrectedA(art::Length target, art::Angle heading, art::PID drivePID, art::PID turnPID)
{
    m_drivePID = drivePID; m_drivePID.reset();
    m_turnPID = turnPID; m_turnPID.reset();
    driveForHeadingCorrectedA(target, heading);
}
void AsyncDrive::driveForHeadingCorrectedS(art::Length target, art::Angle heading)
{
    driveForHeadingCorrectedA(target, heading);
    waitUntil(m_drivePID.isCompleted());
}
void AsyncDrive::driveForHeadingCorrectedS(art::Length target, art::Angle heading, art::PID drivePID, art::PID turnPID)
{
    m_drivePID = drivePID; m_drivePID.reset();
    m_turnPID = turnPID; m_turnPID.reset();

    driveForHeadingCorrectedA(target, heading);

    waitUntil(m_drivePID.isCompleted());
}