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
        DELAY_ON,
        ANTI_JAM_REVERSE
    };

    Intake(vex::motor mot, vex::optical opt);

    void periodic();
    void handleInput(double input);

    void setState(IntakeState state);
    void resetDelay();
    void resetDelay(double time);

    void setAntiJam(bool runningAntiJam);
    bool getAntiJam();

private:
    double m_input_cmd{0.0};
    double m_cmd{0.0};

    art::TimePoint m_startTime;
    double m_delay{0.0};
    double timePassed();

    IntakeState m_state{CONTROL};

    IntakeState m_lastState{CONTROL};
    bool m_runningAntijam{false};

    art::SimpleMotor m_motor;
    vex::optical m_optical;
};
