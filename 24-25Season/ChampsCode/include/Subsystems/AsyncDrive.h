#pragma once

#include "Subsystems/Subsystem.h"
#include "ART/SmartDrive.h"
#include "Logging/Logging.h"

class AsyncDrive : public Subsystem
{
public:
    enum DriveState{
        CONTROL,
        DRIVE,
        DRIVE_HEADING_CORRECTED,
        TURN,
        PATH,

    };

    AsyncDrive(art::SmartDrive& drive);

    void handleInputs(double drive, double rot);
    void setState(DriveState state);

    void periodic();

    bool driveComplete();
    bool turnComplete();

    double driveError();
    double turnError();

    void setDriveTarget(art::Length target);
    void setTurnTarget(art::Angle target);

private:
    DriveState m_state{CONTROL};
    
    art::Angle m_driveTarget;
    art::Angle m_driveOffset;
    art::Angle m_turnTarget;

    art::SmartDrive& m_smartDrive;

    double drive_input{0.0};
    double rot_input{0.0};
};
