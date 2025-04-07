/**
 * @file SmarterDrive.h
 * @author Jath Alison (Jath.Alison@gmail.com)
 * @brief Header containing the SmarterDrive class
 * @version 1.0-beta
 * @date 09-01-2024
 *
 * @copyright Copyright (c) 2024
 *
 * This is the header that needs to be included to use the SmarterDrive
 * class. The class aims to package more complex base controls, making it
 * easier to write autos by providing consistant high-level controls for
 * more complex tasks.
 */
#pragma once

#include "ART/Vec2.h"
#include "ART/PID.h"
#include "ART/Units.h"
#include "ART/HolonomicDrive.h"

#include <memory>
#include <cmath>
#include <vector>

namespace art
{

    class SmarterDrive : public HolonomicDrive
    {
    public:
        SmarterDrive(HolonomicDrive drive, vex::inertial inert);

        SmarterDrive &withWheelSize(Length size);
        SmarterDrive &withGearRatio(double ratio);

        // SmarterDrive &withHorizontalTracker(vex::rotation rotation, Length wheelSize, double gearRatio);
        // SmarterDrive &withHorizontalTracker(vex::rotation rotation, Length wheelSize, double gearRatio, Length wheelOffset);

        int track();

        
        void driveFor(Length target, double speed);
        void driveForPID(Length target);
        bool driveTowardPID(Length target, bool reset);
        PID m_driveForPID;
        SmarterDrive &withDriveForPID(PID pid);

        void turnFor(Angle target, double speed);
        void turnForPID(Angle target);
        PID m_turnForPID;
        SmarterDrive &withTurnForPID(PID pid);

        void turnTo(Angle target, double speed);
        void turnToPID(Angle target);
        bool turnTowardPID(Angle target, bool reset);
        PID m_turnToPID;
        SmarterDrive &withTurnToPID(PID pid);

        Length getWheelTravel();

    private:
        struct Tracker
        {
            Tracker();

            Tracker(vex::rotation rotation, Length wheelSize, double gearRatio);
            Tracker(vex::rotation rotation, Length wheelSize, double gearRatio, Length wheelOffset);

            Length getTravel();

            std::shared_ptr<vex::rotation> m_rotation{nullptr};
        
            Length m_wheelSize{Inches(2.75)};

            double m_gearRatio{1.0};

            Angle m_lastAngle{0};
            Angle m_travelAngle{0};
            Length m_travelDistance{0};

            Length m_offset{0};
        };

        std::vector<Tracker> m_trackers;

        Vec2 m_pos;
        Angle m_dir;

        vex::inertial m_inert;

        Length m_wheelSize{Inches(2.0)};
        double m_gearRatio{1.0};

        Angle getLeftTravel();
        Angle m_LastLeftPos;

        Angle getRightTravel();
        Angle m_LastRightPos;

        Vec2 m_vel;// per second
        Angle m_rotVel;// per second

        Length m_leftTravel;// per second
        Length m_rightTravel;// per second

    };

} // namespace art
