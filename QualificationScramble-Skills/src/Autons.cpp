#include "Autons.h"

int updateMotorsTask(){
    for (;;){
        jwb::SmartMotor::updateAllMotors();
    }
}

void Skills(){

    Intake = -50;
    wait(0.25,vex::sec);
    Intake = 0;

    arcadeFor(50,-15, 0.5);

    Flywheel.set(-100);
    wait(30, vex::seconds);//launching 30
    Flywheel.set(0);

    arcade(-30,0);
    wait(20, vex::msec);
    turnTo(jwb::Degrees(110));// change to 90
    driveTo(jwb::Inches(88));

    turnTo(jwb::Degrees(60));//change to 45
    wings.open();
    driveTo(jwb::Inches(30));
    turnTo(jwb::Degrees(15));//change to 45

    arcade(100, 0);
    wait(0.5, vex::sec);
    arcade(-50, 0);
    wait(0.25, vex::sec);
    arcade(100, 0);
    wait(0.5, vex::sec);

    arcade(-50, 0);
    wait(0.5, vex::sec);
    wings.close();

    arcade(0, 50);
    wait(0.25, vex::sec);

    arcade(100, 25);
    wait(0.5, vex::sec);
    arcade(-50, 0);
    wait(0.25, vex::sec);
    arcade(100, 0);
    wait(0.5, vex::sec);

    arcade(-50, 0);
    wait(0.5, vex::sec);
    wings.close();

    turnTo(jwb::Angle(-80));
    driveTo(jwb::Inches(48));

    turnTo(jwb::Angle(0));
    driveTo(jwb::Inches(36));///New!

    turnTo(jwb::Degrees(70));

    wings.open();
    climb.open();

    arcade( 100, 0);
    wait(0.75, vex::sec);
    arcade( -50, 0);
    wait(0.25, vex::sec);
    arcade( 100, 0);
    wait(0.5, vex::sec);

    arcade( -50, 0);
    wait(0.5, vex::sec);
    wings.close();
    climb.close();

    turnTo(jwb::Degrees(-35));
    arcadeFor(50,0,0.5);

    turnTo(jwb::Degrees(80));

    wings.open();
    climb.open();

    arcade( 100, 0);
    wait(0.65, vex::sec);
    arcade( -50, 0);
    wait(0.25, vex::sec);
    arcade( 100, 0);
    wait(0.5, vex::sec);

    arcade( -50, 0);
    wait(0.5, vex::sec);
    arcade(0,0);
    wings.close();
    climb.close();
}   