#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Backpack_Master

vex::motor armDeployMotor(
    vex::PORT15,
    vex::gearSetting::ratio18_1,
    false
);

vex::message_link link( vex::PORT18, "linkA", vex::linkType::manager );

#endif
