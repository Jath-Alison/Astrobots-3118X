#include "robotConfig.h"
#include "Jath/Path.h"

extern Jath::Path testPath;

extern art::Vec2 target;
extern art::Vec2 travel;

void displayLoopFunction();
void logLoopFunction();

void followPath(Jath::Path p, art::Length lookaheadDist);