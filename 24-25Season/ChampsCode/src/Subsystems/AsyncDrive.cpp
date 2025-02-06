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
    case WAIT:
        m_smartDrive.arcade(0, 0);
    case CONTROL:
        m_smartDrive.arcade(drive_input, rot_input);
        break;
    case DRIVE:

        pos = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
        a = m_smartDrive.m_driveForPID.calculate(m_driveTarget - pos);

        m_smartDrive.arcade(a, 0);

        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_P, m_smartDrive.m_driveForPID.getProportional());
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_I, m_smartDrive.m_driveForPID.getIntegral());
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_D, m_smartDrive.m_driveForPID.getDerivative());
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_feedback, pos);
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_target, m_driveTarget);

        break;
    case DRIVE_HEADING_CORRECTED:
        pos = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
        a = m_smartDrive.m_driveForPID.calculate(m_driveTarget - pos);

        error = art::Degrees(m_turnTarget.degrees() - m_smartDrive.m_inert.rotation(vex::degrees));

        m_smartDrive.arcade(a, m_smartDrive.m_turnForPID.calculate(error));

        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_P, m_smartDrive.m_driveForPID.getProportional());
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_I, m_smartDrive.m_driveForPID.getIntegral());
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_D, m_smartDrive.m_driveForPID.getDerivative());
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_feedback, pos);
        logging::logger.logDoubleEntry(logging::Base_DriveTo_PID_target, m_driveTarget);

        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_P, m_smartDrive.m_turnForPID.getProportional());
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_I, m_smartDrive.m_turnForPID.getIntegral());
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_D, m_smartDrive.m_turnForPID.getDerivative());
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_feedback, m_smartDrive.m_inert.rotation(vex::degrees));
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_target, m_turnTarget.degrees());

        break;
    case TURN:

        error = shortestTurnPath(art::Degrees(m_turnTarget.degrees() - m_smartDrive.m_inert.rotation(vex::degrees)));
        m_smartDrive.arcade(0, m_smartDrive.m_turnForPID.calculate(error));

        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_P, m_smartDrive.m_turnForPID.getProportional());
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_I, m_smartDrive.m_turnForPID.getIntegral());
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_D, m_smartDrive.m_turnForPID.getDerivative());
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_feedback, m_smartDrive.m_inert.rotation(vex::degrees));
        logging::logger.logDoubleEntry(logging::Base_TurnTo_PID_target, m_turnTarget.degrees());

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
    rot_input = rot * rot * rot * 0.01 * 0.01;
}
void AsyncDrive::setDriveTarget(art::Length target)
{
    m_driveOffset = art::Degrees((m_smartDrive.m_left.position(vex::degrees) + m_smartDrive.m_right.position(vex::degrees)) / 2.f);
    m_driveTarget = art::Angle(art::Revolutions(target / m_smartDrive.getWheelTravel()) + m_driveOffset);
    m_smartDrive.m_driveForPID.reset();
}
void AsyncDrive::setTurnTarget(art::Angle target)
{
    m_turnTarget = target;
    m_smartDrive.m_turnForPID.reset();
}
bool AsyncDrive::driveComplete()
{
    return m_smartDrive.m_driveForPID.isCompleted();
}
bool AsyncDrive::turnComplete()
{
    return m_smartDrive.m_turnForPID.isCompleted();
}

double AsyncDrive::driveError()
{
    return m_smartDrive.m_driveForPID.getProportional() / m_smartDrive.m_driveForPID.getkp();
}
double AsyncDrive::turnError()
{
    return m_smartDrive.m_turnForPID.getProportional() / m_smartDrive.m_turnForPID.getkp();
}