#include "Pids.h"

art::PID oldDrivePID = art::PID()
    .withConstants(10, 0.06, -2.5)//Somehow already in 1/(1inch) P * 3, D * 4
    .withIntegralZone(art::Revolutions(art::Inches(2) / (M_PI * art::Inches(2.75) * (36.f/48.f))))//still need conversion from inches to revolutions
    .withTimeout(7.5)   
    .withSettleZone(art::Revolutions(art::Inches(1) / (M_PI * art::Inches(2.75) * (36.f/48.f))))
    .withSettleTimeout(0.05);

art::PID oldTurnPID = art::PID()//medium turn
    .withConstants(3.5/(art::Degrees(1)), 0.0, -950)
    .withIntegralZone(art::Degrees(0))
    .withTimeout(2)
    .withSettleZone(art::Degrees(2))
    .withSettleTimeout(0.05);

// art::PID oldTurnPID = art::PID()//medium turn
//     .withConstants(3/(art::Degrees(1)), 3.0, -1000)
//     .withIntegralZone(art::Degrees(10))
//     .withTimeout(2)
//     .withSettleZone(art::Degrees(2))
//     .withSettleTimeout(0.05);

art::PID bigTurnPID = art::PID()
    .withConstants(3.5/(art::Degrees(1)), 0.0, -1000)
    .withIntegralZone(art::Degrees(0))
    .withTimeout(2)
    .withSettleZone(art::Degrees(2))
    .withSettleTimeout(0.05);

art::PID smallTurnPID = art::PID()
    .withConstants(3.5/(art::Degrees(1)), 0.0, -950)
    .withIntegralZone(art::Degrees(0))
    .withTimeout(2)
    .withSettleZone(art::Degrees(2))
    .withSettleTimeout(0.05);