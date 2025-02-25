#include "NewLib/Profiling.h"

double rateLimit(double rate, double target, double current)
{
    if (fabs(target - current) > rate)
    {
        return target + fabs(rate) * ((target - current) / fabs(target - current));
    }
    else
    {
        return target;
    }
}
double rateLimit(double rate, double target, double current, double dt)
{
    if (fabs(target - current) > rate * dt)
    {
        return target + fabs(rate) * dt * ((target - current) / fabs(target - current));
    }
    else
    {
        return target;
    }
}

double motionProfilePos(double maxVel, double maxAccel, double distance, double elapsedTime)
{
    double accelTime = maxVel / maxAccel;

    double accelDist = 0.5 * maxAccel * (accelTime * accelTime);

    if (accelDist > distance * 0.5)
    {
        accelDist = distance * 0.5;
        accelTime = sqrt(accelDist / (0.5 * maxAccel));
    }

    double realMaxVel = maxAccel * accelTime;
    if (realMaxVel > maxVel)
    {
        realMaxVel = maxVel;
    }

    double cruiseDist = distance - accelDist * 2;
    double cruiseTime = cruiseDist / realMaxVel;

    double totalTime = accelTime + cruiseTime + accelTime;

    if (elapsedTime > totalTime)
    {
        return distance;
    }

    if (elapsedTime < accelTime)
    {
        return 0.5 * maxAccel * (elapsedTime * elapsedTime);
    }
    else if (elapsedTime < accelTime + cruiseTime)
    {
        return accelDist + 0.5 * realMaxVel * (elapsedTime - accelTime);
    }
    else
    {
        return accelDist + cruiseDist + realMaxVel * accelTime +
         -0.5 * maxAccel * ((elapsedTime - accelTime - cruiseTime) * (elapsedTime - accelTime - cruiseTime));
    }

    return 0.0;
}

double motionProfileVel(double maxVel, double maxAccel, double distance, double elapsedTime)
{
    double accelTime = maxVel / maxAccel;

    double accelDist = 0.5 * maxAccel * (accelTime * accelTime);

    if (accelDist > distance * 0.5)
    {
        accelDist = distance * 0.5;
        accelTime = sqrt(accelDist / (0.5 * maxAccel));
    }

    double realMaxVel = maxAccel * accelTime;
    if (realMaxVel > maxVel)
    {
        realMaxVel = maxVel;
    }

    double cruiseDist = distance - accelDist * 2;
    double cruiseTime = cruiseDist / realMaxVel;

    double totalTime = accelTime + cruiseTime + accelTime;

    if (elapsedTime > totalTime)
    {
        return 0;
    }

    if (elapsedTime < accelTime)
    {
        return maxAccel * elapsedTime;
    }
    else if (elapsedTime < accelTime + cruiseTime)
    {
        return realMaxVel;
    }
    else
    {
        return realMaxVel +
         -0.5 * maxAccel * (elapsedTime - accelTime - cruiseTime);
    }

    return 0.0;
}

double motionProfileAccel(double maxVel, double maxAccel, double distance, double elapsedTime)
{
    double accelTime = maxVel / maxAccel;

    double accelDist = 0.5 * maxAccel * (accelTime * accelTime);

    if (accelDist > distance * 0.5)
    {
        accelDist = distance * 0.5;
        accelTime = sqrt(accelDist / (0.5 * maxAccel));
    }

    double realMaxVel = maxAccel * accelTime;
    if (realMaxVel > maxVel)
    {
        realMaxVel = maxVel;
    }

    double cruiseDist = distance - accelDist * 2;
    double cruiseTime = cruiseDist / realMaxVel;

    double totalTime = accelTime + cruiseTime + accelTime;

    if (elapsedTime > totalTime)
    {
        return 0;
    }

    if (elapsedTime < accelTime)
    {
        return maxAccel;
    }
    else if (elapsedTime < accelTime + cruiseTime)
    {
        return 0;
    }
    else
    {
        return -maxAccel;
    }

    return 0.0;
}
