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

    armTarget = art::Degrees(345);
    vex::task armControl(autonArmPos);

    localizeAvg();
    vex::wait(0.25,vex::sec);

    target = art::Vec2::XandY(art::Tiles(2.30 * xSign), art::Tiles(0 * ySign));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction());
    smartDrive.driveForPID(travel.magnitude()*0.35);

    currentDoinker->set(true);
    vex::wait(0.25,vex::sec);
    smartDrive.driveForPID(art::Inches(-18));
    vex::wait(0.5,vex::sec);
    currentDoinker->set(false);

    smartDrive.turnForPID(art::Degrees(15) * xSign * ySign);

    intake.set(100);
    vex::thread waitForBlue(intakePauseBlue);
    if(xSign < 0){waitForBlue = vex::thread(intakePauseRed);}
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
    armControl = vex::task(autonArmPos);

    // resetPositionFromGPSL();

    driveTowardPoint(art::Vec2::XandY(
        art::Tiles(1 * xSign), art::Tiles(2 * ySign)));

        smartDrive.driveForPID(art::Inches(5));

    smartDrive.driveForPID(art::Inches(-19));

    // target = art::Vec2::XandY(art::Tiles(0.75 * xSign), art::Tiles(0.75 * ySign));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnToPID(travel.direction()+art::Degrees(180));
    // smartDrive.driveFor(travel.magnitude(), -50);

    // smartDrive.arcade(0, 0);
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

    double xFlip = 1.0;

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

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(1.35*xFlip),art::Tiles(1.75))) + art::Degrees(20));

    smartDrive.driveFor(art::Inches(10),75);

    vex::wait(0.125, vex::sec);

    smartDrive.driveForPID(art::Inches(-18));

    // localizeAvg();
    resetPositionFromGPSR();
    vex::wait(0.15, vex::sec);

    intakeStop = vex::thread(intakePauseRed);

    vex::thread armControl(autonArmPos);
    armTarget = art::Degrees(10);

    driveTowardPoint(art::Vec2::XandY(art::Tiles(2.5*xFlip),art::Tiles(1)));

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(2.5*xFlip),0)));


    intake.set(100);

    intakeAntiJa.interrupt();
    smartDrive.driveForPID(smartDrive.m_pos.distTo(art::Vec2::XandY(art::Tiles(2.5*xFlip),0)));

    smartDrive.turnToPID(90*xFlip);

    smartDrive.arcade(50,0*xFlip);
    vex::wait(0.40, vex::sec);

    smartDrive.driveForPID(art::Inches(-4));

    // intakePauseRed();

    vex::wait(0.125, vex::sec);

    intake.set(100);
    vex::wait(0.25, vex::sec);

    // smartDrive.driveForPID(art::Inches(2));

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

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(1.5*xFlip),art::Tiles(1.75))) + art::Degrees(20));

    smartDrive.driveFor(art::Inches(10),75);

    vex::wait(0.125, vex::sec);

    smartDrive.driveForPID(art::Inches(-18));

    // localizeAvg();
    resetPositionFromGPSR();
    vex::wait(0.15, vex::sec);

    intakeStop = vex::thread(intakePauseRed);

    vex::thread armControl(autonArmPos);
    armTarget = art::Degrees(10);

    driveTowardPoint(art::Vec2::XandY(art::Tiles(2.5*xFlip),art::Tiles(1)));

    smartDrive.turnToPID(smartDrive.m_pos.angleTo(art::Vec2::XandY(art::Tiles(2.5*xFlip),0)));


    intake.set(100);

    intakeAntiJa.interrupt();
    smartDrive.driveForPID(smartDrive.m_pos.distTo(art::Vec2::XandY(art::Tiles(2.5*xFlip),0)));

    smartDrive.turnToPID(art::Degrees(90)*xFlip);

    smartDrive.arcade(50,0*xFlip);
    vex::wait(0.40, vex::sec);

    smartDrive.driveForPID(art::Inches(-6));

    // intakePauseRed();

    vex::wait(0.125, vex::sec);

    intake.set(100);
    vex::wait(0.25, vex::sec);

    // smartDrive.driveForPID(art::Inches(2));

    intake.set(-25);
    armTarget = art::Degrees(180);

    vex::wait(1.5, vex::sec);

    smartDrive.driveForPID(art::Inches(-6));

    vex::wait(25, vex::sec);
}

