#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Backpack_Master

art::SimpleMotor armDeployMotor(vex::motor(
    vex::PORT2,
    vex::gearSetting::ratio18_1,
    false
));

vex::message_link link( vex::PORT1, "linkA", vex::linkType::manager);

#endif
