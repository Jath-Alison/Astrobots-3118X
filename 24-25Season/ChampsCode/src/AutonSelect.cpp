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
                        { centerRings(); });
Auton BlueCenterRingsPos("Blue Center Rings Pos", []()
                         { centerRings(); });

Auton RedCenterRingsNeg("Red Center Rings Neg", []()
                        { centerRings(); });
Auton BlueCenterRingsNeg("Blue Center Rings Neg", []()
                         { centerRings(); });

Auton RedFlippingAWPPos("Red Flipping AWP Pos", []()
                        { flippingAWPAuton(); });
Auton BlueFlippingAWPPos("Blue Flipping AWP Pos", []()
                         { flippingAWPAuton(); });
;

Auton RedFlippingAWPNeg("Red Flipping AWP Neg", []()
                        { flippingAWPAuton(); });
Auton BlueFlippingAWPNeg("Blue Flipping AWP Neg", []()
                         { flippingAWPAuton(); });
;

std::vector<Auton> autons = {
    Skills,
    RedCenterRingsPos,
    BlueCenterRingsPos,
    RedCenterRingsNeg,
    BlueCenterRingsNeg,
    RedFlippingAWPPos,
    BlueFlippingAWPPos,
    RedFlippingAWPNeg,
    BlueFlippingAWPNeg};

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