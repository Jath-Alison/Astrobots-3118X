#pragma once

#include "robotConfig.h"
#include "Logging.h"
#include "Jath/Path.h"

art::Angle shortestTurnPath(const art::Angle target);

extern art::Vec2 target;
extern art::Vec2 travel;

void resetPositionFromGPS();

void followPath(Jath::Path p, art::Length lookaheadDist);
void followPathRev(Jath::Path p, art::Length lookaheadDist);

void driveTowardPoint(art::Vec2 point);
void driveTowardPointRev(art::Vec2 point);