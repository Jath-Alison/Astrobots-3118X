#include "SubAutons.h"
#include "UILAutons.h"

void JathsSketchyFullFlippingAWP_UIL()
{
    vex::task antiJamTask(intakeAntiJam);
    vex::digital_out* currentDoinker = &doinkerDeployL;

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

    if(xSign * ySign > 0){
        currentDoinker = &doinkerDeployR;
    }

    smartDrive.driveForPID(art::Inches(2));

    arm.set(100);
    vex::wait(1.0, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-20));

    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    localizeAvg();
    vex::wait(0.25,vex::sec);

    target = art::Vec2::XandY(art::Tiles(2.45 * xSign), art::Tiles(0 * ySign));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveForPID(travel.magnitude()*0.25);

    currentDoinker->set(true);
    vex::wait(0.25,vex::sec);
    smartDrive.driveForPID(art::Inches(-18));
    vex::wait(0.5,vex::sec);
    currentDoinker->set(false);

    smartDrive.turnForPID(art::Degrees(15) * xSign * ySign);

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


std::vector<Jath::Point> ringRushBluePoints = {Jath::Point(114.638, 88.811, 8), Jath::Point(112.639, 88.764, 77.684), Jath::Point(110.639, 88.725, 77.497), Jath::Point(108.639, 88.694, 77.299), Jath::Point(106.64, 88.671, 77.091), Jath::Point(104.64, 88.657, 76.641), Jath::Point(102.64, 88.653, 76.399), Jath::Point(100.64, 88.659, 76.144), Jath::Point(98.64, 88.676, 75.877), Jath::Point(96.64, 88.703, 75.597), Jath::Point(94.64, 88.743, 75.303), Jath::Point(92.641, 88.795, 74.996), Jath::Point(90.642, 88.86, 74.341), Jath::Point(88.644, 88.941, 73.992), Jath::Point(86.646, 89.036, 73.63), Jath::Point(84.649, 89.148, 73.254), Jath::Point(82.653, 89.278, 72.463), Jath::Point(80.659, 89.427, 72.049), Jath::Point(78.666, 89.595, 71.187), Jath::Point(76.675, 89.785, 70.741), Jath::Point(74.686, 89.998, 69.827), Jath::Point(72.701, 90.236, 69.363), Jath::Point(70.718, 90.499, 68.428), Jath::Point(68.739, 90.789, 67.964), Jath::Point(66.765, 91.111, 67.054), Jath::Point(64.797, 91.463, 66.192), Jath::Point(62.834, 91.847, 65.408), Jath::Point(60.878, 92.266, 64.734), Jath::Point(58.931, 92.72, 64.203), Jath::Point(56.992, 93.212, 63.847), Jath::Point(55.063, 93.741, 63.693), Jath::Point(53.145, 94.308, 63.767), Jath::Point(51.239, 94.913, 64.083), Jath::Point(49.345, 95.554, 64.648), Jath::Point(47.463, 96.231, 65.458), Jath::Point(45.593, 96.942, 66.498), Jath::Point(43.736, 97.684, 68.434), Jath::Point(41.89, 98.454, 69.925), Jath::Point(40.055, 99.248, 71.527), Jath::Point(38.228, 100.063, 73.197), Jath::Point(36.409, 100.894, 74.89), Jath::Point(34.596, 101.739, 77.38), Jath::Point(32.788, 102.592, 78.954), Jath::Point(30.982, 103.451, 80.424), Jath::Point(29.177, 104.313, 80.233), Jath::Point(27.371, 105.174, 79.033), Jath::Point(25.565, 106.031, 77.984), Jath::Point(23.755, 106.883, 77.091), Jath::Point(21.942, 107.728, 76.352), Jath::Point(20.125, 108.564, 76.038), Jath::Point(18.303, 109.389, 75.516), Jath::Point(16.477, 110.203, 75.128), Jath::Point(14.645, 111.005, 74.86), Jath::Point(12.807, 111.795, 74.767), Jath::Point(10.964, 112.571, 74.654), Jath::Point(9.115, 113.334, 74.631), Jath::Point(7.261, 114.083, 74.643), Jath::Point(5.401, 114.82, 74.674), Jath::Point(3.536, 115.542, 74.78), Jath::Point(1.666, 116.251, 74.852), Jath::Point(-1.366, 117.371, 75.02), Jath::Point(-1.366, 117.371, 0), 
};
Jath::Path ringRushBluePath = Jath::Path::cm(ringRushBluePoints);

