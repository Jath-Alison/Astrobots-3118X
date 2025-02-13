#include "Autons.h"
#include "SubAutons.h"
#include <iostream>

void flippingAWPAuton()
{
    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-5));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(158), oldTurnPID);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(7));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Put out doinker and back up
    doinkerDeployR.set(true);
    vex::wait(0.25, vex::sec);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());

    doinkerDeployR.set(false);
    asyncDrive.setTurnTarget(art::Degrees(160 + 15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    intake.setState(Intake::STOP_RED);
    asyncDrive.setDriveTarget(art::Inches(20));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // TurnToGoal
    asyncDrive.setTurnTarget(art::Degrees(-90 + -20));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-20));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.75, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    asyncDrive.setDriveTarget(0);
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(0));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.setDriveTarget(art::Inches(30));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    arm.handlePosInput(art::Degrees(115));

    asyncDrive.setDriveTarget(art::Inches(-5));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());
    std::cout << asyncDrive.driveError() << std::endl;

    asyncDrive.setTurnTarget(art::Degrees(-15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());
    // waitUntil(asyncDrive.turnError() < art::Degrees(3));

    asyncDrive.setDriveTarget(art::Inches(-15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());
    // waitUntil(fabs(asyncDrive.driveError()) < art::Degrees(45));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-80, 0);

    vex::wait(0.75, vex::sec);

    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(-75);
}

void centerRings()
{
    art::PID driveFastExit = oldDrivePID;
    driveFastExit
        .withSettleTimeout(0.0625)
        .withTimeout(1);

    intake.setAntiJam(true);

    asyncDrive.driveForS(art::Inches(-18), driveFastExit);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.75, vex::sec);

    clamp.set(true);
    vex::wait(0.25, vex::sec);

    asyncDrive.turnToS(art::Degrees(-45), oldTurnPID);
    intake.resetDelay(0.5);
    intake.setState(Intake::DELAY_OFF);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(-45), oldDrivePID, oldTurnPID);

    doinkerDeployL.set(true);
    vex::wait(0.55, vex::sec);

    asyncDrive.turnToS(art::Degrees(295));
    asyncDrive.driveForS(art::Inches(4));

    doinkerDeployR.set(true);
    vex::wait(0.55, vex::sec);

    asyncDrive.driveForS(art::Inches(-47), driveFastExit);

    doinkerDeployL.set(false);
    doinkerDeployR.set(false);

    asyncDrive.turnToS(art::Degrees(-46));

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.driveForS(art::Inches(14), oldDrivePID);
    vex::wait(0.25, vex::sec);
    asyncDrive.turnToS(art::Degrees(-145));

    asyncDrive.driveForHeadingCorrectedS(art::Inches(15),art::Degrees(-145), oldDrivePID, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(36-15),art::Degrees(-145), oldDrivePID, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(2),art::Degrees(-145), oldDrivePID, oldTurnPID);
    
    asyncDrive.turnToS(art::Degrees(-100));

    asyncDrive.driveForS(art::Inches(-36), driveFastExit);
    clamp.set(false);
    asyncDrive.driveForS(art::Inches(36), driveFastExit);
    asyncDrive.turnToS(art::Degrees(90));


}

void ringSideToCorner()
{

    intake.setAntiJam(true);

    oldDrivePID.withSettleTimeout(0.125);
    oldTurnPID.withSettleTimeout(0.125);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    waitUntil(asyncDrive.driveComplete());
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-5));

    // TurnToGoal
    asyncDrive.turnToS(art::Degrees(-90), oldTurnPID);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.75, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    asyncDrive.setDriveTarget(0);
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // TurnToRingStash
    asyncDrive.setTurnTarget(art::Degrees(45));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    doinkerDeployR.set(true);
    vex::wait(0.5, vex::sec);

    asyncDrive.setTurnTarget(art::Degrees(-15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());
    doinkerDeployR.set(false);

    asyncDrive.setDriveTarget(art::Inches(-3));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(45));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.driveForS(art::Inches(4));

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.setTurnTarget(art::Degrees(0));
    asyncDrive.setState(AsyncDrive::SWING_ABOUT_LEFT);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.driveForHeadingCorrectedS(art::Inches(10), 0);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(10), 0);

    asyncDrive.setTurnTarget(art::Degrees(20));
    asyncDrive.setState(AsyncDrive::SWING_ABOUT_LEFT);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-25));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Go for ring stack
    asyncDrive.setTurnTarget(art::Degrees(-25));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // // Go for Corner
    asyncDrive.setTurnTarget(art::Degrees(-55));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    doinkerDeployR.set(true);

    oldDrivePID.withSettleTimeout(0.0625);

    asyncDrive.driveForS(art::Inches(25),oldDrivePID);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.75, vex::sec);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(0, -90);
    vex::wait(0.75, vex::sec);

    doinkerDeployR.set(false);

    asyncDrive.setTurnTarget(art::Degrees(-55));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    intake.setState(Intake::REJECT_BLUE);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.75, vex::sec);

    asyncDrive.driveForS(art::Inches(-5));

    waitUntil(intake.getState() == Intake::CONTROL);
    intake.handleInput(100);
    
    vex::wait(5, vex::sec);
}

void skills()
{
    intake.setAntiJam(true);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.driveForS(art::Inches(-8));
    arm.handlePosInput(art::Degrees(-5));

    asyncDrive.turnToS(art::Degrees(180));
    asyncDrive.driveForS(art::Inches(-12));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.75, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    asyncDrive.turnToS(art::Degrees(90));

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.driveForS(art::Inches(19));

    asyncDrive.turnToS(art::Degrees(45));
    asyncDrive.driveForS(art::Inches(33));

    intake.setState(Intake::STOP_RED);
    
    arm.handlePosInput(art::Degrees(10));
    intake.setAntiJam(false);
    
    asyncDrive.turnToS(art::Degrees(90));
    asyncDrive.driveForS(art::Inches(26));
    
    intake.resetDelay(0.5);
    intake.setState(Intake::DELAY_OFF);
    asyncDrive.driveForS(art::Inches(-20));

    asyncDrive.turnToS(art::Degrees(0));
    arm.handlePosInput(art::Degrees(60));
    asyncDrive.driveForS(art::Inches(5));

    asyncDrive.driveForHeadingCorrectedS(art::Inches(5), 0, oldDrivePID, oldTurnPID);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.5, vex::sec);

    arm.handlePosInput(art::Degrees(135));
    intake.setState(Intake::CONTROL);
    intake.handleInput(-30);

}
