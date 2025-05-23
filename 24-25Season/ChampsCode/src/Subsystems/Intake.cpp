#include "Subsystems/Intake.h"

Intake::Intake(vex::motor motIntake, vex::motor motHooks, vex::optical opt) : m_motor_intake(motIntake), m_motor_hooks(motHooks), m_optical(opt)
{
    m_optical.integrationTime(5);
}

void Intake::periodic()
{
    switch (m_state)
    {
    case CONTROL:
        m_cmd = m_input_cmd;
        m_cmd_intake = m_input_cmd;
        m_optical.setLight(vex::ledState::off);
        break;
    case REJECT_RED:
        m_cmd = 100;
        m_cmd_intake = 100;
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
        m_cmd_intake = 100;
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
        m_cmd_intake = 100;
        m_optical.setLight(vex::ledState::on);
        if (m_optical.getRgb().red > 75 && m_optical.getRgb().blue < 75 || m_optical.isNearObject())
        {
            m_cmd = 0;
            m_input_cmd = 0;
            setState(CONTROL);
            m_optical.setLight(vex::ledState::off);
        }
        break;
    case STOP_BLUE:
        m_cmd = 100;
        m_cmd_intake = 100;
        m_optical.setLight(vex::ledState::on);
        if (m_optical.getRgb().blue > 75 && m_optical.getRgb().red < 75 || m_optical.isNearObject())
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
            m_cmd_intake = 0;
            if (m_continousSorting)
            {
                setState(m_lastState);
                setState(DELAY_ON);
                resetDelay(0.25);
            }
            else
            {
                setState(CONTROL);
            }
        }
        else
        {
            m_cmd = 100;
            m_cmd_intake = 100;
        }
        break;
    case DELAY_ON:
        if (timePassed() > m_delay)
        {
            m_cmd = 100;
            m_cmd_intake = 100;
            if (m_continousSorting)
            {
                setState(m_lastState);
            }
            else
            {
                setState(CONTROL);
            }
        }
        else
        {
            m_cmd = 0;
            m_cmd_intake = 0;
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

    if (m_motor_hooks.get() > 50 && m_motor_hooks.velocity(vex::pct) < 5 &&
        m_state != ANTI_JAM_REVERSE)
    {
        if (m_runningAntijam && timeMoving() > 0.125)
        {
            m_delay = 0.25;
            resetDelay();
            m_lastState = m_state;
            m_state = ANTI_JAM_REVERSE;
        }
    }
    else
    {
        m_startMovingTime = std::chrono::high_resolution_clock::now();
    }

    m_motor_hooks.set(m_cmd);
    m_motor_intake.set(m_cmd_intake);
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
    m_lastState = m_state;
    m_startMovingTime = std::chrono::high_resolution_clock::now();
    m_state = state;
}
Intake::IntakeState Intake::getState()
{
    return m_state;
}
void Intake::setContinousSorting()
{
    m_continousSorting = true;
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
art::SimpleMotor &Intake::getMotor()
{
    return m_motor_hooks;
}