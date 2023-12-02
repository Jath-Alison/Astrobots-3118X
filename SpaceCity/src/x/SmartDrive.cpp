#include "x\SmartDrive.h"
#include <iostream>

vex::gps GPS = vex::gps(vex::PORT14, -76.20, -127.00, vex::mm, 180);

namespace x{

    int getSign(double in){
        if (in<0){return -1;}
        if (in>0){return 1;}
        return 0;
    }

    SmartDrive::SmartDrive(TankDrive drive, vex::inertial inert) : TankDrive(drive), m_inert(inert)
    {
    }

    int SmartDrive::track()
    {
        int count = 0;
        while(true){
            count ++;
            if(count > 200){
                m_pos = XandY( GPS.xPosition(vex::inches), GPS.yPosition(vex::inches) );
                m_inert.setHeading(GPS.yaw(vex::deg), vex::deg);
                count = 0;
            };
            static double prev = 0;
            m_dir = Degrees(m_inert.heading(vex::degrees));
            double change = ((m_left.position(vex::degrees) + m_right.position(vex::degrees))/2.f) - prev;

            Distance travel = Inches( change*((3.25 * 3.1415)/360.f));
            travel = Inches(1);
            Vec2 posChange = dirAndMag(m_dir,travel.inches());

            m_pos = m_pos + posChange;

            prev = (m_left.position(vex::degrees) + m_right.position(vex::degrees))/2.f;
            // std::cout << posChange.x << ", " << posChange.y << ", " << std::endl;
            // std::cout << "  " << m_dir.degrees() << ", " << travel.inches() << std::endl;

        vex::wait(20, vex::msec);
        }
    }

    void SmartDrive::driveTo(Distance target)  
    {
        double offset = (m_left.position(vex::degrees) + m_right.position(vex::degrees))/2.f;
        m_right.setPosition(0, vex::deg);
        double deg = target.inches()/(3.25 * 3.1415) * 360;
        double error = deg - ((m_left.position(vex::degrees) + m_right.position(vex::degrees))/2.f) - offset;
        int count = 0;
        
        while(count < 20){
            error = deg - ((m_left.position(vex::degrees) + m_right.position(vex::degrees))/2.f) - offset;
            double speed = error*0.5;
            if(abs(speed) > 50){speed*=.25;} else {speed *= 0.25;}
            arcade(0, speed + getSign(error)*15, 0);
            if(abs(error) < 5){count++;}else{count = 0;}
            wait(0.05, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::turnTo(Angle target)
    {
        bool running = true;
        int count = 0;
        while(running){
            double error = target.degrees() - m_inert.yaw();
            double speed = error*0.5;
            if(abs(speed) > 50){speed*=.25;} else {speed *= 0.5;}
            arcade(0, 0, speed + getSign(error)*15);
            if(abs(error) < 5){count++;}else{count = 0;}
            if(count > 20){running = false;}
            wait(0.05, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::driveToPoint(Vec2 target)
    {
        Angle angle = m_pos.angleTo(target) - m_dir;
        angle = shortestTurnPath(angle);
        Distance dist = m_pos.distTo(target);

        arcade(0,dist.inches()*5, angle.degrees()*5);
        update();
    }
    Angle SmartDrive::shortestTurnPath(Angle target)
    {
        Angle angle = target;
        if (abs(angle.revolutions()) < .5) {
            return angle;
        }	else {
            return Revolutions(1 - angle.revolutions());
        }
        return Angle();
    }
}