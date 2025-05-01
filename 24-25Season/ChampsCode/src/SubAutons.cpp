#include "SubAutons.h"

#define HEADING_TOLERANCE 6

bool gyroZeroed = false;
void zeroGyro()
{
    gyroZeroed = true;
    asyncDrive.zeroGyro();

    art::Vec2 leftGPSPos = art::Vec2::XandY(art::Inches(gpsSensorL.xPosition(vex::inches)), art::Inches(gpsSensorL.yPosition(vex::inches)));
    art::Vec2 rightGPSPos = art::Vec2::XandY(art::Inches(gpsSensorR.xPosition(vex::inches)), art::Inches(gpsSensorR.yPosition(vex::inches)));

    // if (fabs(gpsSensorL.heading(vex::degrees) - asyncDrive.getDir().degrees()) < art::Degrees(HEADING_TOLERANCE) && fabs(gpsSensorR.heading(vex::degrees) - asyncDrive.getDir().degrees()) < art::Degrees(HEADING_TOLERANCE) &&
    //     gpsSensorR.quality() == 100 && gpsSensorL.quality() == 100 &&
    // gpsSensorR.xPosition() != 0.0 && gpsSensorR.yPosition() != 0.0 && gpsSensorL.xPosition() != 0.0 && gpsSensorL.yPosition() != 0.0)
    // {
    //     asyncDrive.setPos((leftGPSPos + rightGPSPos) * 0.5);
    // }
    // else if (fabs(gpsSensorL.heading(vex::degrees) - asyncDrive.getDir().degrees()) < art::Degrees(HEADING_TOLERANCE) &&
    //          gpsSensorL.quality() == 100
    // && gpsSensorL.xPosition() != 0.0 && gpsSensorL.yPosition() != 0.0)
    // {
    //     asyncDrive.setPos(leftGPSPos);
    // }
    // else
    if (fabs(gpsSensorR.heading(vex::degrees) - asyncDrive.getDir().degrees()) < art::Degrees(HEADING_TOLERANCE) &&
        gpsSensorR.quality() == 100 &&
        gpsSensorR.xPosition() != 0.0 && gpsSensorR.yPosition() != 0.0)
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

    art::Vec2 avgPos = asyncDrive.getPos();

    // if (fabs(gpsSensorL.heading(vex::degrees) - asyncDrive.getDir().degrees() < art::Degrees(HEADING_TOLERANCE)) && fabs(gpsSensorR.heading(vex::degrees) - asyncDrive.getDir().degrees() < art::Degrees(HEADING_TOLERANCE)) &&
    //     gpsSensorR.quality() == 100 && gpsSensorL.quality() == 100)
    // {
    //     avgPos = (leftGPSPos + rightGPSPos) * 0.5;
    // }
    // else if (fabs(gpsSensorL.heading(vex::degrees) - asyncDrive.getDir().degrees() < art::Degrees(HEADING_TOLERANCE)) &&
    //          gpsSensorL.quality() == 100)
    // {
    //     avgPos = leftGPSPos;
    // }
    // else
    if (fabs(gpsSensorR.heading(vex::degrees) - asyncDrive.getDir().degrees()) < art::Degrees(HEADING_TOLERANCE) &&
        gpsSensorR.quality() == 100 &&
        gpsSensorR.xPosition() != 0.0 && gpsSensorR.yPosition() != 0.0)
    {
        avgPos = rightGPSPos;
    }

    avgPos = avgPos * scale + asyncDrive.getPos() * (1.0 - scale);

    asyncDrive.setPos(avgPos);
}

bool localizing = true;
