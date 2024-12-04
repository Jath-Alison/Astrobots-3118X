#include "robotConfig.h"
#include "Logging.h"
#include "Jath/Path.h"

extern Jath::Path testPath;

art::Angle shortestTurnPath(const art::Angle target);

extern art::Vec2 target;
extern art::Vec2 travel;

void resetPositionFromGPS();

void displayLoopFunction();
void logLoopFunction();

void followPath(Jath::Path p, art::Length lookaheadDist);
void followPathRev(Jath::Path p, art::Length lookaheadDist);

void driveTowardPoint(art::Vec2 point);
void driveTowardPointRev(art::Vec2 point);

void blueSoloAWP();
void redSoloAWP();
void blueElims();
void redElims();

void redRushAWP();
void blueRushAWP();

void redAWPGoalFirstNeg();
void blueAWPGoalFirstNeg();

// void redAWPGoalFirstPos();
// void blueAWPGoalFirstPos();

void redAWPStakeFirstPos();
void blueAWPStakeFirstPos();

void winfred_redAWPStakeFirstPos();
void winfred_blueAWPStakeFirstPos();

void JathsSketchyFullFlippingAWP();

void skills();