#include "SubAutons.h"

art::Vec2 target;
art::Vec2 travel;

art::Angle shortestTurnPath(const art::Angle target)
{
    art::Angle angle = target;
    angle.constrain();
    if (std::abs(angle.revolutions()) < .5)
    {
        return angle;
    }
    else
    {
        if (angle.revolutions() > 0)
        {
            return art::Revolutions(1 - angle.revolutions());
        }
        else
        {
            return art::Revolutions(1 + angle.revolutions());
        }
    }
    return art::Angle();
}

void resetPositionFromGPS()
{
    smartDrive.m_pos = art::Vec2::XandY(art::Inches(gpsSensor.xPosition(vex::inches)), art::Inches(gpsSensor.yPosition(vex::inches)));
    smartDrive.m_dir = art::Degrees(gpsSensor.heading(vex::degrees));
}

void followPath(Jath::Path p, art::Length lookaheadDist)
{

    logger.logStringEntry(Auton_Console, "Following Path");

    std::vector<double> pathLog;
    std::vector<double> pathLogBlue = {
        // 1.8 + art::Length(smartDrive.m_pos.x).meters(),
        // 1.8 + art::Length(smartDrive.m_pos.y).meters(),
        // -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
    };
    for (auto point : p.m_points)
    {
        pathLog.push_back(art::Length(point.m_pos.x).meters());
        pathLog.push_back(art::Length(point.m_pos.y).meters());
        pathLog.push_back(1.02);

        pathLogBlue.push_back(art::Length(point.m_pos.x).meters() + 1.8);
        pathLogBlue.push_back(art::Length(point.m_pos.y).meters() + 1.8);
        pathLogBlue.push_back(1.02);
    }

    logger.logDoubleArrayEntry(Auton_CurrentPath, pathLog);
    logger.logDoubleArrayEntry(Auton_CurrentPath, pathLogBlue);

    Jath::Point lookahead = p.getLookahead(smartDrive.m_centerPos, lookaheadDist);
    Jath::Point closest = p.getClosestPoint(smartDrive.m_centerPos);

    smartDrive.turnTowardPID(lookahead.m_pos.direction(), true);
    while (lookahead.m_speed != 0)
    {

        if (Controller1.ButtonA.pressing())
        {
            return;
        }

        travel = art::Vec2(lookahead.m_pos - smartDrive.m_centerPos);

        smartDrive.turnTowardPID(travel.direction(), false);
        smartDrive.m_cmdY = lookahead.m_speed;
        smartDrive.update();

        target = lookahead.m_pos;

        lookahead = p.getLookahead(smartDrive.m_pos, lookaheadDist);
        closest = p.getClosestPoint(smartDrive.m_pos);

        vex::wait(20, vex::msec);
    }

    logger.logStringEntry(Auton_Console, "Finished Following Path");
}
void followPathRev(Jath::Path p, art::Length lookaheadDist)
{

    logger.logStringEntry(Auton_Console, "Following Path in Reverse");

    std::vector<double> pathLog;
    std::vector<double> pathLogBlue = {
        // 1.8 + art::Length(smartDrive.m_pos.x).meters(),
        // 1.8 + art::Length(smartDrive.m_pos.y).meters(),
        // -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
    };
    for (auto point : p.m_points)
    {
        pathLog.push_back(art::Length(point.m_pos.x).meters());
        pathLog.push_back(art::Length(point.m_pos.y).meters());
        pathLog.push_back(1.02);

        pathLogBlue.push_back(art::Length(point.m_pos.x).meters() + 1.8);
        pathLogBlue.push_back(art::Length(point.m_pos.y).meters() + 1.8);
        pathLogBlue.push_back(1.02);
    }

    logger.logDoubleArrayEntry(Auton_CurrentPath, pathLog);
    logger.logDoubleArrayEntry(Auton_CurrentPath, pathLogBlue);

    Jath::Point lookahead = p.getLookahead(smartDrive.m_centerPos, lookaheadDist);
    Jath::Point closest = p.getClosestPoint(smartDrive.m_centerPos);

    smartDrive.turnTowardPID(lookahead.m_pos.direction() + art::Degrees(180), true);
    while (lookahead.m_speed != 0)
    {

        if (Controller1.ButtonA.pressing())
        {
            return;
        }

        travel = art::Vec2(lookahead.m_pos - smartDrive.m_centerPos);

        smartDrive.turnTowardPID(travel.direction() + art::Degrees(180), false);
        smartDrive.m_cmdY = -lookahead.m_speed;
        smartDrive.update();

        target = lookahead.m_pos;

        lookahead = p.getLookahead(smartDrive.m_pos, lookaheadDist);
        closest = p.getClosestPoint(smartDrive.m_pos);

        vex::wait(20, vex::msec);
    }
    logger.logStringEntry(Auton_Console, "Finished Following Path in Reverse");
}

void driveTowardPoint(art::Vec2 point)
{

    logger.logStringEntry(Auton_Console, "Driving Toward Point");

    target = point;
    travel = art::Vec2(target - smartDrive.m_centerPos);

    bool driveActive = false;

    smartDrive.turnToPID(travel.direction());

    smartDrive.driveForPID(travel.magnitude());

    // smartDrive.turnTowardPID(0, true);
    // smartDrive.driveTowardPID(0, true);
    // while (art::Length(travel.magnitude()) > art::Inches(3))
    // {

    //     if (Controller1.ButtonA.pressing())
    //     {
    //         return;
    //     }

    //     travel = art::Vec2(target - smartDrive.m_centerPos);

    //     smartDrive.turnTowardPID(travel.direction(), false);
    //     smartDrive.driveTowardPID(travel.magnitude(), false);

    //     if (smartDrive.m_cmdY > 100)
    //     {
    //         smartDrive.m_cmdY = 100;
    //     }

    //     smartDrive.update();

    //     vex::wait(20, vex::msec);
    // }

    smartDrive.arcade(0, 0);

    // smartDrive.m_left.stop(vex::brake);
    // smartDrive.m_right.stop(vex::brake);

    logger.logStringEntry(Auton_Console, "Finished Driving Toward Point");
}

void driveTowardPointRev(art::Vec2 point)
{
    logger.logStringEntry(Auton_Console, "Driving Toward Point-Rev");

    target = point;
    travel = art::Vec2(target - smartDrive.m_centerPos);

    bool driveActive = false;

    smartDrive.turnToPID(travel.direction() + art::Degrees(180));
    smartDrive.driveForPID(-travel.magnitude());

    // smartDrive.turnTowardPID(0, true);
    // smartDrive.driveTowardPID(0, true);
    // while (art::Length(travel.magnitude()) > art::Inches(3))
    // {

    //     if (Controller1.ButtonA.pressing())
    //     {
    //         return;
    //     }

    //     travel = art::Vec2(target - smartDrive.m_centerPos);

    //     smartDrive.turnTowardPID(travel.direction() + art::Degrees(180), false);
    //     smartDrive.driveTowardPID(-travel.magnitude(), false);

    //     if (smartDrive.m_cmdY < -100)
    //     {
    //         smartDrive.m_cmdY = -100;
    //     }

    //     smartDrive.update();

    //     vex::wait(20, vex::msec);
    // }

    smartDrive.arcade(0, 0);

    // smartDrive.m_left.stop(vex::brake);
    // smartDrive.m_right.stop(vex::brake);

    logger.logStringEntry(Auton_Console, "Finished Driving Toward Point-Rev");
}