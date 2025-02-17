#include "AutonSelect.h"
#include "Autons.h"

// Current Autons
/*
void flippingAWPAuton();

void centerRings();
void centerRingsWWallstake();
void ringSideToCorner();

void skills();*/

Auton Skills("Skills", skills);

Auton RedCenterRingsPos("Red Center Rings Pos", []()
                        { asyncDrive.setXFlip(true); centerRings(); });
Auton BlueCenterRingsPos("Blue Center Rings Pos", []()
                         { centerRings(); });

Auton RedCenterRingsNeg("Red(Wall) Center Rings Neg", []()
                        { centerRingsWWallstake(); });
Auton BlueCenterRingsNeg("Blue(Wall) Center Rings Neg", []()
                         { asyncDrive.setXFlip(true); centerRingsWWallstake; });

Auton RedFlippingAWPPos("Red Flipping AWP Pos", []()
                        { flippingAWPAuton(); });
Auton BlueFlippingAWPPos("Blue Flipping AWP Pos", []()
                         { asyncDrive.setXFlip(true); flippingAWPAuton(); });
;

Auton RedRingsToCorner("Red Rings To Corner", []()
                        { centerRings(); });
Auton BlueRingsToCorner("Blue Rings To Corner", []()
                         { asyncDrive.setXFlip(true); centerRings(); });


std::vector<Auton> autons = {
    Skills,
    RedCenterRingsPos,
    BlueCenterRingsPos,
    RedCenterRingsNeg,
    BlueCenterRingsNeg,
    RedFlippingAWPPos,
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