#pragma once

#include <string>
#include "vex.h"

namespace Jath
{

    class jMotor : public vex::motor
    {
    public:
        jMotor(std::string name, vex::motor mot) : motor(mot) {}

        jMotor &withSpeedMode(bool speedMode)
        {
            m_speedMode = speedMode;
            return *this;
        }
        void setSpeedMode(bool speedMode) { m_speedMode = speedMode; }
        bool getSpeedMode() { return m_speedMode; }

        double get()
        {
            return m_cmd;
        }

        void set(double input)
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

    private:
        std::string m_name;

        double m_cmd{0};
        bool m_speedMode{false};
    };

    class jMotorGroup : public vex::motor_group
    {
    public:
        jMotorGroup(std::string name, vex::motor_group mot) : motor_group(mot) {}

        jMotorGroup &withSpeedMode(bool speedMode)
        {
            m_speedMode = speedMode;
            return *this;
        }
        void setSpeedMode(bool speedMode) { m_speedMode = speedMode; }
        bool getSpeedMode() { return m_speedMode; }

        double get()
        {
            return m_cmd;
        }

        void set(double input)
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

    private:
        std::string m_name;

        double m_cmd{0};
        bool m_speedMode{false};
    };

}