std::vector<Jath::Point> rings1PathPoints_UIL = {
    Jath::Point(-118.646, 55.537, 8), Jath::Point(-118.7, 53.537, 74.144), Jath::Point(-118.717, 51.537, 73.144), Jath::Point(-118.694, 49.538, 72.144), Jath::Point(-118.628, 47.539, 71.143), Jath::Point(-118.514, 45.542, 70.143), Jath::Point(-118.34, 43.55, 69.143), Jath::Point(-118.112, 41.563, 68.143), Jath::Point(-117.811, 39.586, 67.142), Jath::Point(-117.439, 37.621, 66.142), Jath::Point(-116.975, 35.676, 64.19), Jath::Point(-116.414, 33.756, 60.559), Jath::Point(-115.742, 31.873, 56.352), Jath::Point(-114.94, 30.042, 51.597), Jath::Point(-113.991, 28.283, 46.412), Jath::Point(-112.879, 26.622, 41.04), Jath::Point(-111.587, 25.097, 33.497), Jath::Point(-110.11, 23.751, 29.547), Jath::Point(-108.455, 22.632, 26.419), Jath::Point(-106.651, 21.773, 27.278), Jath::Point(-104.739, 21.195, 31.589), Jath::Point(-102.763, 20.897, 35.676), Jath::Point(-100.764, 20.858, 42.481), Jath::Point(-98.774, 21.04, 49.079), Jath::Point(-96.811, 21.417, 51.138), Jath::Point(-94.885, 21.956, 50.138), Jath::Point(-93.005, 22.635, 49.138), Jath::Point(-91.17, 23.431, 48.137), Jath::Point(-89.382, 24.326, 47.137), Jath::Point(-87.641, 25.31, 46.137), Jath::Point(-85.946, 26.371, 45.137), Jath::Point(-84.295, 27.5, 44.136), Jath::Point(-82.687, 28.689, 43.136), Jath::Point(-81.122, 29.935, 43.197), Jath::Point(-79.599, 31.23, 43.259), Jath::Point(-78.115, 32.571, 43.32), Jath::Point(-76.671, 33.955, 43.381), Jath::Point(-75.266, 35.378, 43.443), Jath::Point(-73.9, 36.839, 43.504), Jath::Point(-72.573, 38.335, 43.565), Jath::Point(-71.286, 39.866, 43.627), Jath::Point(-70.038, 41.428, 43.688), Jath::Point(-68.828, 43.021, 43.749), Jath::Point(-67.66, 44.644, 43.811), Jath::Point(-66.533, 46.297, 43.872), Jath::Point(-65.448, 47.977, 43.933), Jath::Point(-64.405, 49.683, 43.995), Jath::Point(-63.41, 51.418, 43.891), Jath::Point(-62.46, 53.178, 43.787), Jath::Point(-61.559, 54.963, 43.683), Jath::Point(-60.707, 56.773, 43.579), Jath::Point(-59.912, 58.608, 43.475), Jath::Point(-59.159, 60.461, 43.37), Jath::Point(-58.375, 62.3, 43.267), Jath::Point(-57.518, 64.107, 43.163), Jath::Point(-56.592, 65.88, 43.059), Jath::Point(-55.587, 67.608, 42.955), Jath::Point(-54.507, 69.292, 43.859), Jath::Point(-53.347, 70.921, 44.762), Jath::Point(-52.106, 72.488, 45.666), Jath::Point(-50.787, 73.992, 46.57), Jath::Point(-49.393, 75.425, 47.473), Jath::Point(-47.928, 76.786, 48.377), Jath::Point(-46.397, 78.073, 49.281), Jath::Point(-44.807, 79.285, 50.184), Jath::Point(-43.165, 80.427, 51.088), Jath::Point(-41.479, 81.502, 51.992), Jath::Point(-39.756, 82.517, 50.88), Jath::Point(-38.003, 83.481, 49.769), Jath::Point(-36.228, 84.402, 48.657), Jath::Point(-34.437, 85.291, 47.545), Jath::Point(-32.635, 86.159, 46.434), Jath::Point(-30.828, 87.016, 45.322), Jath::Point(-29.022, 87.876, 44.211), Jath::Point(-27.222, 88.748, 43.099), Jath::Point(-25.435, 89.646, 41.987), Jath::Point(-23.667, 90.581, 40.876), Jath::Point(-21.925, 91.563, 42.603), Jath::Point(-20.217, 92.603, 44.33), Jath::Point(-18.551, 93.709, 46.057), Jath::Point(-16.936, 94.889, 47.784), Jath::Point(-15.382, 96.147, 49.511), Jath::Point(-13.897, 97.487, 51.238), Jath::Point(-12.49, 98.907, 52.965), Jath::Point(-11.165, 100.405, 54.692), Jath::Point(-9.929, 101.977, 56.42), Jath::Point(-8.781, 103.614, 55.653), Jath::Point(-7.722, 105.31, 54.886), Jath::Point(-6.753, 107.059, 54.119), Jath::Point(-5.871, 108.854, 53.352), Jath::Point(-5.064, 110.684, 52.585), Jath::Point(-4.342, 112.549, 51.819), Jath::Point(-3.683, 114.437, 51.052), Jath::Point(-3.1, 116.35, 50.285), Jath::Point(-2.574, 118.279, 49.518), Jath::Point(-2.102, 120.223, 48.751), Jath::Point(-1.69, 122.18, 48.751), Jath::Point(-1.326, 124.146, 48.751), Jath::Point(-1.006, 126.121, 48.751), Jath::Point(-0.727, 128.101, 48.751), Jath::Point(-0.487, 130.086, 48.751), Jath::Point(-0.283, 132.076, 48.751), Jath::Point(-0.114, 134.069, 48.751), Jath::Point(0.025, 136.064, 48.751), Jath::Point(0.133, 138.061, 48.751), Jath::Point(0.215, 140.059, 48.751), Jath::Point(0.272, 142.058, 48.751), Jath::Point(0.305, 144.058, 48.751), Jath::Point(0.316, 146.058, 48.751), Jath::Point(0.308, 148.058, 48.751), Jath::Point(0.277, 150.058, 48.751), Jath::Point(0.226, 152.057, 48.751), Jath::Point(0.159, 154.056, 48.751), Jath::Point(0.077, 156.054, 48.751), Jath::Point(-0.021, 158.052, 48.751), Jath::Point(-0.137, 160.048, 48.751), Jath::Point(-0.391, 163.862, 48.75), Jath::Point(-0.391, 163.862, 0), 
};
Jath::Path rings1Path_UIL = Jath::Path::cm(rings1PathPoints_UIL);

