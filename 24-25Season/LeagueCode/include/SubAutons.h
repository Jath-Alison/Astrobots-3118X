#pragma once

#include "robotConfig.h"
#include "Logging.h"
#include "Jath/Path.h"

art::Angle shortestTurnPath(const art::Angle target);

extern art::Vec2 target;
extern art::Vec2 travel;

void resetPositionFromGPSL();
void resetPositionFromGPSR();

void localizeAvg();
void localizeAvgSafe();

void followPath(Jath::Path p, art::Length lookaheadDist);
void followPathRev(Jath::Path p, art::Length lookaheadDist);
void followPathHalfspeed(Jath::Path p, art::Length lookaheadDist);

void followPath_flipY(Jath::Path p, art::Length lookaheadDist);
void followPathRev_flipY(Jath::Path p, art::Length lookaheadDist);

void driveTowardPoint(art::Vec2 point);
void driveTowardPointRev(art::Vec2 point);

void driveToPose(art::Vec2 pos, art::Angle heading, art::Length approachDist);

int intakeRejectBlue();
int intakeRejectRed();

int intakePauseBlue();
int intakePauseRed();