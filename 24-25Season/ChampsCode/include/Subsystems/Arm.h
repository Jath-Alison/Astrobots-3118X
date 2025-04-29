#pragma once

#include "Subsystems/Subsystem.h"
#include "ART/SimpleMotorGroup.h"
#include "ART/PID.h"
#include "ART/Units.h"

class Arm : public Subsystem
{
public:
    enum ArmState{
        CONTROL,
        POSITION
    };

    Arm(vex::motor_group mot, art::PID pid);

    void periodic();
    void handlePosInput(art::Angle input);
    void handleCmdInput(double input);

    void setState(ArmState state);

    bool isComplete();

    art::SimpleMotorGroup& getMotor();
    art::Angle getPosCmd();

private:
    double m_cmd{0.0};
    art::Angle m_pos_cmd{0.0};
    double m_output{0.0};

    ArmState m_state{CONTROL};

    art::PID m_pid;

    art::SimpleMotorGroup m_motor;
};
