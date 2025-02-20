#pragma once

#include "Subsystems/Subsystem.h"
#include "ART/SmartDrive.h"
#include "Logging/Logging.h"
#include "ART/Jath/Path.h"

class AsyncDrive : public Subsystem, public art::TankDrive
{
public:
    enum DriveState
    {
        WAIT,
        CONTROL,
        DRIVE,
        TURN,
        DRIVE_HEADING_CORRECTED,
        SWING_ABOUT_LEFT,
        SWING_ABOUT_RIGHT,
        PATH,

    };

    AsyncDrive(art::TankDrive drive, vex::inertial inert);

    AsyncDrive &withWheelSize(art::Length size);
    AsyncDrive &withGearRatio(double ratio);
    AsyncDrive &withDefaultPIDs(art::PID drivePid, art::PID turnPid);
    AsyncDrive &withHorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio);
    AsyncDrive &withHorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio, art::Length wheelOffset);

    void setXFlip(bool flip);
    void setYFlip(bool flip);

    int track();
    bool isCalibrating();

    void setPos(art::Vec2 pos);

    art::Angle getDir();
    art::Vec2 getPos();
    art::Vec2 getCenterPos();
    art::Vec2 getVel();

    void handleInputs(double drive, double rot);
    void setState(DriveState state);

    void periodic();

    //Auto functions

    void driveForA(art::Length target);
    void driveForA(art::Length target, art::PID pid);
    void driveForS(art::Length target);
    void driveForS(art::Length target, art::PID pid);

    void turnToA(art::Angle target);
    void turnToA(art::Angle target, art::PID pid);
    void turnToS(art::Angle target);
    void turnToS(art::Angle target, art::PID pid);

    void driveForHeadingCorrectedA(art::Length target, art::Angle heading);
    void driveForHeadingCorrectedA(art::Length target, art::Angle heading, art::PID drivePID, art::PID turnPID);
    void driveForHeadingCorrectedS(art::Length target, art::Angle heading);
    void driveForHeadingCorrectedS(art::Length target, art::Angle heading, art::PID drivePID, art::PID turnPID);

    void followPathA(Jath::Path p);
    void followPathA(Jath::Path p, art::Length lookahead);
    void followPathA(Jath::Path p, art::Length lookahead, art::PID turnPID);
    void followPathS(Jath::Path p);
    void followPathS(Jath::Path p, art::Length lookahead);
    void followPathS(Jath::Path p, art::Length lookahead, art::PID turnPID);

    bool driveComplete();
    bool turnComplete();
    bool pathComplete();

    double driveError();
    double turnError();

    void setDriveTarget(art::Length target);
    void setTurnTarget(art::Angle target);

    void zeroGyro();

// private:
    DriveState m_state{CONTROL};

    bool m_flipX{false};
    bool m_flipY{false};

    art::Angle m_driveTarget;
    art::Angle m_driveOffset;
    art::Angle m_turnTarget;

    Jath::Path m_path;
    art::Length m_lookaheadDist = art::Inches(10);

    Jath::Point m_lookahead;
    Jath::Point m_closest;

    double drive_input{0.0};
    double rot_input{0.0};

    art::PID m_drivePID;
    art::PID m_turnPID;

    art::Vec2 m_pos;
    art::Vec2 m_centerPos;
    art::Angle m_dir;
    vex::inertial m_inert;
    art::Length m_wheelSize{art::Inches(3.25)};
    double m_gearRatio{1.0};
    art::Angle getLeftTravel();
    art::Angle m_LastLeftPos;
    art::Angle getRightTravel();
    art::Angle m_LastRightPos;
    art::Vec2 m_vel;           // per second
    art::Angle m_rotVel;       // per second
    art::Length m_leftTravel;  // per second
    art::Length m_rightTravel; // per second

    art::Length getWheelTravel();

    struct HorizontalTracker
    {
        HorizontalTracker();

        HorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio);
        HorizontalTracker(vex::rotation rotation, art::Length wheelSize, double gearRatio, art::Length wheelOffset);

        art::Length getTravel();

        std::shared_ptr<vex::rotation> m_rotation{nullptr};
        art::Length m_wheelSize{art::Inches(2.75)};
        double m_gearRatio{1.0};

        art::Angle m_lastAngle = art::Angle(0);
        art::Angle m_travelAngle = art::Angle(0);
        art::Length m_travelDistance = art::Length(0);
        art::Length m_offset = art::Length(0);
    };

    HorizontalTracker m_tracker;
};
