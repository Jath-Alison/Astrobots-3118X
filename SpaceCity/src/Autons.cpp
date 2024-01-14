#include "Autons.h"

void OverBarrier()
{
    smartDrive.arcade(0, 80, 0);
    waitUntil(abs(smartDrive.m_inert.roll()) > 2);
    wait(0.5, vex::sec);
    int count = 0;
    while (count < 10){ 
        wait (5, vex::msec); 
        if (abs(smartDrive.m_inert.roll()) < 2) { count ++;}
    }
    (abs(smartDrive.m_inert.roll()) < 2);
    smartDrive.arcade(0,0,0);
}

void SkillsTest()
{

    smartDrive.m_pos = x::XandY(
        x::Tiles(-1.75), x::Tiles(-2.5)//swap
    );
    smartDrive.m_inert.setHeading(-90 -30, vex::degrees);//change to - 90

    // smartDrive.arcade(0,-15,-30);
    // wait(0.25, vex::seconds);
    // smartDrive.arcade(0,-15,0);
    flywheel.set(-100);
    wait(30, vex::seconds);//launching 30
    flywheel.set(0);

    smartDrive.arcade(0,-30,0);
    wait(20, vex::msec);
    smartDrive.turnTo(x::Degrees(110));// change to 90
    smartDrive.driveTo(x::Inches(88));

    // Brain.resetTimer();
    // while(smartDrive.driveToPoint(x::XandY(x::Tiles(-1.5),x::Tiles(2.5))).inches() > 5){//change to opp
    //     if(Brain.timer(vex::seconds) > 10) { break; }
    // }

    smartDrive.turnTo(x::Degrees(60));//change to 45
    wings.open();
    smartDrive.driveTo(x::Inches(30));
    smartDrive.turnTo(x::Degrees(15));//change to 45

    smartDrive.arcade(0, 100, 0);
    wait(0.5, vex::sec);
    smartDrive.arcade(0, -50, 0);
    wait(0.25, vex::sec);
    smartDrive.arcade(0, 100, 0);
    wait(0.5, vex::sec);

    smartDrive.arcade(0, -50, 0);
    wait(0.5, vex::sec);
    wings.close();

    smartDrive.arcade(0, 0, 50);
    wait(0.25, vex::sec);

    smartDrive.arcade(0, 100, 25);
    wait(0.5, vex::sec);
    smartDrive.arcade(0, -50, 0);
    wait(0.25, vex::sec);
    smartDrive.arcade(0, 100, 0);
    wait(0.5, vex::sec);

    smartDrive.arcade(0, -50, 0);
    wait(0.5, vex::sec);
    wings.close();

    Brain.resetTimer();
    while(smartDrive.driveToPoint(x::XandY(x::Tiles(.5),x::Tiles(-1))).inches() > 2.5) {//change to 1
        // if(Brain.timer(vex::seconds) > 10) { break; }
    }
    Brain.resetTimer();
    while(smartDrive.driveToPoint(x::XandY(x::Tiles(.5),0)).inches() > 5) {//change to 1
        // if(Brain.timer(vex::seconds) > 10) { break; }
    }
    smartDrive.turnTo(x::Degrees(70));

    wings.open();
    climb.open();

    smartDrive.arcade(0, 100, 0);
    wait(0.75, vex::sec);
    smartDrive.arcade(0, -50, 0);
    wait(0.25, vex::sec);
    smartDrive.arcade(0, 100, 0);
    wait(0.5, vex::sec);

    smartDrive.arcade(0, -50, 0);
    wait(0.5, vex::sec);
    wings.close();
    climb.close();

    Brain.resetTimer();
    while(smartDrive.driveToPoint(x::XandY(x::Tiles(1),x::Tiles(.75))).inches() > 5) {//change to 1
        // if(Brain.timer(vex::seconds) > 10) { break; }
    }
    smartDrive.turnTo(x::Degrees(80));

    wings.open();
    climb.open();

    smartDrive.arcade(0, 100, 0);
    wait(0.65, vex::sec);
    smartDrive.arcade(0, -50, 0);
    wait(0.25, vex::sec);
    smartDrive.arcade(0, 100, 0);
    wait(0.5, vex::sec);

    smartDrive.arcade(0, -50, 0);
    wait(0.5, vex::sec);
    wings.close();
    climb.close();

    {// Brain.resetTimer();
    // while(smartDrive.driveToPoint(x::XandY(x::Tiles(1),0)).inches() > 5){//change to 1
    //     if(Brain.timer(vex::seconds) > 10) { break; }
    // }
    // smartDrive.turnTo(x::Degrees(90));

    // OverBarrier();

    // Brain.resetTimer();
    // while(smartDrive.driveToPoint(x::XandY(x::Tiles(-1),0)).inches() > 5){//change
    //     if(Brain.timer(vex::seconds) > 3) { break; }
    // }
    }
}

void newSkills()
{
    
}

void scoreRight()
{
    smartDrive.arcade(0,30,30);
    wait(.35,vex::sec);
    smartDrive.arcade(0,30,-25);
    wait(.5,vex::sec);

    smartDrive.arcade(0,100,0);
    wait(1.5,vex::sec);
    smartDrive.arcade(0,-50,0);

    wait(0.5,vex::sec);

    // smartDrive.arcade(0,100,0);
    // wait(1.5,vex::sec);
    // smartDrive.arcade(0,-50,0);

    // wait(0.5,vex::sec);
    smartDrive.arcade(0,0,0);
}



void leftAwp()
{
    climb.open();
    smartDrive.arcade(0,-35,0);
    wait(0.35,vex::sec);
    smartDrive.arcade(0,-25,25);
    wait(.95,vex::sec);
    climb.close();
    smartDrive.arcade(0,75,0);
    wait(.75,vex::sec);
    smartDrive.arcade(0,0,0);

    // intake.spin(vex::fwd, 5, vex::volt);
    // wait(.25,vex::sec);
    // intake.stop();

    smartDrive.arcade(0,0,-35);
    wait(.35,vex::sec);
    smartDrive.arcade(0,75,0);
    wait(.5,vex::sec);
    smartDrive.arcade(0,0,-70);
    wait(.20,vex::sec);
    smartDrive.arcade(0,20,0);//left awp
    wait(.125,vex::sec);
    smartDrive.arcade(0,60,0);
    wait(.225,vex::sec);
    smartDrive.arcade(0,0,0);
    
}

void redBar()
{
    Brain.resetTimer();
    while(smartDrive.driveToPoint(x::XandY(x::Tiles(-1.5),x::Tiles(-1.5))).inches() > 2.5) {//change to 1
        // if(Brain.timer(vex::seconds) > 10) { break; }
    }
    Brain.resetTimer();
    while(smartDrive.driveToPoint(x::XandY(x::Tiles(.5),x::Tiles(-2.5))).inches() > 5) {//change to 1
        // if(Brain.timer(vex::seconds) > 10) { break; }
    }
}

void blueBar()
{
    Brain.resetTimer();
    while(smartDrive.driveToPoint(x::XandY(x::Tiles(1.5),x::Tiles(1.5))).inches() > 2.5) {//change to 1
        // if(Brain.timer(vex::seconds) > 10) { break; }
    }
    Brain.resetTimer();
    while(smartDrive.driveToPoint(x::XandY(x::Tiles(-.5),x::Tiles(2.5))).inches() > 5) {//change to 1
        // if(Brain.timer(vex::seconds) > 10) { break; }
    }
}
