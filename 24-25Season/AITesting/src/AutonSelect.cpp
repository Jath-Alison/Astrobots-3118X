#include "AutonSelect.h"


// Current Autons
/*
void flippingAWPAuton();

void centerRings();
void centerRingsWWallstake();
void ringSideToCorner();

void skills();*/


Auton DoNothing("DoNothing", []()
                        { /*:)*/ });

std::vector<Auton> autons = {
    DoNothing
};

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