std::vector<Jath::Point> rings1_5PathPoints_UIL = {
    Jath::Point(8.671, 160.354, 8), Jath::Point(8.415, 158.37, 84.059), Jath::Point(8.153, 156.387, 83.376), Jath::Point(7.885, 154.405, 82.694), Jath::Point(7.604, 152.425, 82.011), Jath::Point(7.315, 150.446, 81.328), Jath::Point(7.018, 148.468, 80.645), Jath::Point(6.71, 146.492, 79.963), Jath::Point(6.391, 144.518, 79.28), Jath::Point(6.063, 142.545, 78.597), Jath::Point(5.726, 140.574, 77.914), Jath::Point(5.374, 138.605, 77.231), Jath::Point(5.01, 136.638, 76.549), Jath::Point(4.636, 134.673, 75.866), Jath::Point(4.25, 132.711, 75.183), Jath::Point(3.85, 130.751, 74.5), Jath::Point(3.434, 128.795, 73.818), Jath::Point(3.005, 126.842, 73.135), Jath::Point(2.56, 124.892, 72.452), Jath::Point(2.1, 122.946, 71.769), Jath::Point(1.624, 121.003, 71.087), Jath::Point(1.13, 119.065, 70.404), Jath::Point(0.617, 117.132, 69.721), Jath::Point(0.085, 115.204, 69.038), Jath::Point(-0.468, 113.282, 68.355), Jath::Point(-1.044, 111.367, 67.673), Jath::Point(-1.643, 109.459, 66.99), Jath::Point(-2.268, 107.559, 66.307), Jath::Point(-2.92, 105.668, 65.624), Jath::Point(-3.6, 103.787, 64.942), Jath::Point(-4.312, 101.918, 64.259), Jath::Point(-5.056, 100.062, 63.576), Jath::Point(-5.836, 98.22, 62.893), Jath::Point(-6.656, 96.396, 62.211), Jath::Point(-7.522, 94.593, 61.528), Jath::Point(-8.432, 92.813, 60.845), Jath::Point(-9.396, 91.061, 60.162), Jath::Point(-10.419, 89.342, 59.48), Jath::Point(-11.506, 87.663, 58.797), Jath::Point(-12.663, 86.033, 57.027), Jath::Point(-13.906, 84.466, 51.136), Jath::Point(-15.237, 82.974, 44.134), Jath::Point(-16.669, 81.579, 36.015), Jath::Point(-18.212, 80.308, 26.952), Jath::Point(-19.871, 79.194, 17.41), Jath::Point(-21.648, 78.279, 14), Jath::Point(-23.533, 77.616, 14), Jath::Point(-25.494, 77.233, 14), Jath::Point(-27.491, 77.169, 14), Jath::Point(-29.474, 77.404, 14), Jath::Point(-31.404, 77.923, 15.464), Jath::Point(-33.257, 78.672, 24.787), Jath::Point(-35.019, 79.618, 37.923), Jath::Point(-36.687, 80.719, 45.509), Jath::Point(-38.269, 81.943, 47.872), Jath::Point(-39.769, 83.265, 47.19), Jath::Point(-41.192, 84.67, 46.507), Jath::Point(-42.548, 86.14, 45.824), Jath::Point(-43.846, 87.661, 45.141), Jath::Point(-45.083, 89.232, 44.459), Jath::Point(-46.274, 90.839, 43.776), Jath::Point(-47.415, 92.482, 43.093), Jath::Point(-48.517, 94.151, 42.41), Jath::Point(-49.578, 95.846, 41.728), Jath::Point(-50.602, 97.563, 41.045), Jath::Point(-51.595, 99.299, 40.362), Jath::Point(-52.558, 101.052, 39.679), Jath::Point(-53.489, 102.822, 39.713), Jath::Point(-54.394, 104.606, 39.746), Jath::Point(-55.273, 106.402, 39.78), Jath::Point(-56.129, 108.21, 39.814), Jath::Point(-56.963, 110.028, 39.847), Jath::Point(-57.775, 111.856, 39.881), Jath::Point(-58.567, 113.692, 39.914), Jath::Point(-59.339, 115.537, 39.948), Jath::Point(-60.093, 117.389, 39.982), Jath::Point(-60.83, 119.249, 40.01), Jath::Point(-61.479, 121.14, 40.049), Jath::Point(-62.104, 123.039, 40.082), Jath::Point(-62.739, 124.936, 40.116), Jath::Point(-63.384, 126.829, 40.15), Jath::Point(-64.042, 128.718, 40.183), Jath::Point(-64.713, 130.602, 45.943), Jath::Point(-65.398, 132.481, 51.703), Jath::Point(-66.097, 134.355, 57.463), Jath::Point(-66.813, 136.222, 63.222), Jath::Point(-67.547, 138.083, 68.982), Jath::Point(-68.3, 139.935, 74.742), Jath::Point(-69.076, 141.779, 78.798), Jath::Point(-69.876, 143.612, 77.868), Jath::Point(-70.703, 145.433, 76.82), Jath::Point(-71.563, 147.238, 74.301), Jath::Point(-72.459, 149.026, 72.792), Jath::Point(-73.393, 150.794, 71.085), Jath::Point(-74.377, 152.536, 66.981), Jath::Point(-75.412, 154.247, 64.527), Jath::Point(-76.514, 155.916, 58.663), Jath::Point(-77.69, 157.533, 51.336), Jath::Point(-78.954, 159.082, 42.385), Jath::Point(-80.325, 160.537, 31.846), Jath::Point(-81.818, 161.867, 20.123), Jath::Point(-83.449, 163.022, 14), Jath::Point(-85.22, 163.947, 14), Jath::Point(-87.115, 164.579, 14), Jath::Point(-89.089, 164.886, 14), Jath::Point(-91.087, 164.877, 14), Jath::Point(-93.067, 164.598, 25.052), Jath::Point(-95.006, 164.11, 41.86), Jath::Point(-96.9, 163.472, 47.291), Jath::Point(-98.756, 162.727, 45.631), Jath::Point(-100.58, 161.906, 43.97), Jath::Point(-102.382, 161.038, 42.31), Jath::Point(-104.17, 160.142, 40.649), Jath::Point(-105.951, 159.233, 38.989), Jath::Point(-107.732, 158.323, 37.328), Jath::Point(-109.519, 157.423, 35.668), Jath::Point(-111.314, 156.543, 34.007), Jath::Point(-113.123, 155.689, 32.347), Jath::Point(-114.947, 154.87, 30.686), Jath::Point(-116.79, 154.091, 29.026), Jath::Point(-118.651, 153.359, 29.026), Jath::Point(-120.531, 152.679, 29.026), Jath::Point(-122.433, 152.058, 29.026), Jath::Point(-124.353, 151.5, 29.026), Jath::Point(-126.291, 151.006, 29.026), Jath::Point(-128.244, 150.579, 29.026), Jath::Point(-130.213, 150.228, 29.026), Jath::Point(-132.194, 149.949, 29.026), Jath::Point(-134.183, 149.742, 29.026), Jath::Point(-136.179, 149.616, 29.026), Jath::Point(-138.178, 149.56, 29.026), Jath::Point(-140.177, 149.584, 29.026), Jath::Point(-142.175, 149.673, 29.026), Jath::Point(-144.988, 149.927, 29.02), Jath::Point(-144.988, 149.927, 0), 
};
Jath::Path rings1_5Path_UIL = Jath::Path::cm(rings1_5PathPoints_UIL);

std::vector<Jath::Point> rings1_6PathPoints_UIL = {
    Jath::Point(-153.768, 150.476, 57.74), Jath::Point(-151.768, 150.467, 57.745), Jath::Point(-149.768, 150.459, 57.745), Jath::Point(-147.768, 150.45, 57.745), Jath::Point(-145.768, 150.442, 57.745), Jath::Point(-143.768, 150.433, 57.745), Jath::Point(-141.768, 150.425, 57.745), Jath::Point(-139.768, 150.416, 57.745), Jath::Point(-137.768, 150.408, 57.745), Jath::Point(-135.768, 150.399, 57.745), Jath::Point(-133.768, 150.391, 57.745), Jath::Point(-131.768, 150.382, 57.745), Jath::Point(-129.769, 150.373, 57.745), Jath::Point(-127.769, 150.365, 57.745), Jath::Point(-125.769, 150.356, 57.745), Jath::Point(-123.769, 150.348, 57.745), Jath::Point(-121.769, 150.339, 57.745), Jath::Point(-119.769, 150.331, 57.745), Jath::Point(-117.769, 150.322, 57.745), Jath::Point(-115.769, 150.314, 57.745), Jath::Point(-113.769, 150.305, 57.745), Jath::Point(-111.769, 150.297, 57.745), Jath::Point(-109.769, 150.288, 57.745), Jath::Point(-107.769, 150.28, 57.745), Jath::Point(-105.769, 150.271, 57.745), Jath::Point(-103.769, 150.263, 57.745), Jath::Point(-101.769, 150.254, 57.745), Jath::Point(-99.769, 150.246, 57.745), Jath::Point(-97.769, 150.237, 57.745), Jath::Point(-95.769, 150.229, 57.745), Jath::Point(-93.769, 150.22, 57.745), Jath::Point(-91.769, 150.212, 57.745), Jath::Point(-89.769, 150.203, 57.745), Jath::Point(-87.769, 150.195, 57.745), Jath::Point(-85.769, 150.186, 57.745), Jath::Point(-83.769, 150.178, 57.745), Jath::Point(-81.769, 150.169, 57.745), Jath::Point(-79.769, 150.161, 57.745), Jath::Point(-77.769, 150.152, 57.745), Jath::Point(-75.769, 150.144, 57.745), Jath::Point(-73.769, 150.135, 57.745), Jath::Point(-71.769, 150.127, 57.745), Jath::Point(-69.769, 150.118, 57.745), Jath::Point(-67.769, 150.11, 57.745), Jath::Point(-65.769, 150.101, 57.745), Jath::Point(-63.769, 150.093, 57.745), Jath::Point(-61.769, 150.084, 57.745), Jath::Point(-59.769, 150.076, 57.745), Jath::Point(-57.769, 150.067, 57.745), Jath::Point(-55.769, 150.059, 57.745), Jath::Point(-53.769, 150.05, 57.745), Jath::Point(-51.769, 150.042, 57.745), Jath::Point(-49.769, 150.033, 57.745), Jath::Point(-47.769, 150.025, 57.745), Jath::Point(-45.769, 150.016, 57.745), Jath::Point(-43.769, 150.008, 57.745), Jath::Point(-41.769, 149.999, 57.745), Jath::Point(-39.769, 149.991, 57.745), Jath::Point(-37.769, 149.982, 57.745), Jath::Point(-35.769, 149.973, 57.745), Jath::Point(-33.769, 149.965, 57.745), Jath::Point(-31.769, 149.956, 57.745), Jath::Point(-29.769, 149.948, 57.745), Jath::Point(-27.769, 149.939, 57.745), Jath::Point(-24.805, 149.927, 57.74), Jath::Point(-24.805, 149.927, 0)};
