#include "SubAutons.h"

bool gyroZeroed = false;
void zeroGyro()
{
    gyroZeroed = true;
    asyncDrive.zeroGyro();
}

void ladyBrownMacroTest()
{

    zeroGyro();

    intake.setAntiJam(false);

    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(10));

    waitUntil(arm.isComplete());
    
    intake.resetDelay(0.5);
    intake.setState(Intake::DELAY_OFF);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(5), 0, oldDrivePID, oldTurnPID);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.5, vex::sec);

    arm.handlePosInput(art::Degrees(135));
    intake.setState(Intake::CONTROL);
    intake.handleInput(-30);

    waitUntil(arm.isComplete());

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-5), 0, oldDrivePID, oldTurnPID);
}
