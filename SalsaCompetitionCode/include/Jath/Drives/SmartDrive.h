#pragma once

#include "vex.h"
#include <memory>

#include "Jath/Drives/TankDrive.h"
#include "Jath/Vec2.h"
#include "Jath/Units.h"
#include "Jath/Utils.h"
#include "Jath\Graph.h"

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
            HorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio, Distance wheelOffset);

            Jath::Distance getTravel();

            std::shared_ptr<vex::rotation> m_rotation{nullptr};
            Distance m_wheelSize{2.75}; // stored as diameter
            double m_gearRatio{1.0};    // output/input

            Angle m_lastAngle = Angle(0);
            Angle m_travelAngle = Angle(0);
            Distance m_travelDistance = Distance(0);

            Distance m_offset = Distance(0);
            };

        Vec2 m_pos;
        Vec2 m_centerPos;
        Angle m_dir;

        SmartDrive(TankDrive drive, vex::inertial inert);

        SmartDrive &withWheelSize(Distance size);
        SmartDrive &withGearRatio(double ratio);

        SmartDrive &withHorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio);
        SmartDrive &withHorizontalTracker(vex::rotation rotation, Distance wheelSize, double gearRatio, Distance wheelOffset);

        int track();

        void driveTo(Distance target);Graph driveToGraph;

        void turnTo(Angle target);Graph turnToGraph;

        void driveToHoldAngle(Distance target);

        void turnToPoint(Vec2 target);

        Distance driveToPoint(Vec2 target);
        void driveToPointStoopid(Vec2 target);

        void driveToPointTuned(Vec2 target, double settleRange = Inches(2), double totalTimeout = 6);

        Distance driveTowardPoint(Vec2 target, double speedCap, bool clear = false);Graph driveTowardPointGraph;

        void turnToPointR(Vec2 target);

        Distance driveToPointR(Vec2 target);
        void driveToPointStoopidR(Vec2 target);
        void driveToPointTunedR(Vec2 target, double settleRange = Inches(2), double totalTimeout = 6);

        Angle shortestTurnPath(Angle target);

        vex::inertial m_inert;

        HorizontalTracker m_tracker;

        Distance getWheelTravel();

    private:
        Distance m_wheelSize{2.75}; // stored as diameter
        double m_gearRatio{1.0};    // output/input
    };

}