void ringRushBlueCurved_UIL()
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
    // smartDrive.driveForPID(art::Inches(50));//up from 48
    followPath(ringRushBluePath, art::Inches(15));
    smartDrive.driveForPID(art::Inches(2));

    smartDrive.driveForPID(art::Inches(-2));
    // intake.set(0);

    // vex::wait(0.25,vex::sec);

    // vex::thread delayThread(waitForOptical);
    

    smartDrive.turnToPID(art::Degrees(-45));

    smartDrive.driveForPID(art::Inches(-20));
    resetPositionFromGPSL();

    target = art::Vec2::XandY(art::Tiles(0),art::Tiles(1));
    travel = target - smartDrive.m_pos;

    // smartDrive.turnToPID(art::Degrees(-45));
    // smartDrive.driveForPID(-travel.magnitude());
    smartDrive.driveForPID(art::Inches(-5));
    doinkerDeployR.set(false);
    vex::wait(0.125,vex::sec);
    clamp.set(true);
    resetPositionFromGPSR();

    intake.set(100);
    intakeStop = vex::thread(intakeRejectRed);

    vex::wait(0.125,vex::sec);

    smartDrive.turnForPID(art::Degrees(10));
    smartDrive.driveFor(art::Inches(15),75);

    resetPositionFromGPSR();

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(1),art::Tiles(2))) + art::Degrees(20));

    smartDrive.driveFor(art::Inches(10),75);

    vex::wait(0.125, vex::sec);

    smartDrive.driveForPID(art::Inches(-18));

    localizeAvg();
    vex::wait(0.15, vex::sec);

    intakeStop = vex::thread(intakePauseBlue);

    vex::thread armControl(autonArmPos);
    armTarget = art::Degrees(10);

    driveTowardPoint(art::Vec2::XandY(art::Tiles(2.2),art::Tiles(1.2)));

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(3),0)));


    intake.set(100);

    smartDrive.driveForPID(art::Inches(15));

    smartDrive.arcade(50,-20);
    vex::wait(0.25, vex::sec);

    smartDrive.driveForPID(art::Inches(-4));

    // intakePauseBlue();

    intakeAntiJa.interrupt();
    vex::wait(0.125, vex::sec);

    intake.set(100);
    vex::wait(0.25, vex::sec);

    intake.set(-25);
    armTarget = art::Degrees(180);

    vex::wait(1.5, vex::sec);

    smartDrive.driveForPID(art::Inches(-6));

    vex::wait(25, vex::sec);
}


void ringRushRed_UIL()
{
    // localizeAvg();
    // resetPositionFromGPSL();

    double xFlip = -1.0;

    vex::thread intakeAntiJa(intakeAntiJam);
    vex::thread intakeStop(intakePauseBlue);

    clamp.set(false);
    doinkerDeployL.set(true);

    target = art::Vec2::XandY(art::Inches(4*xFlip),art::Inches(48 - 4));
    travel = target - smartDrive.m_pos;

    intake.set(100);
    smartDrive.driveForPID(art::Inches(50));//up from 48
    // followPath(ringRushBluePath, art::Inches(15));

    smartDrive.driveForPID(art::Inches(-2));
    // intake.set(0);

    // vex::wait(0.25,vex::sec);

    // vex::thread delayThread(waitForOptical);
    

    smartDrive.turnForPID(art::Degrees(30*xFlip));

    smartDrive.driveForPID(art::Inches(-24));
    resetPositionFromGPSL();
    doinkerDeployL.set(false);

    target = art::Vec2::XandY(art::Tiles(0*xFlip),art::Tiles(1));
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

    smartDrive.turnToPID(art::Degrees(-10*xFlip));
    smartDrive.driveFor(art::Inches(15),75);

    smartDrive.turnToPID(art::Degrees(10*xFlip));
    smartDrive.driveFor(art::Inches(15),75);

    vex::wait(0.25, vex::sec);

    smartDrive.driveForPID(art::Inches(-5));
    smartDrive.turnToPID(art::Degrees(-10*xFlip));
    smartDrive.driveForPID(art::Inches(-25));

    localizeAvg();
    vex::wait(0.5, vex::sec);

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(3*xFlip),0)));

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

