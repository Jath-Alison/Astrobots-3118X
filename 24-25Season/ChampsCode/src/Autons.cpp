#include "Autons.h"

void flippingAWPAuton()
{
    //drive 2 inches and score ladybrown
    asyncDrive.setDriveTarget(art::Inches(2));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    arm.handlePosInput(art::Degrees(180));
    arm.setState(Arm::POSITION);
    waitUntil(arm.isComplete());

    //Back out
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());
    arm.handlePosInput(art::Degrees(-5));

    //Move to Rings
    asyncDrive.setTurnTarget(art::Degrees(160));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(10));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    //Put out doinker and back up
    doinkerDeployR.set(true);
    asyncDrive.setDriveTarget(art::Inches(-15));
    waitUntil(asyncDrive.driveComplete());

    doinkerDeployR.set(false);
    asyncDrive.setTurnTarget(art::Degrees(145 + 15));
    asyncDrive.setState(AsyncDrive::TURN);
    waitUntil(asyncDrive.turnComplete());

    intake.setState(Intake::STOP_RED);
    asyncDrive.setDriveTarget(art::Inches(4));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());


}