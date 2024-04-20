#pragma once

#include "vex.h"
#include <memory>

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
        struct HorizontalTracker
        {
            HorizontalTracker();
            HorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio);

            Jath::Distance getTravel();

            std::shared_ptr<vex::rotation> m_rotation{nullptr};
            Distance m_wheelSize{2.75}; // stored as diameter
            double m_gearRatio{1.0};    // output/input

            Jath::Angle m_lastAngle = Jath::Angle(0);
            Jath::Angle m_travelAngle = Jath::Angle(0);
            Jath::Distance m_travelDistance = Jath::Distance(0);
        };

        Vec2 m_pos;
        Angle m_dir;

        SmartDrive(TankDrive drive, vex::inertial inert);

        SmartDrive &withWheelSize(Distance size);
        SmartDrive &withGearRatio(double ratio);

        SmartDrive &withHorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio);

        int track();

        void driveTo(Distance target);
        void turnTo(Angle target);

        Distance driveToPoint(Vec2 target);

        Angle shortestTurnPath(Angle target);

        vex::inertial m_inert;

        HorizontalTracker m_tracker;

        Distance getWheelTravel();

    private:
        Distance m_wheelSize{2.75}; // stored as diameter
        double m_gearRatio{1.0};    // output/input
    };

}