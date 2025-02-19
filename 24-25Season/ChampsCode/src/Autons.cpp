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

    asyncDrive.driveForHeadingCorrectedS(art::Inches(15), art::Degrees(-145), oldDrivePID, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(36 - 15), art::Degrees(-145), oldDrivePID, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(2), art::Degrees(-145), oldDrivePID, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(-100));

    asyncDrive.driveForS(art::Inches(-36), driveFastExit);
    clamp.set(false);
    asyncDrive.driveForS(art::Inches(36), driveFastExit);
    asyncDrive.turnToS(art::Degrees(90));
}

void centerRingsWWallstake()
{

    // red neg
    art::PID driveFastExit = oldDrivePID;
    driveFastExit
        .withSettleTimeout(0.0625)
        .withTimeout(1);

    art::PID turnFastExit = oldTurnPID;
    turnFastExit
        .withSettleTimeout(0.125)
        .withTimeout(1);

    intake.setAntiJam(true);

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
    asyncDrive.turnToS(art::Degrees(-90), turnFastExit);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.setDriveTarget(art::Inches(-15));
    asyncDrive.setState(AsyncDrive::DRIVE);
    waitUntil(asyncDrive.driveComplete());

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.35, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    asyncDrive.turnToS(art::Degrees(135), oldTurnPID);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(135), oldDrivePID, oldTurnPID);

    doinkerDeployL.set(true);
    vex::wait(0.55, vex::sec);

    asyncDrive.turnToS(art::Degrees(108));
    asyncDrive.driveForS(art::Inches(4));

    doinkerDeployR.set(true);
    vex::wait(0.55, vex::sec);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-54), art::Degrees(135), driveFastExit, oldTurnPID);

    doinkerDeployL.set(false);

    asyncDrive.turnToS(art::Degrees(145));
    doinkerDeployR.set(false);
    asyncDrive.turnToS(art::Degrees(165));

    intake.setState(Intake::REJECT_BLUE);
    intake.setContinousSorting();
    intake.handleInput(100);

    asyncDrive.driveForS(art::Inches(14), driveFastExit);
    // vex::wait(0.25, vex::sec);
    asyncDrive.turnToS(art::Degrees(55));

    asyncDrive.driveForHeadingCorrectedS(art::Inches(15), art::Degrees(55), driveFastExit, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(36 - 15), art::Degrees(15), driveFastExit, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(2), art::Degrees(15), driveFastExit, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(100), turnFastExit);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(13), art::Degrees(108), driveFastExit, oldTurnPID);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-13), art::Degrees(45), driveFastExit, oldTurnPID);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-85, 0);
    vex::wait(0.35, vex::sec);
}

void ringSideToCorner()
{
    intake.setContinousSorting();
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

    intake.setState(Intake::REJECT_BLUE);
    // intake.handleInput(100);

    asyncDrive.setTurnTarget(art::Degrees(0));
    asyncDrive.setState(AsyncDrive::SWING_ABOUT_LEFT);
    waitUntil(asyncDrive.turnComplete());

    asyncDrive.driveForHeadingCorrectedS(art::Inches(20), 0);
    // asyncDrive.driveForHeadingCorrectedS(art::Inches(10), 0);

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

    asyncDrive.driveForS(art::Inches(25), oldDrivePID);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.45, vex::sec);

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
}

