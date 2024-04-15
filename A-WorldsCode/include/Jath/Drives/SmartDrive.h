#pragma once

#include "vex.h"

#include "Jath/Drives/TankDrive.h"
#include "Jath/Vec2.h"
#include "Jath/Units.h"
#include "Jath/Utils.h"

// extern vex::gps GPS;
namespace Jath
{

    class SmartDrive : public TankDrive
    {
    public:
        Vec2 m_pos;
        Angle m_dir;

        SmartDrive(TankDrive drive, vex::inertial inert);

        SmartDrive& withWheelSize(Distance size);
        SmartDrive& withGearRatio(double ratio);

        int track();

        void driveTo(Distance target);
        void turnTo(Angle target);

        Distance driveToPoint(Vec2 target);

        Angle shortestTurnPath(Angle target);

        vex::inertial m_inert;

    private:
        Distance m_wheelSize {2.75};//stored as diameter
        double m_gearRatio {1.0};//output/input
    };

}