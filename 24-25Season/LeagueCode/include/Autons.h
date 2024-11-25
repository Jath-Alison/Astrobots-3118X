#include "robotConfig.h"
#include "Jath/Path.h"

extern Jath::Path testPath;

art::Angle shortestTurnPath(const art::Angle target);

extern art::Vec2 target;
extern art::Vec2 travel;

void displayLoopFunction();
void logLoopFunction();

void followPath(Jath::Path p, art::Length lookaheadDist);

void blueSoloAWP();
void redSoloAWP();
void blueElims();
void redElims();

void redRushAWP();
void blueRushAWP();

void redAWPGoalFirst();
void blueAWPGoalFirst();

void redAWPStakeFirst();
void blueAWPStakeFirst();