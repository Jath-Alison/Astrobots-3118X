#include "Autons/SoloAWP.h"
#include "SubAutons.h"

void redSoloAWP()
{
    vex::digital_out *currentDoinker = &doinkerDeployL;
    vex::digital_out *oppDoinker = &doinkerDeployR;
    if (asyncDrive.getXFlip())
    { // there was a typo here
        currentDoinker = &doinkerDeployR;
        oppDoinker = &doinkerDeployL;
    }

    art::PID doinkerTurnPID = oldTurnPID;
    doinkerTurnPID.setConstants(doinkerTurnPID.getkp() * 1.25, doinkerTurnPID.getki(), doinkerTurnPID.getkd());

    intake.setAntiJam(true);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-22));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-15));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(15), oldTurnPID);
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
    asyncDrive.turnToS(art::Degrees(15 - 15), doinkerTurnPID);

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
    asyncDrive.setTurnTarget(art::Degrees(-60));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-21 - 8)); // added additional 8 for no slow
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // asyncDrive.setState(AsyncDrive::CONTROL);
    // asyncDrive.handleInputs(-60, 0);
    // vex::wait(0.75, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    intake.setState(Intake::DELAY_OFF);
    intake.resetDelay(0.5);

    asyncDrive.turnToS(art::Degrees(45 - 7), oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(45 - 7), oldDrivePID, oldTurnPID);

    oppDoinker->set(true);
    vex::wait(0.25, vex::sec);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-32 - 6), art::Degrees(45 - 7), oldDrivePID, oldTurnPID);

    oppDoinker->set(false);

    asyncDrive.turnToS(art::Degrees(45 - 7 + 20), doinkerTurnPID);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(20), art::Degrees(45 - 7 + 20), oldDrivePID, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(-170), oldTurnPID);

    redSoloAWP_part2();
}

void redSoloAWP_part2()
{
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.driveForS(art::Inches(24 + 4 - 8)); // added 4
    asyncDrive.driveForS(art::Inches(-4));
    if (asyncDrive.getXFlip())
    {
        intake.setState(Intake::STOP_BLUE);
    }
    else
    {
        intake.setState(Intake::STOP_RED);
    }

    asyncDrive.turnToS(art::Degrees(135));
    clamp.set(false);
    asyncDrive.turnToS(art::Degrees(45));

    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(65));

    asyncDrive.turnToS(art::Degrees(-89));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-10.5), art::Degrees(-89));

    clamp.set(true);
    vex::wait(0.125, vex::sec);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(85, 80); // Cubic scaled
    vex::wait(0.75, vex::sec);
    asyncDrive.handleInputs(85, 0);
    vex::wait(0.25, vex::sec);
    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(40);
    asyncDrive.handleInputs(0, 0);

    vex::wait(1, vex::sec);
}

