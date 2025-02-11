#include "Autons.h"
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
    intake.resetDelay(0.5);
    intake.setState(Intake::DELAY_OFF);
    vex::wait(0.25, vex::sec);

    asyncDrive.turnToS(art::Degrees(-45), oldTurnPID);

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

    asyncDrive.turnToS(art::Degrees(-45));

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.driveForS(art::Inches(15), oldDrivePID);
    vex::wait(0.25, vex::sec);
    asyncDrive.turnToS(art::Degrees(-145));

    asyncDrive.driveForS(art::Inches(36), driveFastExit);


}

void ringSideToCorner()
{
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

    asyncDrive.setTurnTarget(art::Degrees(0));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-5));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(45));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(4));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.setTurnTarget(art::Degrees(15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(7));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(5));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(7));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(0));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(13.5));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(20));
    asyncDrive.setState(AsyncDrive::SWING_ABOUT_LEFT);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-30));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Go for ring stack
    asyncDrive.setTurnTarget(art::Degrees(-15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(22));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Go for Corner
    asyncDrive.setTurnTarget(art::Degrees(-55));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    doinkerDeployR.set(true);

    asyncDrive.setDriveTarget(art::Inches(25));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

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

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.75, vex::sec);
}