#include "AutonSelect.h"
#include "Autons.h"
#include "Autons/FlippingAutons.h"
#include "Autons/SoloAWP.h"

// Current Autons
/*
void flippingAWPAuton();

void centerRings();
void centerRingsWWallstake();
void ringSideToCorner();

void skills();*/

Auton RedFlippingAWPNeg("Red Flipping AWP Neg", []()
                        { flippingAWPAuton_redNeg(); });
Auton BlueFlippingAWPNeg("Blue Flipping AWP Neg", []()
                         { flippingAWPAuton_blueNeg(); });

Auton RedFlippingAWPPos("Red Flipping AWP Pos", []()
                        { flippingAWPAuton_redPos(); });
Auton BlueFlippingAWPPos("Blue Flipping AWP Pos", []()
                         { flippingAWPAuton_bluePos(); });

Auton RedSoloAWP_part2("Red Solo AWP Part2", []()
                       { redSoloAWP_part2(); });

Auton RedSoloAWP("Red Solo AWP", []()
                 { redSoloAWP(); });
Auton BlueSoloAWP("Blue Solo AWP", []()
                  { blueSoloAWP(); });

Auton BlueSimpleAWPPos("Blue Simple AWP (Pos)", []()
                       { blueSimplAWP(); });
Auton RedSimpleAWPPos("Red Simple AWP (Pos)", []()
                      { redSimplAWP(); });

Auton BlueSimpleAWPNeg("Blue Simple AWP (Neg)", []()
                       { blueSimplAWPNeg(); });
Auton RedSimpleAWPNeg("Red Simple AWP (Neg)", []()
                      { redSimplAWPNeg(); });

Auton BlueSoloAWPNeg("Blue Solo AWP (NEG)", []()
                     { blueSoloAWPNeg(); });

Auton RedCenterRingsPos("Red Center Rings Pos", []()
                        { asyncDrive.setXFlip(true); centerRings(); });
Auton BlueCenterRingsPos("Blue Center Rings Pos", []()
                         { centerRings(); });

Auton RedCenterRingsNeg("Red(Wall) Center Rings Neg", []()
                        { centerRingsWWallstake(); });
Auton BlueCenterRingsNeg("Blue(Wall) Center Rings Neg", []()
                         { asyncDrive.setXFlip(true); centerRingsWWallstake; });

Auton RedRingsToCorner("Red Rings To Corner", []()
                       { centerRings(); });
Auton BlueRingsToCorner("Blue Rings To Corner", []()
                        { asyncDrive.setXFlip(true); centerRings(); });

Auton SimpleSkills("Simple Skills", simpleSkills);
Auton Skills("Skills", skills);

Auton Drive5In("Drive 5 Inches {Backward}", []()
               { asyncDrive.driveForS(art::Inches(-5)); });

std::vector<Auton> autons = {
    RedFlippingAWPNeg,
    RedFlippingAWPPos,
    BlueFlippingAWPNeg,
    BlueFlippingAWPPos,
    RedSoloAWP,
    BlueSoloAWP,
    BlueSimpleAWPPos,
    RedSimpleAWPPos,
    BlueSimpleAWPNeg,
    RedSimpleAWPNeg,
    RedSoloAWP_part2,
    BlueSoloAWPNeg,
    RedCenterRingsPos,
    BlueCenterRingsPos,
    RedCenterRingsNeg,
    BlueCenterRingsNeg,
    BlueRingsToCorner,
    RedRingsToCorner,
    Drive5In,
    SimpleSkills,
    Skills};

AutonSelect autonSelect(autons);
int currentAutonId = 0;
int currentAutonView = 0;

void incAutonView()
{
    if (currentAutonView < autons.size() - 2)
        currentAutonView++;
}
void decAutonView()
{
    if (currentAutonView > 0)
        currentAutonView--;
}
void resetAutonView() { currentAutonView = 0; }

void selectAutonLeft() { currentAutonId = currentAutonView; };
void selectAutonRight() { currentAutonId = currentAutonView + 1; };