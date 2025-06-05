#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Backpack_Blue

art::SimpleMotor armDeployMotor(vex::motor(
    vex::PORT10,
    vex::gearSetting::ratio18_1,
    false
));

vex::message_link link( vex::PORT1, "linkA", vex::linkType::worker);

#endif
