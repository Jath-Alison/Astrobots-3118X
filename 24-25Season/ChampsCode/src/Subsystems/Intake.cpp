#include "Subsystems/Intake.h"

Intake::Intake(vex::motor mot, vex::optical opt) : m_motor(mot), m_optical(opt)
{
    m_optical.integrationTime(5);
}

void Intake::periodic()
{
    switch (m_state)
    {
    case CONTROL:
        m_cmd = m_input_cmd;
        m_optical.setLight(vex::ledState::off);
        break;
    case REJECT_RED:
        m_cmd = 100;
        m_optical.setLight(vex::ledState::on);
        if (m_optical.getRgb().red > 75 && m_optical.getRgb().blue < 75)
        {
            setState(DELAY_OFF);
            m_optical.setLight(vex::ledState::off);
            m_delay = 0.17;
            resetDelay();
        }
        break;
    case REJECT_BLUE:
        m_cmd = 100;
        m_optical.setLight(vex::ledState::on);
        if (m_optical.getRgb().blue > 75 && m_optical.getRgb().red < 75)
        {
            setState(DELAY_OFF);
            m_optical.setLight(vex::ledState::off);
            m_delay = 0.17;
            resetDelay();
        }
        break;
    case STOP_RED:
        m_cmd = 100;
        m_optical.setLight(vex::ledState::on);
        if (m_optical.getRgb().red > 75 && m_optical.getRgb().blue < 75)
        {
            m_cmd = 0;
            m_input_cmd = 0;
            setState(CONTROL);
            m_optical.setLight(vex::ledState::off);
        }
        break;
    case STOP_BLUE:
        m_cmd = 100;
        m_optical.setLight(vex::ledState::on);
        if (m_optical.getRgb().blue > 75 && m_optical.getRgb().red < 75)
        {
            m_cmd = 0;
            m_input_cmd = 0;
            setState(CONTROL);
            m_optical.setLight(vex::ledState::off);
        }
        break;
    case DELAY_OFF:
        if (timePassed() > m_delay)
        {
            m_cmd = 0;
            setState(CONTROL);
        }
        else
        {
            m_cmd = 100;
        }
        break;
    case DELAY_ON:
        if (timePassed() > m_delay)
        {
            m_cmd = 100;
            setState(CONTROL);
        }
        else
        {
            m_cmd = 0;
        }
        break;
    case ANTI_JAM_REVERSE:
        if (timePassed() > m_delay)
        {
            m_startMovingTime = std::chrono::high_resolution_clock::now();

            m_cmd = 100;
            setState(m_lastState);
        }
        else
        {
            m_cmd = -100;
        }
    default:
        break;
    }

    if (m_runningAntijam && timeMoving() > 0.125 &&
        m_motor.get() > 50 && m_motor.velocity(vex::pct) < 5 &&
        m_state != ANTI_JAM_REVERSE)
    {
        m_delay = 0.25;
        resetDelay();
        m_lastState = m_state;
        m_state = ANTI_JAM_REVERSE;
    }

    m_motor.set(m_cmd);
}

void Intake::handleInput(double input)
{
    if (input == m_input_cmd)
    {
        return;
    }
    m_startMovingTime = std::chrono::high_resolution_clock::now();
    m_input_cmd = input;
}

void Intake::setState(IntakeState state)
{
    m_startMovingTime = std::chrono::high_resolution_clock::now();
    m_state = state;
}
void Intake::resetDelay()
{
    m_startTime = std::chrono::high_resolution_clock::now();
}
void Intake::resetDelay(double time)
{
    m_delay = time;
    m_startTime = std::chrono::high_resolution_clock::now();
}
double Intake::timePassed()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime).count() / 1000.0F;
}

double Intake::timeMoving()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startMovingTime).count() / 1000.0F;
}
void Intake::setAntiJam(bool runningAntiJam) { m_runningAntijam = runningAntiJam; };
bool Intake::getAntiJam() { return m_runningAntijam; };