void skillsFirstHalf()
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

    asyncDrive.turnToS(art::Degrees(95));

    intake.setState(Intake::CONTROL);
    intake.handleInput(100);

    std::vector<Jath::Point> ringsPath1Points = {
        Jath::Point(-118.548, 60.252, 7),
        Jath::Point(-116.778, 59.321, 79),
        Jath::Point(-115, 58.406, 79),
        Jath::Point(-113.212, 57.508, 71.5),
        Jath::Point(-111.415, 56.631, 70.452),
        Jath::Point(-109.606, 55.777, 68.648),
        Jath::Point(-107.784, 54.953, 67.278),
        Jath::Point(-105.948, 54.162, 64.95),
        Jath::Point(-104.094, 53.41, 62.283),
        Jath::Point(-102.222, 52.706, 59.276),
        Jath::Point(-100.33, 52.059, 55.957),
        Jath::Point(-98.416, 51.479, 52.393),
        Jath::Point(-96.48, 50.978, 47.461),
        Jath::Point(-94.522, 50.572, 43.852),
        Jath::Point(-92.544, 50.274, 39.592),
        Jath::Point(-90.553, 50.098, 36.508),
        Jath::Point(-88.553, 50.054, 35.122),
        Jath::Point(-86.556, 50.148, 35.72),
        Jath::Point(-84.57, 50.378, 38.25),
        Jath::Point(-82.602, 50.735, 42.34),
        Jath::Point(-80.659, 51.207, 47.425),
        Jath::Point(-78.742, 51.775, 52.91),
        Jath::Point(-76.85, 52.423, 58.298),
        Jath::Point(-74.981, 53.135, 63.249),
        Jath::Point(-73.131, 53.897, 66.558),
        Jath::Point(-71.298, 54.696, 68.005),
        Jath::Point(-69.478, 55.524, 67.506),
        Jath::Point(-67.666, 56.372, 67.006),
        Jath::Point(-65.862, 57.235, 66.506),
        Jath::Point(-64.062, 58.106, 66.006),
        Jath::Point(-62.264, 58.982, 65.507),
        Jath::Point(-60.466, 59.859, 65.007),
        Jath::Point(-59.061, 61.179, 64.50),
        Jath::Point(-57.967, 62.853, 64.007),
        Jath::Point(-56.862, 64.521, 63.508),
        Jath::Point(-55.746, 66.18, 63.008),
        Jath::Point(-54.618, 67.831, 62.508),
        Jath::Point(-53.476, 69.474, 62.508),
        Jath::Point(-52.322, 71.107, 62.508),
        Jath::Point(-51.153, 72.73, 62.508),
        Jath::Point(-49.969, 74.342, 62.508),
        Jath::Point(-48.769, 75.942, 62.508),
        Jath::Point(-47.553, 77.53, 62.508),
        Jath::Point(-46.32, 79.104, 62.508),
        Jath::Point(-45.068, 80.663, 62.508),
        Jath::Point(-43.796, 82.207, 62.508),
        Jath::Point(-42.502, 83.732, 62.508),
        Jath::Point(-41.188, 85.239, 62.508),
        Jath::Point(-39.851, 86.727, 62.508),
        Jath::Point(-38.491, 88.193, 62.508),
        Jath::Point(-37.104, 89.635, 62.508),
        Jath::Point(-35.692, 91.051, 62.508),
        Jath::Point(-34.254, 92.441, 62.508),
        Jath::Point(-32.787, 93.8, 62.508),
        Jath::Point(-31.29, 95.127, 62.508),
        Jath::Point(-29.767, 96.422, 62.508),
        Jath::Point(-28.209, 97.677, 62.508),
        Jath::Point(-26.624, 98.896, 62.508),
        Jath::Point(-25.006, 100.071, 62.508),
        Jath::Point(-23.359, 101.205, 62.508),
        Jath::Point(-21.678, 102.29, 62.508),
        Jath::Point(-19.971, 103.331, 62.508),
        Jath::Point(-18.231, 104.317, 62.508),
        Jath::Point(-16.465, 105.256, 62.508),
        Jath::Point(-14.671, 106.14, 62.508),
        Jath::Point(-12.852, 106.972, 62.508),
        Jath::Point(-11.01, 107.75, 62.508),
        Jath::Point(-9.146, 108.474, 62.508),
        Jath::Point(-7.263, 109.149, 62.508),
        Jath::Point(-5.362, 109.768, 62.508),
        Jath::Point(-3.445, 110.34, 62.508),
        Jath::Point(-1.514, 110.861, 62.508),
        Jath::Point(0.428, 111.338, 62.508),
        Jath::Point(2.381, 111.769, 62.508),
        Jath::Point(4.342, 112.16, 62.508),
        Jath::Point(6.311, 112.51, 62.508),
        Jath::Point(8.286, 112.825, 62.508),
        Jath::Point(10.267, 113.104, 62.508),
        Jath::Point(12.251, 113.354, 62.508),
        Jath::Point(14.239, 113.572, 62.508),
        Jath::Point(16.23, 113.764, 62.508),
        Jath::Point(18.223, 113.932, 62.508),
        Jath::Point(20.217, 114.076, 62.508),
        Jath::Point(22.214, 114.2, 62.508),
        Jath::Point(24.211, 114.306, 62.508),
        Jath::Point(26.209, 114.394, 62.508),
        Jath::Point(28.207, 114.468, 62.508),
        Jath::Point(30.206, 114.528, 62.508),
        Jath::Point(32.206, 114.576, 62.508),
        Jath::Point(34.206, 114.612, 62.508),
        Jath::Point(36.205, 114.639, 62.508),
        Jath::Point(38.205, 114.658, 62.508),
        Jath::Point(40.205, 114.669, 62.508),
        Jath::Point(42.205, 114.674, 62.508),
        Jath::Point(44.205, 114.674, 62.508),
        Jath::Point(46.205, 114.668, 62.508),
        Jath::Point(48.205, 114.659, 62.508),
        Jath::Point(50.205, 114.646, 62.508),
        Jath::Point(52.205, 114.632, 62.508),
        Jath::Point(54.205, 114.615, 62.508),
        Jath::Point(56.205, 114.597, 62.508),
        Jath::Point(58.205, 114.578, 62.508),
        Jath::Point(60.205, 114.558, 62.508),
        Jath::Point(62.205, 114.539, 62.508),
        Jath::Point(64.205, 114.52, 62.508),
        Jath::Point(66.205, 114.503, 62.508),
        Jath::Point(68.204, 114.486, 62.508),
        Jath::Point(70.204, 114.471, 62.508),
        Jath::Point(72.204, 114.457, 62.508),
        Jath::Point(74.204, 114.446, 62.508),
        Jath::Point(76.204, 114.437, 62.508),
        Jath::Point(78.204, 114.431, 62.508),
        Jath::Point(81.662, 114.426, 62.50),
        Jath::Point(81.662, 114.426, -1),
    };
    Jath::Path ringsPath1 = Jath::Path::cm(ringsPath1Points);

    asyncDrive.followPathA(ringsPath1);

    vex::wait(2.25, vex::sec);

    intake.setState(Intake::STOP_RED);
    intake.setAntiJam(false);
    arm.handlePosInput(art::Degrees(10));

    waitUntil(asyncDrive.pathComplete());

    asyncDrive.driveForS(art::Inches(3));
    // asyncDrive.driveForS(art::Inches(-3));

    asyncDrive.turnToS(art::Degrees(80));

    asyncDrive.driveForS(art::Inches(-24));

    intake.resetDelay(0.5);
    intake.setState(Intake::DELAY_OFF);

    asyncDrive.turnToS(art::Degrees(0));

    // arm.handlePosInput(art::Degrees(60));
    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(30);
    intake.setState(Intake::CONTROL);
    intake.handleInput(-30);

    asyncDrive.driveForA(art::Inches(5));
    vex::wait(0.35, vex::sec);
    intake.handleInput(100);
    waitUntil(asyncDrive.driveComplete());

    intake.setState(Intake::STOP_RED);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(3), 0, oldDrivePID, oldTurnPID);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.5, vex::sec);

    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(135));

    waitUntil(arm.isComplete());

    intake.setAntiJam(true);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-12), 0, oldDrivePID, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(-90));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(30), art::Degrees(-90), oldDrivePID, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(15), art::Degrees(-90), oldDrivePID, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(8), art::Degrees(-90), oldDrivePID, oldTurnPID);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(4), art::Degrees(-90), oldDrivePID, oldTurnPID);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-4), art::Degrees(-90), oldDrivePID, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(45));
    asyncDrive.driveForS(art::Inches(18));

    asyncDrive.turnToS(art::Degrees(100));
    asyncDrive.driveForS(art::Inches(-15));

    clamp.set(false);

    intake.setState(Intake::STOP_RED);
    intake.setAntiJam(false);
    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(10));

    asyncDrive.driveForHeadingCorrectedS(art::Inches(80), art::Degrees(100));
    vex::wait(0.125, vex::sec);
    doinkerDeployR.set(true);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(90));
    vex::wait(0.125, vex::sec);

    // vex::wait(0.25, vex::sec);

    asyncDrive.turnToS(art::Degrees(-30));

    intake.resetDelay(0.5);
    intake.setState(Intake::DELAY_OFF);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-16), art::Degrees(-33));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.45, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    asyncDrive.turnToS(art::Degrees(5));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(5));

    asyncDrive.setState(AsyncDrive::SWING_ABOUT_LEFT);
    asyncDrive.setTurnTarget(art::Degrees(-90));

    waitUntil(asyncDrive.turnComplete());
    doinkerDeployR.set(false);

    asyncDrive.setState(AsyncDrive::TURN);
    asyncDrive.setTurnTarget(art::Degrees(-135));

    waitUntil(asyncDrive.turnComplete());

    asyncDrive.driveForS(art::Inches(-3));
    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.25, vex::sec);
    clamp.set(false);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(36), art::Degrees(-170));

    asyncDrive.turnToS(art::Degrees(0));

    asyncDrive.driveForHeadingCorrectedS(art::Inches(-10), art::Degrees(0));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.45, vex::sec);

    clamp.set(true);

    vex::wait(0.25, vex::sec);

    // Going for Alliance Stake

    asyncDrive.turnToS(art::Degrees(90));

    asyncDrive.driveForHeadingCorrectedS(art::Inches(7), art::Degrees(90));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.75, vex::sec);
}

