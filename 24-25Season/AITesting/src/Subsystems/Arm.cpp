#include "Subsystems\Arm.h"

Arm::Arm(vex::motor mot, vex::rotation rot, art::PID pid) : m_motor(mot), m_rotation(rot), m_pid(pid)
{
    m_motor.setBrake(vex::hold);
}

void Arm::periodic()
{

    art::Angle adjusted_pos_cmd = art::Angle(m_pos_cmd) - art::Degrees(90);
    art::Angle feedbackAngle = art::Degrees(m_rotation.angle()) - art::Degrees(90);
    feedbackAngle.constrain();
    adjusted_pos_cmd.constrain();
    
    switch (m_state)
    {
    case CONTROL:
        m_output = m_cmd;
        m_pos_cmd = art::Degrees(m_rotation.angle());
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
art::SimpleMotor &Arm::getMotor()
{
    return m_motor;
}

art::Angle Arm::getPosCmd()
{
    return m_pos_cmd;
}

vex::rotation &Arm::getRotation()
{
    return m_rotation;
}
