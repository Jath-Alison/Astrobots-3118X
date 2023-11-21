#pragma once

#include "vex.h"
#include "x/xMotor.h"

#include <string>
#include <map>

namespace x{

  class TankDrive{
    public:

      TankDrive(vex::motor_group left, vex::motor_group right) : m_left("leftDrive", left), m_right("rightDrive", right){}

      TankDrive& withScales(double x, double y, double rot){
        m_xScale = x; m_yScale = y; m_rotScale = rot; return *this;
      }
      void setScales(double x, double y, double rot){
        m_xScale = x; m_yScale = y; m_rotScale = rot;
      }

      void arcade(double x, double y, double rot){
        m_cmdX = x;
        m_cmdY = y;
        m_cmdRot = rot;
        update();
      };
      void LeftSplitArcade(const vex::controller& cont){
        arcade( 0, cont.Axis3.position(), cont.Axis1.position());
        update();
      };

      void update() {
        m_left.set(  (m_cmdY * m_yScale) + (m_cmdRot * m_rotScale));
        m_right.set(-(m_cmdY * m_yScale) + (m_cmdRot * m_rotScale));
      }

      
    protected:

      xMotorGroup m_left;
      xMotorGroup m_right;

      double m_cmdX{0};
      double m_cmdY{0};
      double m_cmdRot{0};

      double m_xScale{1};
      double m_yScale{1};
      double m_rotScale{1};

  };
}