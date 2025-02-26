/**
 * @file TankDrive.cpp
 * @author Jath Alison (Jath.Alison@gmail.com)
 * @brief Source containing the TankDrive class
 * @version 1.0-beta
 * @date 07-15-2024
 *
 * @copyright Copyright (c) 2024
 *
 * This is the source defining the TankDrive class. The
 * class aims to provide a wrapper for TankDrive base controls, making it easier
 * to write driver control code as well as autons by providing the low level
 * controls for more complex functions to use.
 */

#include "ART/TankDrive.h"
#include <cmath>
#include <algorithm>

namespace art
{
    TankDrive::TankDrive(vex::motor_group left, vex::motor_group right) : m_left(left), m_right(right) {}

    void TankDrive::arcade(double x, double y, double rot)
    {
        m_cmdX = x;
        m_cmdY = y;
        m_cmdRot = rot;
        update();
    }
    void TankDrive::arcade(double drive, double rot)
    {
        m_cmdY = drive;
        m_cmdRot = rot;
        update();
    }
    void TankDrive::tank(double left, double right)
    {
        m_cmdY = left + right;
        m_cmdRot = left - right;
        update();
    }

    void TankDrive::LeftSplitArcade(const vex::controller &cont)
    {
        arcade(cont.Axis3.position(), cont.Axis1.position());
        update();
    }
    void TankDrive::LeftSplitArcadeCurved(const vex::controller &cont)
    {
        arcade(cont.Axis3.position() * cont.Axis3.position() * cont.Axis3.position() * 0.01 * 0.01,
               cont.Axis1.position() * cont.Axis1.position() * cont.Axis1.position() * 0.01 * 0.01);
        update();
    }
    void TankDrive::curvatureDrive(double iThrottle, double iCurvature, double iThreshold)
    {
        if (std::fabs(iThrottle) <= iThreshold)
        {
            arcade(0, iCurvature);
            return;
        }

        iThrottle = std::fabs(iThrottle) > iThreshold ? iThrottle : 0;
        iCurvature = std::fabs(iCurvature) > iThreshold ? iCurvature : 0;

        double left = iThrottle + (std::fabs(iThrottle/100.0) * iCurvature);
        double right = iThrottle - (std::fabs(iThrottle/100.0) * iCurvature);

        double mag = std::max(std::fabs(left), std::fabs(right));
        if (mag > 100.0)
        {
            left /= mag;
            left *= 100.0;
            right /= mag;
            right *= 100.0;
        }

        m_left.set(left);
        m_right.set(right);
    }
    void TankDrive::update()
    {
        m_left.set(m_cmdY + m_cmdRot);
        m_right.set(m_cmdY - m_cmdRot);
    }
} // namespace art
