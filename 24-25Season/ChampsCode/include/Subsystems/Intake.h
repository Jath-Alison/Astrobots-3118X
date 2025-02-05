#pragma once

#include "Subsystems/Subsystem.h"
#include "ART/SimpleMotor.h"
#include "ART/PID.h"

class Intake : public Subsystem
{
public:
    enum IntakeState{
        CONTROL,
        REJECT_RED,
        REJECT_BLUE,
        STOP_RED,
        STOP_BLUE,
        DELAY_OFF,
        DELAY_ON
    };

    Intake(vex::motor mot, vex::optical opt);

    void periodic();
    void handleInput(double input);

    void setState(IntakeState state);
    void resetDelay();
    void resetDelay(double time);

private:
    double m_input_cmd{0.0};
    double m_cmd{0.0};

    art::TimePoint m_startTime;
    double m_delay{0.0};
    double timePassed();

    IntakeState m_state{CONTROL};

    art::SimpleMotor m_motor;
    vex::optical m_optical;
};
