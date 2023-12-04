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
        m_inert.calibrate();
    }

    int SmartDrive::track()
    {
        while(m_inert.isCalibrating()){vex::wait(5, vex::msec);}
        int count = 0;
        while(true){
            count ++;
            if(count > 200){
                // m_pos = XandY( GPS.xPosition(vex::inches), GPS.yPosition(vex::inches) );
                // m_inert.setHeading(GPS.yaw(vex::deg), vex::deg);
                count = 0;
            };
            static double prev = 0;
            m_dir = Degrees(m_inert.heading(vex::degrees));
            double change = ((m_left.position(vex::degrees) - m_right.position(vex::degrees))/2.f) - prev;

            Distance travel = Inches(change*((3.25 * 3.1415)/360.f) / (72.f/48.f));
            Vec2 posChange = dirAndMag(m_dir,travel);

            m_pos = m_pos + posChange;

            prev = (m_left.position(vex::degrees) - m_right.position(vex::degrees))/2.f;
            // std::cout << posChange.x << ", " << posChange.y << ", " << std::endl;
            // std::cout << "\ttravel: " << travel.inches() << std::endl;

        vex::wait(20, vex::msec);
        }
    }

    void SmartDrive::driveTo(Distance target)  
    {
        double offset = (m_left.position(vex::degrees) - m_right.position(vex::degrees))/2.f;
        double deg = target.inches()/(3.25 * 3.1415) * 360 * (72.f/48.f);
        double error = deg - (((m_left.position(vex::degrees) - m_right.position(vex::degrees))/2.f) - offset);
        int count = 0;

        double i = 0;
        double prevError;
        
        while(count < 20){
            error = deg - (((m_left.position(vex::degrees) - m_right.position(vex::degrees))/2.f) - offset);
            double speed = error*0.25;
            // if(abs(speed) > 50){speed*=.25;} else {speed *= 0.25;}
            if(abs(error) < 100){i += error;} else {i=0;}
            speed += i*.025;
            arcade(0, speed + .5 * (error - prevError), 0);
            if(abs(error) < 5){count++;}else{count = 0;}
            prevError = error;
            std::cout << "error: " << error << "\n";
            std::cout << "speed: " << speed << "\n" << std::endl;
            wait(20, vex::msec);
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
            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    Distance SmartDrive::driveToPoint(Vec2 target)
    {
        Angle angle = Angle(m_pos.angleTo(target) - m_dir);
        // angle = Angle(shortestTurnPath(angle));
        Distance dist = m_pos.distTo(target);

        std::cout << "pos: " << Distance (m_pos.x).tiles() << "," << Distance (m_pos.y).tiles() << "\n";
        std::cout << "target: " << target.x << "," << target.y << "\n";
        std::cout << "target angle: " << m_pos.angleTo(target) << "\n";
        std::cout << "distance: " << dist.inches() << "\n\n";

        arcade(0,dist.inches() * 3, angle.degrees()*.5);
        update();
        return dist;
    }
    Angle SmartDrive::shortestTurnPath(Angle target)
    {
        Angle angle = target;
        if (abs(angle.revolutions()) < .5) {
            return angle;
        }	else {
            if(angle.revolutions() > 0){
                return Revolutions(1 - angle.revolutions());
            }else{
                return Revolutions(1 + angle.revolutions());
            }
        }
        return Angle();
    }
}