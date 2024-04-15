#include "Jath\Drives\SmartDrive.h"
#include <iostream>

namespace Jath{

    SmartDrive::SmartDrive(TankDrive drive, vex::inertial inert) : TankDrive(drive), m_inert(inert)
    {
        m_inert.calibrate();
    }

    SmartDrive &SmartDrive::withWheelSize(Distance size)
    {
        m_wheelSize = size;
        return *this;
    }

    SmartDrive &SmartDrive::withGearRatio(double ratio)
    {
        m_gearRatio = ratio;
        return *this;
    }

    int SmartDrive::track()
    {
        while(m_inert.isCalibrating()){vex::wait(5, vex::msec);}

        while(true){

            m_dir = Degrees(m_inert.heading(vex::degrees));

            Jath::Angle wheelTravel = (m_left.travel() + m_right.travel()) / 2.0;
            Jath::Distance travel = wheelTravel * (m_wheelSize/2.0) * m_gearRatio;

            // Distance travel = Inches(change*((3.25 * 3.1415)/360.f) / (72.f/48.f));
            Vec2 posChange = dirAndMag(m_dir,travel);

            m_pos = m_pos + posChange;


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
            // if(std::abs(speed) > 50){speed*=.25;} else {speed *= 0.25;}
            if(std::abs(error) < 100){i += error;} else {i=0;}
            speed += i*.025;
            arcade(0, speed + .5 * (error - prevError), 0);
            if(std::abs(error) < 5){count++;}else{count = 0;}
            prevError = error;
            // std::cout << "error: " << error << "\n";
            // std::cout << "speed: " << speed << "\n" << std::endl;
            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    void SmartDrive::turnTo(Angle target)
    {
        bool running = true;
        int count = 0;
        Angle prev;
        while(running){
            Angle error = shortestTurnPath(Jath::Degrees(target.degrees() - m_inert.heading(vex::degrees)) );
            double speed = error.degrees()*0.5;
            if(std::abs(speed) > 50){speed*=.25;} else {speed *= 0.5;}
            if(Angle(prev - error).degrees() < 5){speed*=2.5;}
            arcade(0, 0, speed + getSign(error.degrees())*20);
            if(std::abs(error.degrees()) < 5){count++;}else{count = 0;}
            // std::cout << error.degrees() << ", " << count << std::endl;
            if(count > 20){running = false;}
            prev = error;
            wait(20, vex::msec);
        }
        arcade(0, 0, 0);
    }
    Distance SmartDrive::driveToPoint(Vec2 target)
    {
        Angle angle = Angle(m_pos.angleTo(target) - m_dir);
        // angle = Angle(shortestTurnPath(angle));
        Distance dist = m_pos.distTo(target);

        // std::cout << "pos: " << Distance (m_pos.x).tiles() << "," << Distance (m_pos.y).tiles() << "\n";
        // std::cout << "target: " << target.x << "," << target.y << "\n";
        // std::cout << "target angle: " << Radians(m_pos.angleTo(target)).degrees() << "\n";
        // std::cout << "distance: " << dist.inches() << "\n\n";

        if( std::abs(angle.degrees()) > 15){
            arcade(0,0 , angle.degrees());
        }else{
            arcade(0,dist.inches() * 5, angle.degrees());
        }
        update();
        return dist;
    }
    Angle SmartDrive::shortestTurnPath(Angle target)
    {
        Angle angle = target;
        if (std::abs(angle.revolutions()) < .5) {
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