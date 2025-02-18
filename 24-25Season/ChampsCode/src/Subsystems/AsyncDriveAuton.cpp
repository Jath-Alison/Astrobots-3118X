#include "Subsystems/AsyncDrive.h"
#include <iostream>

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

void AsyncDrive::followPathA(Jath::Path p){
    m_path = p;
    if(m_path.m_points.size() > 0){
        m_pos = m_path.m_points.front().m_pos;
    }

    m_turnPID.reset();
    m_state = AsyncDrive::PATH;

}
void AsyncDrive::followPathA(Jath::Path p, art::Length lookahead){
    m_lookaheadDist = lookahead;
    followPathA(p);
}
void AsyncDrive::followPathA(Jath::Path p, art::Length lookahead, art::PID turnPID){
    m_lookaheadDist = lookahead;
    m_turnPID = turnPID;
    followPathA(p);
}
void AsyncDrive::followPathS(Jath::Path p){
    followPathA(p);
    waitUntil(pathComplete());
}
void AsyncDrive::followPathS(Jath::Path p, art::Length lookahead){
    m_lookaheadDist = lookahead;
    followPathA(p);
    waitUntil(pathComplete());
}
void AsyncDrive::followPathS(Jath::Path p, art::Length lookahead, art::PID turnPID){
    m_lookaheadDist = lookahead;
    m_turnPID = turnPID;
    followPathA(p);
    waitUntil(pathComplete());
}