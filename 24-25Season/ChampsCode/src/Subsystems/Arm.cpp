#include "Subsystems\Arm.h"

Arm::Arm(vex::motor mot, vex::motor mot2, art::PID pid) : m_motor(mot),m_motor2(mot2), m_pid(pid)
{
    m_motor.setStopping(vex::hold);
    resetPos();
}

void Arm::resetPos()
{
    m_motor.setPosition(-15 * 3.0, vex::degrees);
    m_motor2.setPosition(-15 * 3.0, vex::degrees);
}
void Arm::periodic()
{

    double motorPos = ((m_motor.position(vex::degrees)* .33333) + (m_motor2.position(vex::degrees)* .33333) * 0.5);

    art::Angle adjusted_pos_cmd = art::Angle(m_pos_cmd) - art::Degrees(90);
    art::Angle feedbackAngle = art::Degrees(motorPos) - art::Degrees(90);
    feedbackAngle.constrain();
    adjusted_pos_cmd.constrain();
    
    switch (m_state)
    {
    case CONTROL:
        m_output = m_cmd;
        m_pos_cmd = art::Degrees(motorPos);
        break;
    case POSITION:
        if (fabs(art::Angle(adjusted_pos_cmd - feedbackAngle).degrees()) >= 0.5)
        {
            m_output = m_pid.calculate(adjusted_pos_cmd - feedbackAngle);
        }else{
            m_output = 0;
        }
        break;
    default:
        break;
    }

    m_motor.set(m_output);
    m_motor2.set(m_output);
}
void Arm::handlePosInput(art::Angle input)
{
    m_pid.reset();
    m_pos_cmd = input;
}
void Arm::handleCmdInput(double input)
{
    m_cmd = input;
}

void Arm::setState(ArmState state)
{
    m_state = state;
}
bool Arm::isComplete()
{
    return m_pid.isCompleted();
}
art::SimpleMotorGroup &Arm::getMotor()
{
    return m_motor;
}

art::Angle Arm::getPosCmd()
{
    return m_pos_cmd;
}