void ringRushRedCurved_UIL()
{
    // localizeAvg();
    // resetPositionFromGPSL();

    vex::thread intakeAntiJa(intakeAntiJam);
    vex::thread intakeStop(intakePauseBlue);

    double xFlip = -1.0;

    clamp.set(false);
    doinkerDeployL.set(true);

    target = art::Vec2::XandY(art::Inches(4*xFlip),art::Inches(48 - 4));
    travel = target - smartDrive.m_pos;

    intake.set(100);
    // smartDrive.driveForPID(art::Inches(50));//up from 48
    followPath_flipX(ringRushBluePath, art::Inches(15));
    smartDrive.driveForPID(art::Inches(2));

    smartDrive.driveForPID(art::Inches(-2));
    // intake.set(0);

    // vex::wait(0.25,vex::sec);

    // vex::thread delayThread(waitForOptical);
    

    smartDrive.turnToPID(art::Degrees(-45*xFlip));

    smartDrive.driveForPID(art::Inches(-20));
    resetPositionFromGPSL();

    target = art::Vec2::XandY(art::Tiles(0*xFlip),art::Tiles(1));
    travel = target - smartDrive.m_pos;

    // smartDrive.turnToPID(art::Degrees(-45));
    // smartDrive.driveForPID(-travel.magnitude());
    smartDrive.driveForPID(art::Inches(-5));
    doinkerDeployL.set(false);
    vex::wait(0.125,vex::sec);
    clamp.set(true);
    resetPositionFromGPSR();

    intake.set(100);
    intakeStop = vex::thread(intakeRejectBlue);

    vex::wait(0.125,vex::sec);

    smartDrive.turnForPID(art::Degrees(10*xFlip));
    smartDrive.driveFor(art::Inches(15),75);

    resetPositionFromGPSR();

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(1.35*xFlip),art::Tiles(2))) + art::Degrees(20));

    smartDrive.driveFor(art::Inches(10),75);

    vex::wait(0.125, vex::sec);

    smartDrive.driveForPID(art::Inches(-18));

    // localizeAvg();
    resetPositionFromGPSR();
    vex::wait(0.15, vex::sec);

    intakeStop = vex::thread(intakePauseRed);

    vex::thread armControl(autonArmPos);
    armTarget = art::Degrees(10);

    driveTowardPoint(art::Vec2::XandY(art::Tiles(2.2*xFlip),art::Tiles(1.2)));

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(3*xFlip),0)));


    intake.set(100);

    intakeAntiJa.interrupt();
    smartDrive.driveForPID(art::Inches(15));

    smartDrive.arcade(50,-20*xFlip);
    vex::wait(0.25, vex::sec);

    smartDrive.driveForPID(art::Inches(-4));

    // intakePauseRed();

    vex::wait(0.125, vex::sec);

    intake.set(100);
    vex::wait(0.25, vex::sec);

    smartDrive.driveForPID(art::Inches(2));

    intake.set(-25);
    armTarget = art::Degrees(180);

    vex::wait(1.5, vex::sec);

    smartDrive.driveForPID(art::Inches(-6));

    vex::wait(25, vex::sec);
}