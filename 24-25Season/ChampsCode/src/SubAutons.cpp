#include "SubAutons.h"

bool gyroZeroed = false;
void zeroGyro()
{
    gyroZeroed = true;
    asyncDrive.zeroGyro();

    art::Vec2 leftGPSPos = art::Vec2::XandY(art::Inches(gpsSensorL.xPosition(vex::inches)), art::Inches(gpsSensorL.yPosition(vex::inches)));
    art::Vec2 rightGPSPos = art::Vec2::XandY(art::Inches(gpsSensorR.xPosition(vex::inches)), art::Inches(gpsSensorR.yPosition(vex::inches)));

    if (gpsSensorL.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) && gpsSensorR.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) &&
        gpsSensorR.quality() == 100 && gpsSensorL.quality() == 100)
    {
        asyncDrive.setPos((leftGPSPos + rightGPSPos) * 0.5);
    }
    else if (gpsSensorL.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) &&
             gpsSensorL.quality() == 100)
    {
        asyncDrive.setPos(leftGPSPos);
    }
    else if (gpsSensorR.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) &&
             gpsSensorR.quality() == 100)
    {
        asyncDrive.setPos(rightGPSPos);
    }
    else
    {
        // logger.logStringEntry(Auton_Console, "Failed to Localize");
    }
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

void localize(double scale)
{
    art::Vec2 leftGPSPos = art::Vec2::XandY(art::Inches(gpsSensorL.xPosition(vex::inches)), art::Inches(gpsSensorL.yPosition(vex::inches)));
    art::Vec2 rightGPSPos = art::Vec2::XandY(art::Inches(gpsSensorR.xPosition(vex::inches)), art::Inches(gpsSensorR.yPosition(vex::inches)));

    art::Vec2 avgPos;

    if (gpsSensorL.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) && gpsSensorR.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) &&
        gpsSensorR.quality() == 100 && gpsSensorL.quality() == 100)
    {
        avgPos = (leftGPSPos + rightGPSPos) * 0.25;
    }
    else if (gpsSensorL.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) &&
             gpsSensorL.quality() == 100)
    {
        avgPos = leftGPSPos;
    }
    else if (gpsSensorR.heading(vex::degrees) - asyncDrive.getDir() < art::Degrees(2) &&
             gpsSensorR.quality() == 100)
    {
        avgPos = rightGPSPos;
    }
    
    avgPos = avgPos * scale + asyncDrive.getPos() * (1.0-scale);

    asyncDrive.setPos(avgPos);
    
}
