#pragma once
#include <cmath>
#include <chrono>
#include <sstream>

namespace Jath
{

    class PID
    {
    public:
        PID();
        // PID(double kp, double ki, double kd);
        // PID(double kp, double ki, double kd, double ff);

        void reset();

        std::string str();

        void setConstants(double kp, double ki, double kd);
        PID &withConstants(double kp, double ki, double kd);
        void setConstants(double kp, double ki, double kd, double ff);
        PID &withConstants(double kp, double ki, double kd, double ff);

        double getkp() { return m_kp; }
        double getki() { return m_ki; }
        double getkd() { return m_kd; }
        double getff() { return m_ff; }

        void setIntegralZone(double integralZone);
        PID &withIntegralZone(double integralZone);

        void setTimeout(double timeout);
        PID &withTimeout(double timeout);

        void setSettleZone(double settleZone);
        PID &withSettleZone(double settleZone);

        void setSettleTimeout(double settleTimeout);
        PID &withSettleTimeout(double settleTimeout);

        virtual double calculate(double error);
        double calculate(double target, double feedback);

        bool isCompleted();

        double timePassed();
        double settledTimePassed();

        virtual double getProportional();
        double getIntegral();
        double getDerivative();

    protected:
        double m_error{0};
        double m_prevError{0};

        double m_derivative{0};

        double m_integral{0};
        double m_integralZone{0};

        double m_output{0};

        double m_kp{0};
        double m_ki{0};
        double m_kd{0};
        double m_ff{0};

        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
        double m_timeout{0};

        std::chrono::time_point<std::chrono::high_resolution_clock> m_startSettledTime;
        double m_settleTimeout{0};
        double m_settleZone{0};
    };
} // namespace Jath