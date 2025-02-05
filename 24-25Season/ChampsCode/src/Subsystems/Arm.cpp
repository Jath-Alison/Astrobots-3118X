#include "Subsystems\Arm.h"

Arm::Arm(vex::motor mot, vex::rotation rot, art::PID pid) : m_motor(mot), m_rotation(rot), m_pid(pid)
{
}

void Arm::periodic()
{
    switch (m_state)
    {
    case CONTROL:
        m_output = m_cmd;
        m_pos_cmd = art::Degrees(m_rotation.angle());
        break;
    case POSITION:
        if (abs(art::shortestTurnPath(m_pos_cmd - art::Degrees(m_rotation.angle())).degrees()) >= 0.5)
        {
            if (art::shortestTurnPath(m_pos_cmd - art::Degrees(m_rotation.angle())).degrees() > 30 && m_pos_cmd.degrees() < 50)
            {
                m_output = -m_pid.calculate(art::shortestTurnPath(m_pos_cmd - art::Degrees(m_rotation.angle())));
            }
            else
            {
                m_output = m_pid.calculate(art::shortestTurnPath(m_pos_cmd - art::Degrees(m_rotation.angle())));
            };
        }
        break;
    default:
        break;
    }

    m_motor.set(m_output);
}
void Arm::handlePosInput(art::Angle input)
{
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