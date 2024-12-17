#include "Jath\Motors\jMotorGroup.h"

namespace Jath
{

    jMotorGroup::jMotorGroup(std::string name, vex::motor_group mot) : vex::motor_group(mot), m_name(name)
    {
        m_name = name;
        // Jath::Angle m_lastAngle = Jath::Angle(0);
        // Jath::Angle m_travel = Jath::Angle(0);
    }

    std::string jMotorGroup::getName() { return m_name; }

    jMotorGroup &jMotorGroup::withSpeedMode(bool speedMode)
    {
        m_speedMode = speedMode;
        return *this;
    }
    void jMotorGroup::setSpeedMode(bool speedMode) { m_speedMode = speedMode; }
    bool jMotorGroup::getSpeedMode() { return m_speedMode; }

    double jMotorGroup::get()
    {
        return m_cmd;
    }

    void jMotorGroup::set(double input)
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

    Jath::Angle jMotorGroup::travel()
    {
        Jath::Angle currentAngle = Degrees(position(vex::degrees));
        
        m_travel = Angle(currentAngle - m_lastAngle);
        m_lastAngle = currentAngle;

        return m_travel;
    }
    Jath::Angle jMotorGroup::getTravel() { return m_travel; }
} // namespace Jath
