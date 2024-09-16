#include "Autons.h"

int updateMotorsTask(){
    for (;;){
        jwb::SmartMotor::updateAllMotors();
    }
}

void Skills(){

    inert.setHeading( -45, vex::degrees);

    Intake = -50;
    wait(0.25,vex::sec);
    Intake = 0;

    arcadeFor(50,-15, 0.5);

    wings.open();
    Flywheel.set(-100);
    wait(30, vex::seconds);//launching 30
    Flywheel.set(0);
    wings.close();

    arcade(-30,0);
    wait(20, vex::msec);
    turnTo(jwb::Degrees(135));// change to 90
    driveTo(jwb::Inches(15));
    turnTo(jwb::Degrees(100));// change to 90
    driveTo(jwb::Inches(60));

    turnTo(jwb::Degrees(60));//change to 45
    wings.open();
    driveTo(jwb::Inches(25));
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

    turnTo(jwb::Degrees(-80));
    driveTo(jwb::Inches(48/2));

    turnTo(jwb::Degrees(0));
    driveTo(jwb::Inches(36/2));///New!

    turnTo(jwb::Degrees(70));

    wings.open();
    climb.open();

    arcade( 100, -10);
    wait(0.75, vex::sec);
    arcade( -50, 0);
    wait(0.25, vex::sec);
    arcade( 100, 0);
    wait(0.5, vex::sec);

    arcade( -50, 0);
    wait(0.75, vex::sec);

    turnTo(jwb::Degrees(70));

    wings.open();
    climb.open();

    arcade( 100, -10);
    wait(0.75, vex::sec);
    arcade( -50, 0);
    wait(0.25, vex::sec);
    arcade( 100, 0);
    wait(0.5, vex::sec);
    arcade( -50, 0);
    wait(1, vex::sec);

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
    wait(0.75, vex::sec);
    // wings.close();
    // climb.close();



    // turnTo(jwb::Degrees(-35));
    // arcadeFor(50,0,0.5);

    // turnTo(jwb::Degrees(80));

    // wings.open();
    // climb.open();

    // arcade( 100, 0);
    // wait(0.65, vex::sec);
    // arcade( -50, 0);
    // wait(0.25, vex::sec);
    // arcade( 100, 0);
    // wait(0.5, vex::sec);

    // arcade( -50, 0);
    // wait(0.5, vex::sec);
    // arcade(0,0);
    // wings.close();
    // climb.close();
}   