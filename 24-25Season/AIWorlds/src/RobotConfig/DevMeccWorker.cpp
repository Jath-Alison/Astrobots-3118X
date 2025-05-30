#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Mecc_Worker

vex::message_link link( vex::PORT17, "linkA", vex::linkType::worker );

vex::inertial inert (vex::PORT8);

vex::motor mot_lf_a(vex::PORT20, !true);
vex::motor mot_lf_b(vex::PORT19, !false);
vex::motor mot_lb_a(vex::PORT10, !true);
vex::motor mot_lb_b(vex::PORT9, !false);
vex::motor mot_rf_a(vex::PORT11, !false);
vex::motor mot_rf_b(vex::PORT12, !true);
vex::motor mot_rb_a(vex::PORT1, !false);
vex::motor mot_rb_b(vex::PORT2, !true);

art::SimpleMotorGroup mot_lf(vex::motor_group(mot_lf_a, mot_lf_b));
art::SimpleMotorGroup mot_lb(vex::motor_group(mot_lb_a, mot_lb_b));
art::SimpleMotorGroup mot_rf(vex::motor_group(mot_rf_a, mot_rf_b));
art::SimpleMotorGroup mot_rb(vex::motor_group(mot_rb_a, mot_rb_b));

// art::HolonomicDrive holoDrive(
//   art::SimpleMotorGroup(vex::motor_group(mot_lf_a, mot_lf_b)),
//   art::SimpleMotorGroup(vex::motor_group(mot_lb_a, mot_lb_b)),
//   art::SimpleMotorGroup(vex::motor_group(mot_rf_a, mot_rf_b)),
//   art::SimpleMotorGroup(vex::motor_group(mot_rb_a, mot_rb_b))
// );
#endif
