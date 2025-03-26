#include "ART/HolonomicDrive.h"
#include <cmath>
#include <algorithm>

namespace art
{
    HolonomicDrive::HolonomicDrive(SimpleMotorGroup leftFront, SimpleMotorGroup leftBack, SimpleMotorGroup rightFront, SimpleMotorGroup rightBack) :
    m_leftBack(leftBack), m_leftFront(leftFront), m_rightBack(rightBack), m_rightFront(rightFront)
    {
    }

    void HolonomicDrive::arcade(double x, double y, double rot)
    {
        m_cmdX = x;
        m_cmdY = y;
        m_cmdRot = rot;
        update();
    }

    void HolonomicDrive::LeftSplitArcade(const vex::controller &cont)
    {
        arcade(cont.Axis4.position(), cont.Axis3.position(), cont.Axis1.position());
        update();
    }
    void HolonomicDrive::LeftSplitArcadeCurved(const vex::controller &cont)
    {
        arcade(
            cont.Axis4.position() * cont.Axis4.position() * cont.Axis4.position() * 0.01 * 0.01,
            cont.Axis3.position() * cont.Axis3.position() * cont.Axis3.position() * 0.01 * 0.01,
            cont.Axis1.position() * cont.Axis1.position() * cont.Axis1.position() * 0.01 * 0.01);
        update();
    }

    void HolonomicDrive::update()
    {
        m_leftFront.set(
            m_cmdY + m_cmdRot
            -m_cmdX 
        );
        m_leftBack.set(
            m_cmdY + m_cmdRot
            +m_cmdX 
        );
        m_rightFront.set(
            m_cmdY - m_cmdRot
            +m_cmdX 
        );
        m_rightBack.set(
            m_cmdY - m_cmdRot
            -m_cmdX 
        );
    }
} // namespace art
