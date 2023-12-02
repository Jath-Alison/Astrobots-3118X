#pragma once

#include "vex.h"

#include "x/TankDrive.h"
#include "x/Vec2.h"
#include "x/Units.h"

namespace x{

    class SmartDrive : public TankDrive {
    public:

        Vec2 m_pos;
        Angle m_dir;

        SmartDrive (TankDrive drive, vex::inertial inert); 

        int track();

        void driveTo(Distance target);  
        void turnTo(Angle target);

        void driveToPoint(Vec2 target);
    private:

        Angle shortestTurnPath(Angle target);

        vex::inertial m_inert;
    

    };

}