Jath::Path rings1_6Path_UIL = Jath::Path::cm(rings1_6PathPoints_UIL);

std::vector<Jath::Point> rings1_75PathPoints_UIL = {
    Jath::Point(-21.512, 148.28, 48.67), Jath::Point(-22.671, 146.65, 51.081), Jath::Point(-23.771, 144.981, 55.824), Jath::Point(-24.818, 143.276, 59.711), Jath::Point(-25.819, 141.545, 66.564), Jath::Point(-26.785, 139.794, 74.278), Jath::Point(-27.729, 138.031, 72.133), Jath::Point(-28.667, 136.264, 69.989), Jath::Point(-29.616, 134.504, 65.627), Jath::Point(-30.596, 132.76, 54.303), Jath::Point(-31.626, 131.046, 42.843), Jath::Point(-32.726, 129.376, 31.864), Jath::Point(-33.913, 127.767, 22.196), Jath::Point(-35.2, 126.236, 14.783), Jath::Point(-36.594, 124.803, 14), Jath::Point(-38.094, 123.481, 14), Jath::Point(-39.693, 122.281, 14), Jath::Point(-41.378, 121.204, 18.098), Jath::Point(-43.136, 120.252, 22.919), Jath::Point(-44.952, 119.416, 30.983), Jath::Point(-46.815, 118.688, 36.503), Jath::Point(-48.713, 118.057, 39.967), Jath::Point(-50.637, 117.514, 37.822), Jath::Point(-52.582, 117.049, 38.255), Jath::Point(-54.543, 116.653, 38.687), Jath::Point(-56.514, 116.318, 39.12), Jath::Point(-58.494, 116.037, 39.552), Jath::Point(-60.481, 115.808, 39.985), Jath::Point(-62.472, 115.619, 40.417), Jath::Point(-64.467, 115.473, 40.85), Jath::Point(-66.463, 115.358, 41.282), Jath::Point(-68.462, 115.279, 42.702), Jath::Point(-70.461, 115.228, 44.121), Jath::Point(-72.461, 115.203, 45.541), Jath::Point(-74.461, 115.202, 46.96), Jath::Point(-76.461, 115.225, 48.38), Jath::Point(-78.46, 115.268, 49.799), Jath::Point(-80.459, 115.33, 51.219), Jath::Point(-82.458, 115.409, 52.638), Jath::Point(-84.455, 115.505, 54.058), Jath::Point(-86.452, 115.615, 55.477), Jath::Point(-88.448, 115.741, 56.897), Jath::Point(-90.444, 115.879, 58.316), Jath::Point(-92.438, 116.03, 59.736), Jath::Point(-94.431, 116.192, 57.233), Jath::Point(-96.424, 116.365, 54.73), Jath::Point(-98.415, 116.549, 52.227), Jath::Point(-100.406, 116.742, 49.725), Jath::Point(-102.396, 116.945, 47.222), Jath::Point(-104.384, 117.157, 44.719), Jath::Point(-106.372, 117.377, 42.216), Jath::Point(-108.359, 117.605, 39.713), Jath::Point(-110.345, 117.839, 37.21), Jath::Point(-112.331, 118.082, 37.21), Jath::Point(-114.315, 118.332, 37.21), Jath::Point(-116.299, 118.587, 37.21), Jath::Point(-118.281, 118.848, 37.2), Jath::Point(-120.263, 119.117, 37.21), Jath::Point(-122.258, 119.221, 37.21), Jath::Point(-124.257, 119.258, 37.21), Jath::Point(-126.257, 119.295, 37.21), Jath::Point(-128.257, 119.331, 37.21), Jath::Point(-130.256, 119.368, 37.21), Jath::Point(-132.256, 119.405, 37.21), Jath::Point(-134.256, 119.441, 37.21), Jath::Point(-136.255, 119.478, 37.21), Jath::Point(-138.255, 119.515, 37.21), Jath::Point(-140.255, 119.552, 37.21), Jath::Point(-142.254, 119.588, 37.21), Jath::Point(-144.254, 119.625, 37.21), Jath::Point(-146.254, 119.662, 37.21), Jath::Point(-148.253, 119.698, 37.21), Jath::Point(-149.758, 119.726, 37.2), Jath::Point(-149.758, 119.726, 0), 
};
Jath::Path rings1_75Path_UIL = Jath::Path::cm(rings1_75PathPoints_UIL);

