#pragma once

#include <string>
#include "vex.h"

namespace x{

    class xMotor : public vex::motor{
    public:

        xMotor(std::string name,vex::motor mot): motor(mot){ }

        xMotor& withSpeedMode(bool speedMode){ m_speedMode = speedMode; return *this; }
        void setSpeedMode(bool speedMode){ m_speedMode = speedMode;}
        bool getSpeedMode() {return m_speedMode;}

        double get(){
            return m_cmd;
        }

        void set(double input){
        m_cmd = input;
        if( m_speedMode ) {
            spin(vex::fwd, m_cmd, vex::pct);
        } else {
            spin(vex::fwd, m_cmd * 12/100.f, vex::volt);
        }
        }

    private:

        std::string m_name;
        
        double m_cmd{0};
        bool m_speedMode{false};

    };
    
    class xMotorGroup : public vex::motor_group{
    public:

        xMotorGroup(std::string name,vex::motor_group mot): motor_group(mot){ }

        xMotorGroup& withSpeedMode(bool speedMode){ m_speedMode = speedMode; return *this; }
        void setSpeedMode(bool speedMode){ m_speedMode = speedMode;}
        bool getSpeedMode() {return m_speedMode;}

        double get(){
            return m_cmd;
        }

        void set(double input){
        m_cmd = input;
        if( m_speedMode ) {
            spin(vex::fwd, m_cmd, vex::pct);
        } else {
            spin(vex::fwd, m_cmd * 12/100.f, vex::volt);
        }
        }

    private:

        std::string m_name;
        
        double m_cmd{0};
        bool m_speedMode{false};

    };

}