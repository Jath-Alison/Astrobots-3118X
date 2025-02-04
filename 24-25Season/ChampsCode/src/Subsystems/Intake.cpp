#include "Subsystems/Intake.h"

Intake::Intake(vex::motor mot, vex::optical opt) : m_motor(mot), m_optical(opt)
{
}

void Intake::periodic()
{
    switch (m_state)
    {
    case CONTROL:
        m_cmd = m_input_cmd;
        break;
    case REJECT_RED:
        m_cmd = 100;
        if (m_optical.getRgb().red > 100)
        {
            setState(DELAY_OFF);
            m_delay = 0.25;
            resetDelay();
        }
        break;
    case REJECT_BLUE:
        m_cmd = 100;
        if (m_optical.getRgb().blue > 100)
        {
            setState(DELAY_OFF);
            m_delay = 0.25;
            resetDelay();
        }
        break;
    case STOP_RED:
        m_cmd = 100;
        if (m_optical.getRgb().red > 100)
        {
            m_cmd = 0;
            m_input_cmd = 0;
            setState(CONTROL);
        }
        break;
    case STOP_BLUE:
        m_cmd = 100;
        if (m_optical.getRgb().blue > 100)
        {
            m_cmd = 0;
            m_input_cmd = 0;
            setState(CONTROL);
        }
        break;
    case DELAY_OFF:
        if (timePassed() > m_delay)
        {
            m_cmd = 0;
            setState(CONTROL);
        }
        break;
    case DELAY_ON:
        if (timePassed() > m_delay)
        {
            m_cmd = 100;
            setState(CONTROL);
        }
        break;
    default:
        break;
    }

    m_motor.set(m_cmd);
}

void Intake::handleInput(double input)
{
    m_input_cmd = input;
}

void Intake::setState(IntakeState state)
{
    m_state = state;
}
void Intake::resetDelay()
{
    m_startTime = std::chrono::high_resolution_clock::now();
}
double Intake::timePassed()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime).count() / 1000.0F;
}