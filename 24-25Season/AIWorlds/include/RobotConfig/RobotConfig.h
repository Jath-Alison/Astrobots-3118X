#pragma once
#include "RobotSelect.h"

#if CURRENT_ROBOT == Backpack_Red
    #include "RobotConfig/BackpackRed.h"
#elif CURRENT_ROBOT == Backpack_Blue
    #include "RobotConfig/BackpackBlue.h"
#elif CURRENT_ROBOT == Dora
    #include "RobotConfig/Dora.h"
#elif CURRENT_ROBOT == Dev_Backpack_Master
    #include "RobotConfig/DevBackpackMaster.h"
#elif CURRENT_ROBOT == Dev_Mecc_Worker
    #include "RobotConfig/DevMeccWorker.h"
#endif