std::vector<Jath::Point> goal3PathPoints_UIL = {
    Jath::Point(-177.88, -0.435, 90.46), Jath::Point(-176.216, -1.544, 90.462), Jath::Point(-174.556, -2.659, 90.24), Jath::Point(-172.9, -3.78, 90.008), Jath::Point(-171.25, -4.912, 90.008), Jath::Point(-169.607, -6.051, 89.766), Jath::Point(-167.969, -7.199, 89.514), Jath::Point(-166.336, -8.354, 89.252), Jath::Point(-164.711, -9.52, 89.252), Jath::Point(-163.093, -10.695, 88.98), Jath::Point(-161.481, -11.88, 88.697), Jath::Point(-159.877, -13.074, 88.406), Jath::Point(-158.28, -14.278, 88.104), Jath::Point(-156.691, -15.493, 88.104), Jath::Point(-155.112, -16.72, 87.795), Jath::Point(-153.542, -17.958, 87.477), Jath::Point(-151.98, -19.208, 87.151), Jath::Point(-150.429, -20.47, 86.82), Jath::Point(-148.888, -21.745, 86.484), Jath::Point(-147.358, -23.033, 86.144), Jath::Point(-145.839, -24.334, 85.803), Jath::Point(-144.332, -25.649, 85.463), Jath::Point(-142.837, -26.978, 85.126), Jath::Point(-141.356, -28.322, 84.795), Jath::Point(-139.889, -29.681, 84.164), Jath::Point(-138.437, -31.057, 83.871), Jath::Point(-137, -32.448, 83.6), Jath::Point(-135.579, -33.855, 83.355), Jath::Point(-134.173, -35.278, 82.963), Jath::Point(-132.787, -36.719, 82.829), Jath::Point(-131.417, -38.176, 82.744), Jath::Point(-130.065, -39.65, 82.749), Jath::Point(-128.733, -41.142, 82.853), Jath::Point(-127.418, -42.648, 83.298), Jath::Point(-126.122, -44.172, 83.074), Jath::Point(-124.843, -45.71, 82.779), Jath::Point(-123.581, -47.261, 82.484), Jath::Point(-122.335, -48.825, 82.189), Jath::Point(-121.101, -50.399, 81.894), Jath::Point(-119.878, -51.981, 81.599), Jath::Point(-118.661, -53.569, 81.304), Jath::Point(-117.446, -55.157, 81.009), Jath::Point(-116.228, -56.744, 80.714), Jath::Point(-115.001, -58.323, 80.42), Jath::Point(-113.758, -59.89, 79.458), Jath::Point(-112.493, -61.439, 75.472), Jath::Point(-111.2, -62.965, 71.807), Jath::Point(-109.874, -64.462, 68.648), Jath::Point(-108.51, -65.924, 66.151), Jath::Point(-107.104, -67.347, 64.428), Jath::Point(-105.656, -68.726, 63.532), Jath::Point(-104.165, -70.059, 63.45), Jath::Point(-102.632, -71.343, 64.113), Jath::Point(-101.059, -72.579, 65.403), Jath::Point(-99.45, -73.767, 67.175), Jath::Point(-97.806, -74.906, 68.194), Jath::Point(-96.132, -75.999, 70.405), Jath::Point(-94.432, -77.052, 72.736), Jath::Point(-92.705, -78.061, 73.91), Jath::Point(-90.958, -79.036, 75.701), Jath::Point(-89.191, -79.972, 75.406), Jath::Point(-87.408, -80.878, 75.111), Jath::Point(-85.609, -81.752, 74.816), Jath::Point(-83.797, -82.598, 74.521), Jath::Point(-81.974, -83.419, 74.226), Jath::Point(-80.14, -84.218, 73.931), Jath::Point(-78.296, -84.992, 73.637), Jath::Point(-76.443, -85.746, 73.342), Jath::Point(-74.583, -86.481, 73.047), Jath::Point(-72.717, -87.199, 72.752), Jath::Point(-70.844, -87.9, 72.457), Jath::Point(-68.965, -88.587, 72.162), Jath::Point(-67.082, -89.259, 71.867), Jath::Point(-65.194, -89.918, 71.572), Jath::Point(-63.301, -90.565, 71.277), Jath::Point(-61.405, -91.201, 70.98), Jath::Point(-59.505, -91.826, 70.687), Jath::Point(-57.533, -92.153, 70.393), Jath::Point(-55.558, -92.466, 70.098), Jath::Point(-53.584, -92.787, 69.803), Jath::Point(-51.611, -93.113, 69.508), Jath::Point(-49.638, -93.444, 69.213), Jath::Point(-47.667, -93.779, 68.918), Jath::Point(-45.695, -94.117, 68.623), Jath::Point(-43.724, -94.456, 68.328), Jath::Point(-41.753, -94.795, 68.033), Jath::Point(-39.782, -95.133, 67.738), Jath::Point(-37.81, -95.468, 67.443), Jath::Point(-35.838, -95.799, 67.149), Jath::Point(-33.865, -96.124, 66.854), Jath::Point(-31.89, -96.441, 66.559), Jath::Point(-29.914, -96.749, 66.264), Jath::Point(-27.936, -97.044, 65.969), Jath::Point(-25.955, -97.326, 65.674), Jath::Point(-23.973, -97.591, 65.379), Jath::Point(-21.988, -97.837, 65.084), Jath::Point(-20.001, -98.062, 64.789), Jath::Point(-18.011, -98.262, 64.494), Jath::Point(-16.019, -98.435, 64.199), Jath::Point(-14.024, -98.576, 63.904), Jath::Point(-12.027, -98.684, 63.61), Jath::Point(-10.028, -98.753, 63.315), Jath::Point(-8.028, -98.78, 63.02), Jath::Point(-6.028, -98.761, 62.725), Jath::Point(-4.029, -98.692, 62.43), Jath::Point(-2.033, -98.568, 62.135), Jath::Point(-0.042, -98.386, 61.84), Jath::Point(1.943, -98.142, 61.545), Jath::Point(3.919, -97.831, 59.765), Jath::Point(5.882, -97.449, 60.955), Jath::Point(7.829, -96.994, 57.645), Jath::Point(9.757, -96.463, 54.334), Jath::Point(11.663, -95.855, 51.024), Jath::Point(13.541, -95.17, 47.714), Jath::Point(15.389, -94.406, 44.403), Jath::Point(17.204, -93.566, 41.093), Jath::Point(18.982, -92.65, 37.782), Jath::Point(20.719, -91.66, 34.472), Jath::Point(22.415, -90.6, 31.161), Jath::Point(24.068, -89.473, 27.851), Jath::Point(25.676, -88.284, 24.54), Jath::Point(27.239, -87.036, 27.918), Jath::Point(28.756, -85.734, 31.296), Jath::Point(30.23, -84.382, 34.674), Jath::Point(31.66, -82.984, 38.052), Jath::Point(33.049, -81.545, 41.43), Jath::Point(34.394, -80.065, 44.807), Jath::Point(35.7, -78.551, 48.185), Jath::Point(36.97, -77.005, 48.185), Jath::Point(38.199, -75.428, 48.185), Jath::Point(39.454, -73.888, 48.18), Jath::Point(41.139, -72.81, 48.185), Jath::Point(42.799, -71.695, 48.185), Jath::Point(44.433, -70.541, 48.185), Jath::Point(46.036, -69.346, 48.185), Jath::Point(47.612, -68.115, 48.185), Jath::Point(49.157, -66.844, 48.185), Jath::Point(50.671, -65.538, 48.185), Jath::Point(52.155, -64.197, 48.185), Jath::Point(53.608, -62.823, 48.185), Jath::Point(55.03, -61.416, 48.185), Jath::Point(56.424, -59.983, 48.185), Jath::Point(57.789, -58.52, 48.185), Jath::Point(59.128, -57.035, 48.185), Jath::Point(60.445, -55.53, 48.185), Jath::Point(61.74, -54.006, 48.185), Jath::Point(63.019, -52.468, 48.185), Jath::Point(64.286, -50.921, 48.185), Jath::Point(65.546, -49.367, 48.185), Jath::Point(66.805, -47.813, 48.185), Jath::Point(68.069, -46.264, 48.185), Jath::Point(69.347, -44.725, 48.185), Jath::Point(70.645, -43.204, 48.185), Jath::Point(71.974, -41.709, 48.185), Jath::Point(73.341, -40.249, 48.185), Jath::Point(74.755, -38.835, 48.185), Jath::Point(76.225, -37.48, 47.309), Jath::Point(77.761, -36.198, 37.463), Jath::Point(79.365, -35.004, 31.975), Jath::Point(81.039, -33.911, 27.849), Jath::Point(82.782, -32.932, 25.447), Jath::Point(84.589, -32.076, 24.986), Jath::Point(86.452, -31.35, 26.477), Jath::Point(88.361, -30.756, 29.717), Jath::Point(90.306, -30.29, 34.33), Jath::Point(92.276, -29.947, 39.851), Jath::Point(94.262, -29.715, 45.813), Jath::Point(96.257, -29.587, 48.185), Jath::Point(98.257, -29.558, 48.185), Jath::Point(100.256, -29.607, 48.185), Jath::Point(102.252, -29.738, 48.185), Jath::Point(104.242, -29.93, 48.185), Jath::Point(106.226, -30.187, 48.185), Jath::Point(108.201, -30.497, 48.185), Jath::Point(110.169, -30.854, 48.185), Jath::Point(112.129, -31.252, 48.185), Jath::Point(114.08, -31.694, 48.185), Jath::Point(116.022, -32.17, 48.185), Jath::Point(117.956, -32.678, 48.185), Jath::Point(119.883, -33.215, 48.185), Jath::Point(121.802, -33.778, 48.185), Jath::Point(123.714, -34.366, 48.185), Jath::Point(125.618, -34.976, 48.185), Jath::Point(127.516, -35.606, 48.185), Jath::Point(129.408, -36.255, 48.185), Jath::Point(131.293, -36.924, 48.185), Jath::Point(133.172, -37.609, 48.185), Jath::Point(135.046, -38.309, 48.185), Jath::Point(136.914, -39.022, 48.185), Jath::Point(138.778, -39.748, 48.185), Jath::Point(140.636, -40.487, 48.185), Jath::Point(142.489, -41.239, 48.185), Jath::Point(144.339, -42.001, 48.185), Jath::Point(146.184, -42.772, 48.185), Jath::Point(148.024, -43.555, 48.185), Jath::Point(149.861, -44.347, 48.185), Jath::Point(151.695, -45.145, 48.185), Jath::Point(153.524, -45.954, 48.185), Jath::Point(155.35, -46.77, 48.185), Jath::Point(157.173, -47.592, 48.185), Jath::Point(158.992, -48.424, 48.185), Jath::Point(160.808, -49.261, 48.185), Jath::Point(162.622, -50.103, 48.185), Jath::Point(165.869, -51.631, 48.18), Jath::Point(165.869, -51.631, 0), 
};
Jath::Path goal3Path_UIL = Jath::Path::cm(goal3PathPoints_UIL);

