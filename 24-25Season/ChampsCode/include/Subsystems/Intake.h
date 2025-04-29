#pragma once

#include "Subsystems/Subsystem.h"
#include "ART/SimpleMotorGroup.h"
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

    Intake(vex::motor_group mot, vex::optical opt);

    void periodic();
    void handleInput(double input);

    void setState(IntakeState state);
    IntakeState getState();
    void setContinousSorting();
    void resetDelay();
    void resetDelay(double time);

    void setAntiJam(bool runningAntiJam);
    bool getAntiJam();

    art::SimpleMotorGroup& getMotor();

private:
    double m_input_cmd{0.0};
    double m_cmd{0.0};

    art::TimePoint m_startTime;
    art::TimePoint m_startMovingTime;
    double m_delay{0.0};
    double timePassed();
    double timeMoving();

    IntakeState m_state{CONTROL};

    IntakeState m_lastState{CONTROL};
    bool m_runningAntijam{false};
    bool m_continousSorting{false};

    art::SimpleMotorGroup m_motor;
    vex::optical m_optical;
};
