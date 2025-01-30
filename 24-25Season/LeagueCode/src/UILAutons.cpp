#include "SubAutons.h"
#include "UILAutons.h"

void JathsSketchyFullFlippingAWP_UIL()
{
    vex::task antiJamTask(intakeAntiJam);

    double xSign = 1.0;
    double ySign = 1.0;

    if (smartDrive.m_pos.x < 0)
    {
        xSign = -1.0;
    }
    if (smartDrive.m_pos.y < 0)
    {
        ySign = -1.0;
    }

    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.25, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-20));

    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    // resetPositionFromGPSL();

    target = art::Vec2::XandY(art::Tiles(2.45 * xSign), art::Tiles(0 * ySign));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveForPID(travel.magnitude()*0.25);
    
    doinkerDeployR.set(true);
    vex::wait(0.25,vex::sec);
    smartDrive.driveForPID(art::Inches(-18));
    vex::wait(0.5,vex::sec);
    doinkerDeployR.set(false);

    smartDrive.turnForPID(art::Degrees(15));

    intake.set(100);
    vex::thread waitForBlue(intakePauseBlue);
    // smartDrive.driveFor(art::Tiles(1.5), 60);
    // smartDrive.driveFor(art::Inches(10), 60);

    smartDrive.driveFor(art::Inches(10), 60);
    
    // vex::thread intakeOffDelay(intakeOffDelay1Sec);
    // intake.set(0);
    // AutonArmPosRunning = false;

    // driveTowardPointRev(art::Vec2::XandY(
    //     art::Tiles(2 * xSign), art::Tiles(1 * ySign)));
    // resetPositionFromGPSL();

    smartDrive.arcade(0, 0);
    // resetPositionFromGPSL();
    localizeAvg();
    vex::wait(0.25, vex::sec);

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(1.1 * xSign), art::Tiles(1 * ySign)));

    smartDrive.driveForPID(art::Inches(-3));
    clamp.set(true);
    waitForBlue.interrupt();
    intake.set(100);

    smartDrive.arcade(0,0);
    vex::wait(1, vex::sec);
    armTarget = art::Degrees(130);
    armControl = vex::thread(autonArmPos);

    // resetPositionFromGPSL();

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(2 * ySign)));

        smartDrive.driveForPID(art::Inches(5));

    smartDrive.driveForPID(art::Inches(-19));

    target = art::Vec2::XandY(art::Tiles(0.75 * xSign), art::Tiles(0.75 * ySign));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveFor(travel.magnitude(), 50);

    smartDrive.arcade(0, 0);
    AutonArmPosRunning = false;
}

void ringRushBlue_UIL()
{
    // localizeAvg();
    // resetPositionFromGPSL();

    vex::thread intakeAntiJa(intakeAntiJam);
    vex::thread intakeStop(intakePauseBlue);

    clamp.set(false);
    doinkerDeployR.set(true);

    target = art::Vec2::XandY(art::Inches(4),art::Inches(48 - 4));
    travel = target - smartDrive.m_pos;

    intake.set(100);
    smartDrive.driveForPID(art::Inches(50));//up from 48
    // followPath(ringRushBluePath, art::Inches(15));

    smartDrive.driveForPID(art::Inches(-2));
    // intake.set(0);

    // vex::wait(0.25,vex::sec);

    // vex::thread delayThread(waitForOptical);
    

    smartDrive.turnForPID(art::Degrees(30));

    smartDrive.driveForPID(art::Inches(-24));
    resetPositionFromGPSL();
    doinkerDeployR.set(false);

    target = art::Vec2::XandY(art::Tiles(0),art::Tiles(1));
    travel = target - smartDrive.m_pos;

    // smartDrive.turnToPID(art::Degrees(-45));
    // smartDrive.driveForPID(-travel.magnitude());
    smartDrive.driveForPID(art::Inches(-5));
    vex::wait(0.25,vex::sec);
    clamp.set(true);
    resetPositionFromGPSR();

    intake.set(100);
    intakeStop = vex::thread(intakeRejectRed);

    vex::wait(0.25,vex::sec);

    smartDrive.turnToPID(art::Degrees(-10));
    smartDrive.driveFor(art::Inches(15),75);

    smartDrive.turnToPID(art::Degrees(10));
    smartDrive.driveFor(art::Inches(15),75);

    vex::wait(0.25, vex::sec);

    smartDrive.driveForPID(art::Inches(-5));
    smartDrive.turnToPID(art::Degrees(-10));
    smartDrive.driveForPID(art::Inches(-25));

    localizeAvg();
    vex::wait(0.5, vex::sec);

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(3),0)));

    vex::thread armControl(autonArmPos);
    armTarget = art::Degrees(10);

    intake.set(100);

    smartDrive.driveForPID(art::Inches(30));

    smartDrive.arcade(50,0);
    vex::wait(0.5, vex::sec);

    smartDrive.driveForPID(art::Inches(-4));

    intakePauseBlue();

    intakeAntiJa.interrupt();
    vex::wait(0.25, vex::sec);

    intake.set(100);
    vex::wait(0.5, vex::sec);

    intake.set(-25);
    armTarget = art::Degrees(180);

    vex::wait(1.5, vex::sec);

    smartDrive.driveForPID(art::Inches(-6));

    vex::wait(25, vex::sec);
}