#include "AutonSelect.h"
#include "Autons.h"

// Current Autons
/*
void flippingAWPAuton();

void centerRings();
void centerRingsWWallstake();
void ringSideToCorner();

void skills();*/

Auton SimpleSkills("Simple Skills", simpleSkills);
Auton Skills("Skills", skills);

Auton Drive5In("Drive 5 Inches {Backward}", []()
                        { asyncDrive.driveForS(art::Inches(-5)); });

Auton RedCenterRingsPos("Red Center Rings Pos", []()
                        { asyncDrive.setXFlip(true); centerRings(); });
Auton BlueCenterRingsPos("Blue Center Rings Pos", []()
                         { centerRings(); });

Auton RedCenterRingsNeg("Red(Wall) Center Rings Neg", []()
                        { centerRingsWWallstake(); });
Auton BlueCenterRingsNeg("Blue(Wall) Center Rings Neg", []()
                         { asyncDrive.setXFlip(true); centerRingsWWallstake; });

Auton RedFlippingAWPNeg("Red Flipping AWP Neg", []()
                        { flippingAWPAuton(); });
Auton BlueFlippingAWPNeg("Blue Flipping AWP Neg", []()
                         { asyncDrive.setXFlip(true); flippingAWPAuton(); });

Auton RedFlippingAWPPos("Red Flipping AWP Pos", []()
                        { asyncDrive.setYFlip(true); flippingAWPAuton(); });
Auton BlueFlippingAWPPos("Blue Flipping AWP Pos", []()
                         { asyncDrive.setYFlip(true); asyncDrive.setXFlip(true); flippingAWPAuton(); });

Auton RedRingsToCorner("Red Rings To Corner", []()
                       { centerRings(); });
Auton BlueRingsToCorner("Blue Rings To Corner", []()
                        { asyncDrive.setXFlip(true); centerRings(); });

std::vector<Auton> autons = {
    SimpleSkills,
    Skills,
    Drive5In,
    RedCenterRingsPos,
    BlueCenterRingsPos,
    RedCenterRingsNeg,
    BlueCenterRingsNeg,
    RedFlippingAWPNeg,
    RedFlippingAWPPos,
    BlueFlippingAWPNeg,
    BlueFlippingAWPPos,
    RedRingsToCorner,
    BlueRingsToCorner};

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