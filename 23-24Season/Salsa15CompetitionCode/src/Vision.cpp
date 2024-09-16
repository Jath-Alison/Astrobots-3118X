#include "Vision.h"
#include "RobotConfig.h"
#include "Jath\DataSet.h"
#include "Jath\PIDs\QPID.h"
#include "Jath\Units.h"

vex::vision::signature SIG_1 = vex::vision::signature(1, -5163, -3827, -4495, -5767, -3681, -4724, 4.9, 0);
vex::vision::signature SIG_2 = vex::vision::signature(2, -5093, -3823, -4458, -5699, -3787, -4743, 1.9, 0);
vex::vision::signature SIG_3 = vex::vision::signature(3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_4 = vex::vision::signature(4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature(5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 = vex::vision::signature(6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 = vex::vision::signature(7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Vision1 = vex::vision(vex::PORT5, 150, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);

bool driveTowardBall(bool clear)
{
    Vision1.takeSnapshot(SIG_1);

    static Jath::DataSet<1> centerXData;
    static Jath::DataSet<5> currentData;
    static Jath::PID pid = Jath::QPID()
                               .withConstants(21 / (Jath::Degrees(1)), 0, -1500)
                               .withIntegralZone(Jath::Degrees(10))
                               .withTimeout(2)
                               .withSettleZone(Jath::Degrees(3))
                               .withSettleTimeout(0.25);


    if (clear)
    {
        currentData = Jath::DataSet<5>();
        pid.reset();
        return false;
    }
    static double temp = 0;
    if (Vision1.largestObject.exists)
    {
        centerXData.put((160 - Vision1.largestObject.centerX) / 160.f);
        intake.set(75);
    }else{
        centerXData.put(0);
        intake.set(0);
    }

    smartDrive.arcade(0, 30, pid.calculate(Jath::Degrees(centerXData.getMedian() * 5)));

    if(!Vision1.largestObject.exists && temp != 0){
        smartDrive.arcade(0,0,0);
        intake.set(75);
        vex::wait(0.5,vex::sec);
        intake.set(0);
        return true;
    }

    temp = centerXData.getAverage();

    return false;
}