#include "Pids.h"

art::PID oldDrivePID = art::PID()
    .withConstants(10, 0.06, -5.0)//Somehow already in 1/(1inch) P * 3, D * 4
    .withIntegralZone(art::Revolutions(art::Inches(2) / (M_PI * art::Inches(2.75) * (36.f/48.f))))//still need conversion from inches to revolutions
    .withTimeout(7.5)   
    .withSettleZone(art::Revolutions(art::Inches(1) / (M_PI * art::Inches(2.75) * (36.f/48.f))))
    .withSettleTimeout(0.15);

art::PID oldTurnPID = art::PID()
    .withConstants(3/(art::Degrees(1)), 3.0, -750)
    .withIntegralZone(art::Degrees(10))
    .withTimeout(2)
    .withSettleZone(art::Degrees(3))
    .withSettleTimeout(0.15);

art::PID bigTurnPID = art::PID()
    .withConstants(3/(art::Degrees(1)), 3.0, -900)
    .withIntegralZone(art::Degrees(10))
    .withTimeout(2)
    .withSettleZone(art::Degrees(3))
    .withSettleTimeout(0.15);

art::PID smallTurnPID = art::PID()
    .withConstants(3/(art::Degrees(1)), 3.0, -750)
    .withIntegralZone(art::Degrees(10))
    .withTimeout(2)
    .withSettleZone(art::Degrees(3))
    .withSettleTimeout(0.15);