std::vector<Jath::Point> RingsFinal1Points_UIL = {
    Jath::Point(120.477, -0.435, 97.64),
    Jath::Point(120.31, -2.428, 97.644),
    Jath::Point(120.133, -4.42, 97.46),
    Jath::Point(119.948, -6.411, 96.369),
    Jath::Point(119.753, -8.402, 94.825),
    Jath::Point(119.549, -10.391, 93.281),
    Jath::Point(119.333, -12.38, 91.737),
    Jath::Point(119.107, -14.367, 90.194),
    Jath::Point(118.868, -16.352, 88.65),
    Jath::Point(118.616, -18.337, 87.106),
    Jath::Point(118.351, -20.319, 85.562),
    Jath::Point(118.073, -22.299, 84.018),
    Jath::Point(117.78, -24.278, 82.475),
    Jath::Point(117.471, -26.254, 80.931),
    Jath::Point(117.146, -28.227, 79.387),
    Jath::Point(116.802, -30.198, 77.843),
    Jath::Point(116.44, -32.164, 76.3),
    Jath::Point(116.057, -34.127, 74.756),
    Jath::Point(115.654, -36.086, 73.212),
    Jath::Point(115.227, -38.04, 71.668),
    Jath::Point(114.777, -39.989, 70.124),
    Jath::Point(114.298, -41.931, 68.581),
    Jath::Point(113.79, -43.865, 67.037),
    Jath::Point(113.252, -45.791, 65.493),
    Jath::Point(112.678, -47.707, 63.949),
    Jath::Point(112.066, -49.611, 60.747),
    Jath::Point(111.414, -51.502, 57.545),
    Jath::Point(110.716, -53.376, 54.343),
    Jath::Point(109.967, -55.23, 51.141),
    Jath::Point(109.163, -57.062, 47.939),
    Jath::Point(108.296, -58.864, 44.736),
    Jath::Point(107.358, -60.63, 41.534),
    Jath::Point(106.343, -62.353, 38.332),
    Jath::Point(105.242, -64.022, 38.248),
    Jath::Point(104.044, -65.623, 38.163),
    Jath::Point(102.737, -67.136, 38.079),
    Jath::Point(101.316, -68.543, 32.963),
    Jath::Point(99.774, -69.815, 23.157),
    Jath::Point(98.112, -70.925, 18),
    Jath::Point(96.334, -71.839, 18),
    Jath::Point(94.462, -72.538, 18),
    Jath::Point(92.519, -73.008, 18),
    Jath::Point(90.535, -73.25, 22.822),
    Jath::Point(88.536, -73.278, 32.11),
    Jath::Point(86.544, -73.108, 37.321),
    Jath::Point(84.574, -72.77, 37.237),
    Jath::Point(82.633, -72.289, 37.152),
    Jath::Point(80.727, -71.684, 37.068),
    Jath::Point(78.857, -70.975, 36.984),
    Jath::Point(77.022, -70.179, 38.869),
    Jath::Point(75.222, -69.309, 40.754),
    Jath::Point(73.453, -68.375, 42.639),
    Jath::Point(71.715, -67.386, 44.524),
    Jath::Point(70.004, -66.351, 46.41),
    Jath::Point(68.319, -65.273, 48.295),
    Jath::Point(66.658, -64.16, 50.18),
    Jath::Point(65.017, -63.016, 52.065),
    Jath::Point(63.397, -61.844, 53.95),
    Jath::Point(61.794, -60.648, 55.83),
    Jath::Point(60.263, -59.364, 57.721),
    Jath::Point(58.805, -57.995, 59.606),
    Jath::Point(57.347, -56.626, 61.491),
    Jath::Point(55.889, -55.257, 63.376),
    Jath::Point(54.432, -53.887, 69.647),
    Jath::Point(52.975, -52.517, 75.918),
    Jath::Point(51.518, -51.147, 82.188),
    Jath::Point(50.062, -49.776, 88.459),
    Jath::Point(48.607, -48.404, 94.729),
    Jath::Point(47.153, -47.031, 101),
    Jath::Point(45.7, -45.656, 100.431),
    Jath::Point(44.249, -44.279, 99.863),
    Jath::Point(42.801, -42.901, 99.294),
    Jath::Point(41.355, -41.518, 98.725),
    Jath::Point(39.913, -40.132, 98.157),
    Jath::Point(38.477, -38.74, 97.588),
    Jath::Point(37.047, -37.342, 97.019),
    Jath::Point(35.626, -35.935, 96.451),
    Jath::Point(34.212, -34.52, 95.882),
    Jath::Point(32.807, -33.097, 95.313),
    Jath::Point(31.407, -31.669, 94.744),
    Jath::Point(30.011, -30.236, 94.176),
    Jath::Point(28.617, -28.802, 93.607),
    Jath::Point(27.224, -27.367, 93.038),
    Jath::Point(25.83, -25.933, 88.994),
    Jath::Point(24.436, -24.5, 84.949),
    Jath::Point(23.04, -23.067, 80.904),
    Jath::Point(21.643, -21.636, 76.859),
    Jath::Point(20.245, -20.205, 72.814),
    Jath::Point(18.846, -18.776, 68.769),
    Jath::Point(17.446, -17.348, 64.725),
    Jath::Point(16.044, -15.921, 60.68),
    Jath::Point(14.642, -14.495, 56.635),
    Jath::Point(13.239, -13.07, 52.59),
    Jath::Point(11.835, -11.646, 48.545),
    Jath::Point(10.43, -10.223, 44.5),
    Jath::Point(9.024, -8.8, 40.456),
    Jath::Point(7.617, -7.378, 36.411),
    Jath::Point(6.21, -5.957, 36.411),
    Jath::Point(4.802, -4.536, 36.411),
    Jath::Point(3.394, -3.117, 36.411),
    Jath::Point(1.985, -1.697, 36.411),
    Jath::Point(0.575, -0.278, 36.411),
    Jath::Point(-0.835, 1.14, 36.411),
    Jath::Point(-2.246, 2.558, 36.411),
    Jath::Point(-3.657, 3.975, 36.411),
    Jath::Point(-5.068, 5.392, 36.411),
    Jath::Point(-6.48, 6.808, 36.411),
    Jath::Point(-7.893, 8.224, 36.411),
    Jath::Point(-9.306, 9.64, 36.411),
    Jath::Point(-10.719, 11.055, 36.411),
    Jath::Point(-12.132, 12.47, 36.411),
    Jath::Point(-14.265, 14.603, 36.41),
    Jath::Point(-14.265, 14.603, 0),
};
Jath::Path RingsFinal1_UIL = Jath::Path::cm(RingsFinal1Points_UIL);

