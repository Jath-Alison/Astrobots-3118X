#include "Autons/FlippingAutons.h"
#include "SubAutons.h"

void flippingAWPAuton_redNeg()
{
    vex::digital_out *currentDoinker = &doinkerDeployL;
    if (asyncDrive.getYFlip() == asyncDrive.getXFlip())
    { // there was a typo here
        currentDoinker = &doinkerDeployR;
    }

    intake.setAntiJam(true);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-20));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-15));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(165), oldTurnPID);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Put out doinker and back up
    // currentDoinker->set(true);
    currentDoinker->set(true);
    vex::wait(0.25, vex::sec);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());

    // currentDoinker->set(false);
    currentDoinker->set(false);
    asyncDrive.setTurnTarget(art::Degrees(165 + 15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    if (asyncDrive.getXFlip())
    {
        intake.setState(Intake::STOP_BLUE);
    }
    else
    {
        intake.setState(Intake::STOP_RED);
    }

    asyncDrive.setDriveTarget(art::Inches(20));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // TurnToGoal
    asyncDrive.setTurnTarget(art::Degrees(-110));
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

    asyncDrive.setDriveTarget(art::Inches(32));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    arm.handlePosInput(art::Degrees(65));

    asyncDrive.setDriveTarget(art::Inches(-5));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(-15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());
    // waitUntil(asyncDrive.turnError() < art::Degrees(3));

    asyncDrive.setDriveTarget(art::Inches(-15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());
    // waitUntil(fabs(asyncDrive.driveError()) < art::Degrees(45));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-73, 0);

    // asyncDrive.setDriveTarget(art::Inches(-40));
    // waitUntil(asyncDrive.driveComplete());

    vex::wait(1.5, vex::sec);

    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(-40);
    asyncDrive.handleInputs(0, 0);

    vex::wait(0.75, vex::sec);

    // arm.handlePosInput(art::Degrees(180));
    // arm.setState(Arm::POSITION);
}

void flippingAWPAuton_redPos()
{
    asyncDrive.setYFlip(true);

    vex::digital_out *currentDoinker = &doinkerDeployL;
    if (asyncDrive.getYFlip() == asyncDrive.getXFlip())
    { // there was a typo here
        currentDoinker = &doinkerDeployR;
    }

    intake.setAntiJam(true);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-20));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-15));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(165), oldTurnPID);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Put out doinker and back up
    // currentDoinker->set(true);
    currentDoinker->set(true);
    vex::wait(0.25, vex::sec);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());

    // currentDoinker->set(false);
    currentDoinker->set(false);
    asyncDrive.setTurnTarget(art::Degrees(165 + 15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    if (asyncDrive.getXFlip())
    {
        intake.setState(Intake::STOP_BLUE);
    }
    else
    {
        intake.setState(Intake::STOP_RED);
    }

    asyncDrive.setDriveTarget(art::Inches(20));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // TurnToGoal
    asyncDrive.setTurnTarget(art::Degrees(-110));
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

    asyncDrive.setDriveTarget(art::Inches(32));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    arm.handlePosInput(art::Degrees(65));

    asyncDrive.setDriveTarget(art::Inches(-5));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(-15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());
    // waitUntil(asyncDrive.turnError() < art::Degrees(3));

    asyncDrive.setDriveTarget(art::Inches(-15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());
    // waitUntil(fabs(asyncDrive.driveError()) < art::Degrees(45));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-73, 0);

    // asyncDrive.setDriveTarget(art::Inches(-40));
    // waitUntil(asyncDrive.driveComplete());

    vex::wait(1.5, vex::sec);

    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(-40);
    asyncDrive.handleInputs(0, 0);

    vex::wait(0.75, vex::sec);

    // arm.handlePosInput(art::Degrees(180));
    // arm.setState(Arm::POSITION);
}

void flippingAWPAuton_blueNeg()
{
    asyncDrive.setXFlip(true);

    vex::digital_out *currentDoinker = &doinkerDeployL;
    if (asyncDrive.getYFlip() == asyncDrive.getXFlip())
    { // there was a typo here
        currentDoinker = &doinkerDeployR;
    }

    intake.setAntiJam(true);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-20));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-15));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(165), oldTurnPID);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Put out doinker and back up
    // currentDoinker->set(true);
    currentDoinker->set(true);
    vex::wait(0.25, vex::sec);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());

    // currentDoinker->set(false);
    currentDoinker->set(false);
    asyncDrive.setTurnTarget(art::Degrees(165 + 15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    if (asyncDrive.getXFlip())
    {
        intake.setState(Intake::STOP_BLUE);
    }
    else
    {
        intake.setState(Intake::STOP_RED);
    }

    asyncDrive.setDriveTarget(art::Inches(20));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // TurnToGoal
    asyncDrive.setTurnTarget(art::Degrees(-110));
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

    asyncDrive.setDriveTarget(art::Inches(32));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    arm.handlePosInput(art::Degrees(65));

    asyncDrive.setDriveTarget(art::Inches(-5));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(-15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());
    // waitUntil(asyncDrive.turnError() < art::Degrees(3));

    asyncDrive.setDriveTarget(art::Inches(-15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());
    // waitUntil(fabs(asyncDrive.driveError()) < art::Degrees(45));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-73, 0);

    // asyncDrive.setDriveTarget(art::Inches(-40));
    // waitUntil(asyncDrive.driveComplete());

    vex::wait(1.5, vex::sec);

    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(-40);
    asyncDrive.handleInputs(0, 0);

    vex::wait(0.75, vex::sec);

    // arm.handlePosInput(art::Degrees(180));
    // arm.setState(Arm::POSITION);
}

void flippingAWPAuton_bluePos()
{
    asyncDrive.setYFlip(true);
    asyncDrive.setXFlip(true);

    vex::digital_out *currentDoinker = &doinkerDeployL;
    if (asyncDrive.getYFlip() == asyncDrive.getXFlip())
    { // there was a typo here
        currentDoinker = &doinkerDeployR;
    }

    intake.setAntiJam(true);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-20));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-15));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(165), oldTurnPID);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // Put out doinker and back up
    // currentDoinker->set(true);
    currentDoinker->set(true);
    vex::wait(0.25, vex::sec);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());

    // currentDoinker->set(false);
    currentDoinker->set(false);
    asyncDrive.setTurnTarget(art::Degrees(165 + 15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    if (asyncDrive.getXFlip())
    {
        intake.setState(Intake::STOP_BLUE);
    }
    else
    {
        intake.setState(Intake::STOP_RED);
    }

    asyncDrive.setDriveTarget(art::Inches(20));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // TurnToGoal
    asyncDrive.setTurnTarget(art::Degrees(-110));
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

    asyncDrive.setDriveTarget(art::Inches(32));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    arm.handlePosInput(art::Degrees(65));

    asyncDrive.setDriveTarget(art::Inches(-5));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setTurnTarget(art::Degrees(-15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());
    // waitUntil(asyncDrive.turnError() < art::Degrees(3));

    asyncDrive.setDriveTarget(art::Inches(-15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());
    // waitUntil(fabs(asyncDrive.driveError()) < art::Degrees(45));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-73, 0);

    // asyncDrive.setDriveTarget(art::Inches(-40));
    // waitUntil(asyncDrive.driveComplete());

    vex::wait(1.5, vex::sec);

    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(-40);
    asyncDrive.handleInputs(0, 0);

    vex::wait(0.75, vex::sec);

    // arm.handlePosInput(art::Degrees(180));
    // arm.setState(Arm::POSITION);
}