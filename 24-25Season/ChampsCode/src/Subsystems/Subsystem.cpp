#include "Subsystems/Subsystem.h"
#include "RobotConfig.h"

std::vector<Subsystem *> Subsystem::m_subsystems = {};

void Subsystem::periodicAll()
{
    for (size_t i = 0; i < m_subsystems.size(); i++)
    {
        m_subsystems[i]->periodic();
    }
}

vex::thread periodicThread;
int periodicLoop()
{
    while(true){
        intake.periodic();
		arm.periodic();

        vex::wait(10, vex::msec);
    }
    return 0;
}