std::vector<Jath::Point> RingsFinal2Points_UIL = {
    Jath::Point(122.882, -4.522, 82.17), Jath::Point(121.788, -2.848, 81.986), Jath::Point(120.684, -1.181, 81.792), Jath::Point(119.571, 0.481, 81.592), Jath::Point(118.447, 2.135, 81.171), Jath::Point(117.312, 3.782, 80.951), Jath::Point(116.166, 5.421, 80.01), Jath::Point(115.007, 7.051, 78.94), Jath::Point(113.836, 8.672, 77.87), Jath::Point(112.651, 10.284, 76.8), Jath::Point(111.453, 11.885, 75.729), Jath::Point(110.24, 13.475, 74.659), Jath::Point(109.012, 15.054, 73.589), Jath::Point(107.768, 16.62, 72.519), Jath::Point(106.506, 18.172, 71.449), Jath::Point(105.228, 19.709, 70.379), Jath::Point(103.931, 21.232, 69.308), Jath::Point(102.614, 22.738, 68.238), Jath::Point(101.278, 24.226, 67.168), Jath::Point(99.921, 25.695, 66.098), Jath::Point(98.543, 27.144, 65.028), Jath::Point(97.142, 28.572, 63.958), Jath::Point(95.719, 29.977, 62.888), Jath::Point(94.274, 31.359, 61.817), Jath::Point(92.805, 32.716, 60.747), Jath::Point(91.313, 34.049, 59.677), Jath::Point(89.799, 35.356, 58.607), Jath::Point(88.265, 36.638, 57.537), Jath::Point(86.71, 37.896, 56.467), Jath::Point(85.137, 39.131, 55.397), Jath::Point(83.547, 40.345, 54.326), Jath::Point(81.945, 41.542, 53.256), Jath::Point(80.333, 42.725, 52.186), Jath::Point(78.713, 43.899, 51.116), Jath::Point(77.091, 45.068, 50.046), Jath::Point(75.469, 46.238, 48.976), Jath::Point(73.851, 47.414, 47.906), Jath::Point(72.241, 48.601, 46.835), Jath::Point(70.643, 49.804, 45.765), Jath::Point(69.059, 51.025, 44.695), Jath::Point(67.493, 52.269, 43.625), Jath::Point(65.946, 53.536, 42.555), Jath::Point(64.42, 54.829, 44.388), Jath::Point(62.918, 56.149, 46.22), Jath::Point(61.438, 57.495, 48.053), Jath::Point(59.983, 58.867, 49.88), Jath::Point(58.644, 60.351, 51.718), Jath::Point(57.363, 61.887, 53.551), Jath::Point(56.126, 63.459, 55.383), Jath::Point(54.939, 65.068, 57.216), Jath::Point(53.81, 66.718, 59.049), Jath::Point(52.74, 68.408, 60.881), Jath::Point(51.738, 70.138, 62.714), Jath::Point(50.814, 71.912, 59.364), Jath::Point(49.975, 73.728, 56.014), Jath::Point(49.229, 75.583, 52.664), Jath::Point(48.583, 77.476, 49.314), Jath::Point(48.048, 79.402, 45.964), Jath::Point(47.632, 81.358, 42.614), Jath::Point(47.338, 83.336, 39.264), Jath::Point(47.168, 85.328, 35.914), Jath::Point(47.127, 87.328, 32.564), Jath::Point(47.214, 89.325, 34.104), Jath::Point(47.42, 91.314, 35.644), Jath::Point(47.745, 93.287, 37.185), Jath::Point(48.176, 95.24, 38.725), Jath::Point(48.706, 97.168, 40.265), Jath::Point(49.326, 99.07, 41.805), Jath::Point(50.023, 100.944, 43.345), Jath::Point(50.792, 102.79, 44.885), Jath::Point(51.62, 104.611, 46.425), Jath::Point(52.499, 106.407, 47.965), Jath::Point(53.424, 108.18, 47.965), Jath::Point(54.385, 109.934, 47.965), Jath::Point(55.375, 111.672, 47.965), Jath::Point(56.389, 113.396, 47.965), Jath::Point(57.419, 115.11, 47.965), Jath::Point(58.461, 116.817, 47.965), Jath::Point(59.508, 118.521, 47.965), Jath::Point(60.556, 120.225, 47.965), Jath::Point(61.598, 121.932, 47.965), Jath::Point(62.628, 123.646, 47.965), Jath::Point(63.64, 125.371, 47.965), Jath::Point(64.629, 127.11, 47.965), Jath::Point(65.587, 128.865, 47.965), Jath::Point(66.505, 130.642, 47.965), Jath::Point(67.378, 132.441, 47.965), Jath::Point(68.194, 134.267, 47.965), Jath::Point(68.945, 136.121, 47.965), Jath::Point(69.619, 138.004, 46.268), Jath::Point(70.205, 139.916, 42.577), Jath::Point(70.474, 140.925, 40.7), Jath::Point(70.474, 140.925, 0),
};
Jath::Path RingsFinal2_UIL = Jath::Path::cm(RingsFinal2Points_UIL);

