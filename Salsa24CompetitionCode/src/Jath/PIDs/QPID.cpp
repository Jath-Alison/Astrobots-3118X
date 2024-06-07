#include "Jath\PIDs\QPID.h"
#include "Jath\Utils.h"

Jath::QPID::QPID() : PID()
{
}

double Jath::QPID::calculate(double error)
{
    m_error = error;
    m_derivative = m_prevError - m_error;

    if (std::abs(m_error) < m_integralZone)
    {
        m_integral += m_error;
    }
    else
    {
        m_integral = 0;
    }
    if ((m_error > 0 && m_prevError < 0) || (m_error < 0 && m_prevError > 0))
    {
        // m_integral *= -0.5;
    }

    if (std::abs(error) > m_settleZone)
    {
        m_startSettledTime = std::chrono::high_resolution_clock::now();
    }

    m_output = (m_kp * (m_error * m_error) * getSign(m_error)) + (m_kd * m_derivative) + (m_ki * m_integral) + m_ff;

    m_prevError = m_error;
    return m_output;
}

double Jath::QPID::getProportional()
{
    return m_error * m_error * m_kp * getSign(m_error);
}