#include "Subsystems\Arm.h"

Arm::Arm(vex::motor_group mot, art::PID pid) : m_motor(mot), m_pid(pid)
{
    m_motor.setStopping(vex::hold);
    m_motor.setPosition(-15 * .33333, vex::degrees);
}

void Arm::periodic()
{

    art::Angle adjusted_pos_cmd = art::Angle(m_pos_cmd) - art::Degrees(90);
    art::Angle feedbackAngle = art::Degrees(m_motor.position(vex::degrees)* .33333) - art::Degrees(90);
    feedbackAngle.constrain();
    adjusted_pos_cmd.constrain();
    
    switch (m_state)
    {
    case CONTROL:
        m_output = m_cmd;
        m_pos_cmd = art::Degrees(m_motor.position(vex::degrees)* .33333);
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
