#pragma once

#include <string>
#include <iostream>
#include "vex.h"
#include "Jath\Units.h"

namespace Jath
{

    class jMotor : public vex::motor
    {
    public:
        jMotor(std::string name, vex::motor mot);

        std::string getName();

        jMotor &withSpeedMode(bool speedMode);
        void setSpeedMode(bool speedMode);
        bool getSpeedMode();

        double get();

        void set(double input);

        // Jath::Angle travel()
        // {
        //     Jath::Angle currentAngle = Degrees(position(vex::degrees));

        //     m_travel = m_lastAngle - currentAngle;
        //     m_lastAngle = currentAngle;
        // }
        // Jath::Angle getTravel() { return m_travel; }

    private:
        std::string m_name = "motor";

        double m_cmd{0};
        bool m_speedMode{false};

        // Jath::Angle m_lastAngle = Jath::Angle(0);
        // Jath::Angle m_travel = Jath::Angle(0);
    };

}