void skillsSecondHalf()
{
    bigTurnPID.withSettleZone(0.125)
    .withConstants(2/(art::Degrees(1)), 3.0, -750)
    ;

    asyncDrive.driveForS(art::Inches(-7));

    intake.setState(Intake::CONTROL);
    intake.handleInput(-30);
    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(180));

    waitUntil(arm.isComplete());

    
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-8), art::Degrees(90), oldDrivePID, oldTurnPID);
    arm.handlePosInput(art::Degrees(-5));
    
    intake.handleInput(100);
    intake.setAntiJam(true);
    

    asyncDrive.turnToS(art::Degrees(-45), bigTurnPID);
    waitUntil(arm.isComplete());
    asyncDrive.driveForHeadingCorrectedS(art::Inches(32), art::Degrees(-45), oldDrivePID, oldTurnPID);

    asyncDrive.turnToS(art::Degrees(-135));

    asyncDrive.driveForHeadingCorrectedS(art::Inches(34 * 3 - 15), art::Degrees(-135));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(13), art::Degrees(-135));

    asyncDrive.turnToS(art::Degrees(-90));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(12), art::Degrees(-90));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-4), art::Degrees(-90));

    asyncDrive.turnToS(art::Degrees(135));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(18), art::Degrees(135));

    asyncDrive.turnToS(art::Degrees(75));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-16), art::Degrees(75));

    clamp.set(false);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(8), art::Degrees(75));

    asyncDrive.turnToS(art::Degrees(180));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-22), art::Degrees(180));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-60, 0);
    vex::wait(0.75, vex::sec);

    clamp.set(true);
    
    vex::wait(0.25, vex::sec);
    
    intake.setState(Intake::STOP_RED);
    intake.setAntiJam(true);
    arm.handlePosInput(art::Degrees(10));
    
    asyncDrive.turnToS(art::Degrees(135));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(33), art::Degrees(135));
    
    asyncDrive.turnToS(art::Degrees(75));
    intake.setAntiJam(false);
    intake.resetDelay(0.5);
    intake.setState(Intake::DELAY_OFF);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(25), art::Degrees(75));
    
    asyncDrive.turnToS(art::Degrees(180));
    
    //Wall stake
    arm.setState(Arm::CONTROL);
    arm.handleCmdInput(30);
    intake.setState(Intake::CONTROL);
    intake.handleInput(-30);

    asyncDrive.driveForA(art::Inches(5));
    vex::wait(0.35, vex::sec);
    intake.handleInput(100);
    waitUntil(asyncDrive.driveComplete());

    intake.setState(Intake::STOP_RED);

    asyncDrive.driveForHeadingCorrectedS(art::Inches(3), art::Degrees(180), oldDrivePID, oldTurnPID);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(80, 0);
    vex::wait(0.5, vex::sec);

    arm.setState(Arm::POSITION);
    arm.handlePosInput(art::Degrees(135));

    waitUntil(arm.isComplete());

    intake.setAntiJam(true);
    intake.setState(Intake::CONTROL);
    intake.handleInput(100);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-12), art::Degrees(180), oldDrivePID, oldTurnPID);

    arm.handlePosInput(art::Degrees(90));

    //Final rings

    asyncDrive.turnToS(art::Degrees(90));
    intake.setContinousSorting();
    intake.setState(Intake::REJECT_BLUE);
    asyncDrive.driveForHeadingCorrectedS(art::Inches(24), art::Degrees(90));
    
    asyncDrive.turnToS(art::Degrees(0));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(24), art::Degrees(0));

    asyncDrive.turnToS(art::Degrees(60));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(30), art::Degrees(60));

    asyncDrive.turnToS(art::Degrees(165));
    clamp.set(false);
    asyncDrive.driveForS(art::Inches(33));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(85, 0);
    vex::wait(0.75, vex::sec);

    asyncDrive.setTurnTarget(art::Degrees(135));
    asyncDrive.setState(AsyncDrive::SWING_ABOUT_LEFT);
    waitUntil(asyncDrive.turnComplete());

    arm.handlePosInput(art::Degrees(232));
    asyncDrive.driveForHeadingCorrectedS(art::Inches(-55), art::Degrees(135));

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(-85, 0);
    vex::wait(0.75, vex::sec);

    asyncDrive.setState(AsyncDrive::CONTROL);
    asyncDrive.handleInputs(60, 0);
    vex::wait(0.75, vex::sec);
    asyncDrive.handleInputs(0, 0);


}

void skills()
{
    oldDrivePID.withSettleTimeout(0.15);
    oldTurnPID.withSettleTimeout(0.15);

    skillsFirstHalf();
    skillsSecondHalf();
}
