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
    logger.logStringEntry(Auton_Console, "ResetPos");

    smartDrive.m_pos = art::Vec2::XandY(art::Inches(gpsSensorL.xPosition(vex::inches)), art::Inches(gpsSensorL.yPosition(vex::inches)));
    smartDrive.m_dir = art::Degrees(gpsSensorL.heading(vex::degrees));
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
void followPathHalfspeed(Jath::Path p, art::Length lookaheadDist)
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
        smartDrive.m_cmdY = lookahead.m_speed * 0.5;
        smartDrive.update();

        target = lookahead.m_pos;

        lookahead = p.getLookahead(smartDrive.m_pos, lookaheadDist);
        closest = p.getClosestPoint(smartDrive.m_pos);

        vex::wait(20, vex::msec);
    }

    logger.logStringEntry(Auton_Console, "Finished Following Path");
}

void followPath_flipY(Jath::Path p, art::Length lookaheadDist)
{
    Jath::Path temp(p.m_points);

    for (size_t i = 0; i < temp.m_points.size(); i++)
    {
        temp.m_points[i].m_pos.y = temp.m_points[i].m_pos.y * -1.0;
    }

    logger.logStringEntry(Auton_Console, "Following Path");

    std::vector<double> pathLog;
    std::vector<double> pathLogBlue = {
        // 1.8 + art::Length(smartDrive.m_pos.x).meters(),
        // 1.8 + art::Length(smartDrive.m_pos.y).meters(),
        // -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
    };
    for (auto point : temp.m_points)
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

    Jath::Point lookahead = temp.getLookahead(smartDrive.m_centerPos, lookaheadDist);
    Jath::Point closest = temp.getClosestPoint(smartDrive.m_centerPos);

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

        lookahead = temp.getLookahead(smartDrive.m_pos, lookaheadDist);
        closest = temp.getClosestPoint(smartDrive.m_pos);

        vex::wait(20, vex::msec);
    }

    logger.logStringEntry(Auton_Console, "Finished Following Path");
}
void followPathRev_flipY(Jath::Path p, art::Length lookaheadDist)
{

    Jath::Path temp(p.m_points);

    for (size_t i = 0; i < temp.m_points.size(); i++)
    {
        temp.m_points[i].m_pos.y = temp.m_points[i].m_pos.y * -1.0;
    }

    logger.logStringEntry(Auton_Console, "Following Path in Reverse");

    std::vector<double> pathLog;
    std::vector<double> pathLogBlue = {
        // 1.8 + art::Length(smartDrive.m_pos.x).meters(),
        // 1.8 + art::Length(smartDrive.m_pos.y).meters(),
        // -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
    };
    for (auto point : temp.m_points)
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

    Jath::Point lookahead = temp.getLookahead(smartDrive.m_centerPos, lookaheadDist);
    Jath::Point closest = temp.getClosestPoint(smartDrive.m_centerPos);

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

        lookahead = temp.getLookahead(smartDrive.m_pos, lookaheadDist);
        closest = temp.getClosestPoint(smartDrive.m_pos);

        vex::wait(20, vex::msec);
    }
    logger.logStringEntry(Auton_Console, "Finished Following Path in Reverse");
}

void driveTowardPoint(art::Vec2 point)
{

    logger.logStringEntry(Auton_Console, "Driving Toward Point");

    target = point;
    travel = art::Vec2(target - smartDrive.m_pos);

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
    travel = art::Vec2(target - smartDrive.m_pos);

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

void driveToPose(art::Vec2 pos, art::Angle heading, art::Length approachDist)
{
    logger.logStringEntry(Auton_Console, "Driving to Pose");

    std::vector<art::Vec2> controlPoints = {
        smartDrive.m_centerPos,
        smartDrive.m_centerPos 
            + art::Vec2::dirAndMag(smartDrive.m_dir, art::Inches(10)) //10 some starting dist
            + smartDrive.m_vel * (art::Inches(1)/art::Pixels(1)) * 0.05,//some const
        pos - art::Vec2::dirAndMag(heading, approachDist),
        pos,
    };

    Jath::Path p = Jath::bezier(controlPoints, 200.0);
    p.calculateSpeeds(20, 70.0);

    std::vector<double> pathLog;
    std::vector<double> pathLogBlue = {};
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

    Jath::Point lookahead = p.getLookahead(smartDrive.m_centerPos, art::Inches(13));
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

        lookahead = p.getLookahead(smartDrive.m_pos, art::Inches(13));
        closest = p.getClosestPoint(smartDrive.m_pos);

        vex::wait(20, vex::msec);
    }

    logger.logStringEntry(Auton_Console, "Finished Following Path");
}