void blueSoloAWP()
{
    asyncDrive.setXFlip(true);

    vex::digital_out *currentDoinker = &doinkerDeployL;
    vex::digital_out *oppDoinker = &doinkerDeployR;
    if (asyncDrive.getXFlip())
    { // there was a typo here
        currentDoinker = &doinkerDeployR;
        oppDoinker = &doinkerDeployL;
    }

    art::PID doinkerTurnPID = oldTurnPID;
    doinkerTurnPID.setConstants(doinkerTurnPID.getkp() * 1.25, doinkerTurnPID.getki(), doinkerTurnPID.getkd());

    intake.setAntiJam(true);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-22));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-15));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(10), oldTurnPID);
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
    asyncDrive.turnToS(art::Degrees(10 - 15), doinkerTurnPID);

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
    asyncDrive.setTurnTarget(art::Degrees(-60));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-21 - 8)); // added additional 8 for no slow
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // asyncDrive.setState(AsyncDrive::CONTROL);
    // asyncDrive.handleInputs(-60, 0);
    // vex::wait(0.75, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    intake.setState(Intake::DELAY_OFF);
    intake.resetDelay(0.5);

    asyncDrive.turnToS(art::Degrees(45 - 7), oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(45 - 7), oldDrivePID, oldTurnPID);

    oppDoinker->set(true);
    vex::wait(0.25, vex::sec);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-32 - 6), art::Degrees(45 - 7), oldDrivePID, oldTurnPID);

    oppDoinker->set(false);

    asyncDrive.turnToS(art::Degrees(45 - 7 + 20), doinkerTurnPID);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(20), art::Degrees(45 - 7 + 20), oldDrivePID, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(-163), oldTurnPID);

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.driveForS(art::Inches(24 + 4 - 8)); // added 4
    asyncDrive.driveForS(art::Inches(-4));
    if (asyncDrive.getXFlip())
    {
        intake.setState(Intake::STOP_BLUE);
    }
    else
    {
        intake.setState(Intake::STOP_RED);
    }

    asyncDrive.turnToS(art::Degrees(135));
    clamp.set(false);
    asyncDrive.turnToS(art::Degrees(45));

    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(65));

    asyncDrive.turnToS(art::Degrees(-89));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-10.5), art::Degrees(-89));

    clamp.set(true);
    vex::wait(0.125, vex::sec);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(85, -80); // Cubic scaled
    vex::wait(0.75, vex::sec);
    asyncDrive.handleInputs(85, 0);
    vex::wait(0.25, vex::sec);
    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(40);
    asyncDrive.handleInputs(0, 0);

    vex::wait(1, vex::sec);
}
void blueSoloAWPNeg()
{
    vex::digital_out *currentDoinker = &doinkerDeployL;
    vex::digital_out *oppDoinker = &doinkerDeployR;
    if (asyncDrive.getXFlip())
    { // there was a typo here
        currentDoinker = &doinkerDeployR;
        oppDoinker = &doinkerDeployL;
    }

    art::PID doinkerTurnPID = oldTurnPID;
    doinkerTurnPID.setConstants(doinkerTurnPID.getkp() * 1.25, doinkerTurnPID.getki(), doinkerTurnPID.getkd());

    intake.setAntiJam(true);

    // drive 2 inches and score ladybrown
    asyncDrive.driveForS(art::Inches(2), oldDrivePID);
    asyncDrive.setState(AsyncDrive::WAIT);

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    // Back out
    asyncDrive.setState(AsyncDrive::DRIVE);
    asyncDrive.setDriveTarget(art::Inches(-22));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-15));

    // Move to Rings
    asyncDrive.turnToS(art::Degrees(15), oldTurnPID);
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
    asyncDrive.turnToS(art::Degrees(15 - 15), doinkerTurnPID);

    if (!asyncDrive.getXFlip()) //reversed to run on wrong y side
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
    asyncDrive.setTurnTarget(art::Degrees(-60));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-21 - 8)); // added additional 8 for no slow
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    // asyncDrive.setState(AsyncDrive::CONTROL);
    // asyncDrive.handleInputs(-60, 0);
    // vex::wait(0.75, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    intake.setState(Intake::DELAY_OFF);
    intake.resetDelay(0.5);

    asyncDrive.turnToS(art::Degrees(45 - 7), oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(45 - 7), oldDrivePID, oldTurnPID);

    oppDoinker->set(true);
    vex::wait(0.25, vex::sec);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-32 - 6), art::Degrees(45 - 7), oldDrivePID, oldTurnPID);

    oppDoinker->set(false);

    asyncDrive.turnToS(art::Degrees(45 - 7 + 20), doinkerTurnPID);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(15), art::Degrees(45 - 7 + 20), oldDrivePID, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(180), oldTurnPID);

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.driveForS(art::Inches(24 + 4 - 8)); // added 4
    if (!asyncDrive.getXFlip()) //reversed to run on wrong y side
    {
        intake.setState(Intake::STOP_BLUE);
    }
    else
    {
        intake.setState(Intake::STOP_RED);
    }

    asyncDrive.turnToS(art::Degrees(45));
    clamp.set(false);

    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(65));

    asyncDrive.turnToS(art::Degrees(-89));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-10.5), art::Degrees(-89));

    clamp.set(true);
    vex::wait(0.125, vex::sec);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(85, 80); // Cubic scaled
    vex::wait(0.75, vex::sec);
    asyncDrive.handleInputs(85, 0);
    vex::wait(0.25, vex::sec);
    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(40);
    asyncDrive.handleInputs(0, 0);

    vex::wait(1, vex::sec);
}