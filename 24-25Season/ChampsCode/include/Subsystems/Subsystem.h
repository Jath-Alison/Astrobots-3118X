#pragma once
#include <vector>
#include "vex.h"

class Subsystem
{
public:
    virtual void periodic() = 0;

    static void periodicAll();

private:
    static std::vector<Subsystem *> m_subsystems;
};

extern vex::thread periodicThread;
int periodicLoop();