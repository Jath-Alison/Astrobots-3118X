#pragma once

#include <string>
#include <iostream>
#include "vex.h"
#include "Jath\Units.h"

namespace Jath
{

    class jMotorGroup : public vex::motor_group
    {
    public:
        jMotorGroup(std::string name, vex::motor_group mot);

        std::string getName();

        jMotorGroup &withSpeedMode(bool speedMode);
        void setSpeedMode(bool speedMode);
        bool getSpeedMode();

        double get();

        void set(double input);

        Jath::Angle travel();
        Jath::Angle getTravel();

    private:
        std::string m_name = "motor";

        double m_cmd{0};
        bool m_speedMode{false};

        Jath::Angle m_lastAngle = Jath::Angle(0);
        Jath::Angle m_travel = Jath::Angle(0);
    };

}
