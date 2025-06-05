#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Backpack_Red

art::SimpleMotor armDeployMotor(vex::motor(
    vex::PORT10,
    vex::gearSetting::ratio18_1,
    true
));

vex::message_link link( vex::PORT1, "linkA", vex::linkType::worker);

#endif