void skills_UIL()
{
    vex::thread antiJamTask(intakeAntiJam);

    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2.5), art::Tiles(0));
    smartDrive.m_dir = art::Degrees(-90);

    // resetPositionFromGPSL();

    arm.set(100);
    vex::wait(1, vex::seconds);
    arm.set(0);
    arm.stop(vex::hold);

    smartDrive.driveForPID(art::Inches(-5));

    armTarget = art::Degrees(0);
    vex::thread armControl(autonArmPos);

    // followPathRev(goal1Path, art::Inches(13));

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(-2.15), art::Tiles(0.95)
    ));

    // maybe add additional drive
    smartDrive.driveForPID(art::Inches(-2));
    clamp.set(true);
    smartDrive.arcade(0,0);

    vex::wait(0.75, vex::sec);

    resetPositionFromGPSL();

    intake.set(100);
    followPath(rings1Path_UIL, art::Inches(13));

    // antiJamTask.interrupt();//new
    // armTarget = art::Degrees(10);

    // smartDrive.arcade(40, 0);
    // vex::wait(0.25,vex::sec);
    // smartDrive.arcade(-40, 0);
    // vex::wait(0.125,vex::sec);
    // smartDrive.arcade(30, 0);
    // vex::wait(0.25,vex::sec);


    // intake.set(0);

    // armTarget = art::Degrees(135);

    // vex::wait(1, vex::sec);

    // smartDrive.arcade(-25,0);
    // vex::wait(.125, vex::sec);

    // smartDrive.arcade(75,0);
    // vex::wait(.25, vex::sec);
    
    // smartDrive.driveForPID(art::Inches(-10));

    // antiJamTask = vex::thread(intakeAntiJam);

    smartDrive.driveForPID(art::Inches(-3));//orig
    smartDrive.turnForPID(art::Degrees(165));
    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec);
    resetPositionFromGPSL();

    smartDrive.arcade(0,0);
    vex::wait(0.15, vex::sec);
    localizeAvg();

    // followPath(rings1_5Path, art::Inches(13));
    // smartDrive.driveForPID(art::Inches(5));

    // followPathRev(rings1_6Path, art::Inches(13));

    followPath(rings1_75Path_UIL, art::Inches(13));
    smartDrive.arcade(75, 0);
    vex::wait( 0.3,vex::sec);

    smartDrive.driveForPID(art::Inches(-5));

    target = art::Vec2::XandY(art::Tiles(-2.75), art::Tiles(2.75));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.arcade(-75, 0);
    vex::wait(1,vex::sec);

    clamp.set(false);
    intake.set(0);

    smartDrive.driveForPID(art::Inches(24));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPSL();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(-2), art::Tiles(0)
    ));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPSL();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(-2), art::Tiles(-0.95)
    ));

    // maybe add additional drive
    smartDrive.driveForPID(art::Inches(-2));
    clamp.set(true);
    smartDrive.arcade(0,0);

    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec);
    resetPositionFromGPSL();

    intake.set(100);
    followPath_flipY(rings1Path_UIL, art::Inches(13));
    smartDrive.arcade(40, 0);
    vex::wait( 0.3,vex::sec);

    smartDrive.driveForPID(art::Inches(-3));
    smartDrive.turnForPID(art::Degrees(-15));
    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec); logger.logStringEntry(Auton_Console, "Waiting to reset");
    resetPositionFromGPSL();

    // followPath_flipY(rings1_5Path, art::Inches(13));
    // smartDrive.driveForPID(art::Inches(5));

    // followPathRev_flipY(rings1_6Path, art::Inches(13));

    followPath_flipY(rings1_75Path_UIL, art::Inches(13));
    smartDrive.arcade(75, 0);
    vex::wait( 0.3,vex::sec);

    smartDrive.driveForPID(art::Inches(-5));

    target = art::Vec2::XandY(art::Tiles(-2.75), art::Tiles(2.75 * -1.0));
    travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.arcade(-75, 0);
    vex::wait(1,vex::sec);

    clamp.set(false);
    intake.set(0);

    smartDrive.driveForPID(art::Inches(48));

    //End of Red

    smartDrive.turnToPID(art::Degrees(135));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPSL(); // Delete this

    smartDrive.arcade(0,0);
    vex::wait(0.75, vex::sec);
    resetPositionFromGPSL();

    intake.set(100);
    followPath(goal3Path_UIL, art::Inches(13));

    // smartDrive.arcade(0,0);
    // vex::wait(0.75, vex::sec);
    // resetPositionFromGPSL();

    // target = art::Vec2::XandY(art::Tiles(2.5), art::Tiles(-1.0));
    // travel = art::Vec2(target - smartDrive.m_pos);

    smartDrive.turnToPID(art::Degrees(135));
    intake.set(-100);

    smartDrive.arcade(75, 0);
    vex::wait(1.75, vex::sec);

    smartDrive.driveForPID(art::Inches(-54));
    smartDrive.turnToPID(art::Degrees(60));
    intake.set(0);

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPSL();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(2), art::Tiles(-1.0)
    ));

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPSL();

    driveTowardPointRev(art::Vec2::XandY(
        art::Tiles(2), art::Tiles(0.0)
    ));

    // maybe add additional drive
    smartDrive.driveForPID(art::Inches(-3));
    clamp.set(true);
    smartDrive.arcade(0,0);

    smartDrive.arcade(0,0);
    vex::wait(0.5, vex::sec);
    resetPositionFromGPSL();

    intake.set(100);

    // followPath(RingsFinal1, art::Inches(13));
    // smartDrive.turnToPID(art::Degrees(45));
    
    followPath(RingsFinal2_UIL, art::Inches(13));

    smartDrive.driveForPID(art::Inches(5));
    smartDrive.driveForPID(art::Inches(-5));

    // smartDrive.arcade(0,0);
    // vex::wait(0.5, vex::sec);
    // resetPositionFromGPSL();

    // driveTowardPoint(art::Vec2::XandY(
    //     art::Tiles(2),art::Tiles(1.95)
    // ));

    // smartDrive.driveForPID(art::Inches(-15));

    // driveTowardPoint(art::Vec2::XandY(
    //     art::Tiles(2),art::Tiles(2.5)
    // ));

    // smartDrive.driveForPID(art::Inches(-5));

    // smartDrive.arcade(0,0);
    // vex::wait(0.5, vex::sec);
    // resetPositionFromGPSL();

    // target = art::Vec2::XandY(art::Tiles(2.75), art::Tiles(2.75));
    // travel = art::Vec2(target - smartDrive.m_pos);

    // smartDrive.turnForPID(art::Degrees(travel.direction()) + art::Degrees(180));

    smartDrive.turnToPID(art::Degrees(-135));
    smartDrive.arcade(-75, 0);
    vex::wait(1.75, vex::sec);

    clamp.set(false);
    intake.set(0);

    smartDrive.driveForPID(art::Inches(24));

    smartDrive.arcade(0, 0);
}
