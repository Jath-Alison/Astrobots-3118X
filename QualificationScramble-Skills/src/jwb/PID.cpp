#include "jwb\PID.h"

namespace jwb{

    PID::PID()
        : m_startTime( std::chrono::high_resolution_clock::now() )
    {
        setConstants(1, 0, 0, 0);
        m_startTime = std::chrono::high_resolution_clock::now();
        m_startSettledTime = std::chrono::high_resolution_clock::now();
    }

    PID::PID(double kp, double ki, double kd)
    {
        setConstants(kp, ki, kd, m_ff);
        PID();
    }
    PID::PID(double kp, double ki, double kd, double ff)
    {
        setConstants(kp, ki, kd, ff);
        PID();
    }

    void PID::reset()
    {
        m_error = 0;
        m_prevError = 0;

        m_derivative = 0;
        m_integral = 0;

        m_startTime = std::chrono::high_resolution_clock::now();
        m_startSettledTime = std::chrono::high_resolution_clock::now();
    }

    void PID::setConstants(double kp, double ki, double kd)
    {
        m_kp = kp;
        m_ki = ki;
        m_kd = kd;
    }
    PID& PID::withConstants(double kp, double ki, double kd){setConstants(kp, ki, kd); return *this;}
    void PID::setConstants(double kp, double ki, double kd, double ff)
    {
        m_kp = kp;
        m_ki = ki;
        m_kd = kd;
        m_ff = ff;
    }
    PID& PID::withConstants(double kp, double ki, double kd, double ff){setConstants(kp, ki, kd, ff); return *this;}

    void PID::setIntegralZone(double integralZone){ m_integralZone = integralZone; }
    PID& PID::withIntegralZone(double integralZone){ setIntegralZone( integralZone ); return *this; }

    void PID::setTimeout(double timeout){ m_timeout = timeout; }
    PID& PID::withTimeout(double timeout){ setTimeout( timeout ); return *this; }

    void PID::setSettleZone(double settleZone){ m_settleZone = settleZone; }
    PID& PID::withSettleZone(double settleZone){ setSettleZone( settleZone ); return *this; }

    void PID::setSettleTimeout(double settleTimeout) { m_settleTimeout = settleTimeout; }
    PID& PID::withSettleTimeout(double settleTimeout){ setSettleTimeout( settleTimeout ); return *this; }


    double PID::calculate(double error){
        m_error = error;
        m_derivative = m_prevError - m_error;

        if( std::abs(m_error) < m_integralZone ){
            m_integral += m_error;   
        }else {
            m_integral = 0;
        }
        if ( (m_error > 0 && m_prevError < 0) || (m_error < 0 && m_prevError > 0) ){
            m_integral = 0; 
        }

        if( std::abs(error) > m_settleZone ){
            m_startSettledTime = std::chrono::high_resolution_clock::now();
        }

        m_output = (m_kp * m_error) + (m_kd * m_derivative) + (m_ki * m_integral) + m_ff;

        m_prevError = m_error; 
        return m_output;
    }
    double PID::calculate(double target, double feedback){
        return calculate(target - feedback);
    }

    bool PID::isCompleted()
    {
        if( timePassed() > m_timeout && m_timeout != 0 ) { return true; }
        if( settledTimePassed() > m_settleTimeout && m_settleTimeout != 0 ) { return true; }
        return false;
    }

    double PID::timePassed()
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startTime).count()/1000.f;
    }

    double PID::settledTimePassed()
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_startSettledTime).count()/1000.f;
    }
}