#include "Jath\Motors\jMotor.h"

namespace Jath
{

    jMotor::jMotor(std::string name, vex::motor mot) : vex::motor(mot), m_name(name)
    {
        m_name = name;
    }

    std::string jMotor::getName() { return m_name; }

    jMotor &jMotor::withSpeedMode(bool speedMode)
    {
        m_speedMode = speedMode;
        return *this;
    }
    void jMotor::setSpeedMode(bool speedMode) { m_speedMode = speedMode; }
    bool jMotor::getSpeedMode() { return m_speedMode; }

    double jMotor::get()
    {
        return m_cmd;
    }

    void jMotor::set(double input)
    {
        m_cmd = input;
        if (m_speedMode)
        {
            spin(vex::fwd, m_cmd, vex::pct);
        }
        else
        {
            spin(vex::fwd, m_cmd * 12 / 100.f, vex::volt);
        }
    }

        
} // namespace Jath
