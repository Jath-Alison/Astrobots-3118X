#include "Autons.h"

std::vector<Jath::Point> testPathPoints = {Jath::Point(-0.934, -1.781, 66), Jath::Point(-0.921, 0.219, 64.572), Jath::Point(-0.898, 2.218, 63.143), Jath::Point(-0.857, 4.218, 61.715), Jath::Point(-0.793, 6.217, 60.286), Jath::Point(-0.715, 8.215, 58.858), Jath::Point(-0.615, 10.213, 57.43), Jath::Point(-0.489, 12.209, 56.001), Jath::Point(-0.342, 14.203, 54.573), Jath::Point(-0.174, 16.196, 53.144), Jath::Point(0.026, 18.186, 51.716), Jath::Point(0.256, 20.173, 50.288), Jath::Point(0.515, 22.156, 48.859), Jath::Point(0.806, 24.135, 47.431), Jath::Point(1.132, 26.108, 46.002), Jath::Point(1.497, 28.074, 44.574), Jath::Point(1.904, 30.032, 43.146), Jath::Point(2.357, 31.98, 41.717), Jath::Point(2.86, 33.916, 40.289), Jath::Point(3.418, 35.837, 38.86), Jath::Point(4.036, 37.739, 37.432), Jath::Point(4.717, 39.619, 36.004), Jath::Point(5.467, 41.473, 34.575), Jath::Point(6.289, 43.296, 33.147), Jath::Point(7.192, 45.08, 31.718), Jath::Point(8.189, 46.813, 30.29), Jath::Point(9.272, 48.494, 28.862), Jath::Point(10.459, 50.103, 27.433), Jath::Point(11.739, 51.639, 26.005), Jath::Point(13.13, 53.076, 24.576), Jath::Point(14.615, 54.415, 23.148), Jath::Point(16.192, 55.644, 21.72), Jath::Point(17.856, 56.753, 24.269), Jath::Point(19.595, 57.739, 26.818), Jath::Point(21.396, 58.609, 29.367), Jath::Point(23.246, 59.366, 31.917), Jath::Point(25.136, 60.021, 34.466), Jath::Point(27.054, 60.585, 37.015), Jath::Point(28.994, 61.073, 39.564), Jath::Point(30.948, 61.499, 42.114), Jath::Point(32.911, 61.879, 44.663), Jath::Point(34.88, 62.229, 47.212), Jath::Point(36.852, 62.567, 43.813), Jath::Point(38.822, 62.91, 40.414), Jath::Point(40.788, 63.277, 37.015), Jath::Point(42.745, 63.69, 33.616), Jath::Point(44.686, 64.171, 30.217), Jath::Point(46.602, 64.744, 26.818), Jath::Point(48.478, 65.435, 23.419), Jath::Point(50.296, 66.266, 20.02), Jath::Point(52.032, 67.259, 16.621), Jath::Point(53.654, 68.427, 13.222), Jath::Point(55.135, 69.769, 15.701), Jath::Point(56.458, 71.267, 18.179), Jath::Point(57.613, 72.898, 20.657), Jath::Point(58.605, 74.634, 23.136), Jath::Point(59.437, 76.452, 25.614), Jath::Point(60.129, 78.328, 28.093), Jath::Point(60.704, 80.243, 30.571), Jath::Point(61.162, 82.189, 33.05), Jath::Point(61.53, 84.155, 35.528), Jath::Point(61.821, 86.134, 38.006), Jath::Point(62.034, 88.122, 40.485), Jath::Point(62.185, 90.116, 42.963), Jath::Point(62.282, 92.114, 42.963), Jath::Point(62.33, 94.113, 42.963), Jath::Point(62.335, 96.113, 42.963), Jath::Point(62.301, 98.113, 42.963), Jath::Point(62.233, 100.111, 42.963), Jath::Point(62.134, 102.109, 42.963), Jath::Point(62.003, 104.105, 42.963), Jath::Point(61.844, 106.098, 42.963), Jath::Point(61.522, 109.553, 42.963), Jath::Point(61.522, 109.553, 0)};
Jath::Path testPath = Jath::Path::cm(testPathPoints);

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

void displayLoopFunction()
{
    logger.logStringEntry(100, timePassed(), "Display Loop Task Started");

    Brain.Screen.setPenWidth(3);

    while (1)
    {
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("X: %f", art::Length(smartDrive.m_pos.x).inches());
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Y: %f", art::Length(smartDrive.m_pos.y).inches());
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Rot: %f", art::Angle(smartDrive.m_dir).degrees());
        Brain.Screen.setCursor(4, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Arm_Angle: %f", arm.position(vex::degrees)/3.0);
        Brain.Screen.setCursor(5, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Arm Target: %f ", armTarget.degrees());

        Brain.Screen.setFillColor(vex::color::blue);
        Brain.Screen.drawRectangle(480 - 5 - 80, 5, 80, 120 - 10);
        Brain.Screen.setFillColor(vex::color::red);
        Brain.Screen.drawRectangle(480 - 5 - 80, 125, 80, 120 - 10);
        Brain.Screen.setFillColor(vex::color::black);

        Brain.Screen.setCursor(8, 1);
        Brain.Screen.clearLine();
        if (isBlue)
        {
            Brain.Screen.print("Blue Auton Selected");
        }
        else
        {
            Brain.Screen.print("Red Auton Selected");
        }

        if (Brain.Screen.PRESSED)
        {
            if (Brain.Screen.xPosition() > 480 - 5 - 80 && Brain.Screen.xPosition() < 480 - 5 - 80 + 120 - 10 && Brain.Screen.yPosition() > 5 && Brain.Screen.yPosition() < 5 + 120 - 10)
            {
                isBlue = true;
            }
            if (Brain.Screen.xPosition() > 480 - 5 - 80 && Brain.Screen.xPosition() < 480 - 5 - 80 + 120 - 10 && Brain.Screen.yPosition() > 120 + 5 && Brain.Screen.yPosition() < 5 + 120 - 10 + 120)
            {
                isBlue = false;
            }
            // isBlue = !isBlue;
        }

        vex::this_thread::sleep_for(20);
    }
}

auto last_logged = std::chrono::high_resolution_clock::now();
auto current_time_logLoop = std::chrono::high_resolution_clock::now();

uint64_t logTimePassed()
{
    current_time_logLoop = std::chrono::high_resolution_clock::now();
    return uint64_t(std::chrono::duration_cast<std::chrono::microseconds>(current_time_logLoop - last_logged).count());
}

void logLoopFunction()
{

    logger.logStringEntry(100, timePassed(), "Log Loop Task Started");

    logger.clearFile("TestLog.wpilog");

    /**
     * Controller stuff:
     * - 4 Axis - int 64
     * - 12 Buttons - bool
     *
     * Motor stats:
     * - Motor Command
     * - Motor Speed
     * - Motor Current
     * - Motor Temperature
     *
     * Robot stats:
     * - Pose
     *  - X,Y, Rot
     *
     * Later:
     * - PID Stats
     * - Sensor inputs
     * - Other robot states
     *
     */

    logger.startFloatArrayEntry("DS/joystick0/axes", 1);
    logger.startBooleanArrayEntry("DS/joystick0/buttons", 2);
    logger.startFloatArrayEntry("DS/joystick0/povs", 29);


    logger.startFloatArrayEntry("Motors/Command", 3);
    logger.startFloatArrayEntry("Motors/Speed", 4);
    logger.startFloatArrayEntry("Motors/Current", 5);
    logger.startFloatArrayEntry("Motors/Temperature", 6);

    logger.startDoubleArrayEntry("Robot/Pose", 7);
    logger.startDoubleArrayEntry("Robot/Pose(Blue)", 8);

    logger.startDoubleArrayEntry("Autons/TargetPos", 9);
    logger.startDoubleArrayEntry("Autons/TargetPos(Blue)", 10);

    logger.startInt64Entry("Logger/Size", 11);
    logger.startInt64Entry("Logger/Capacity", 12);
    logger.startFloatEntry("Logger/TimeSinceLastLog", 13);

    logger.startFloatEntry("Base/cmd_Drive", 14);
    logger.startFloatEntry("Base/cmd_Rot", 15);

    logger.startFloatEntry("Intake/cmd", 16);

    // logger.startDoubleEntry("Arm/targetPos", 17);
    // logger.startDoubleEntry("Arm/rotAngle", 18);
    // logger.startDoubleEntry("Arm/Output", 19);

    // logger.startDoubleEntry("Arm/PID/P", 20);
    // logger.startDoubleEntry("Arm/PID/I", 21);
    // logger.startDoubleEntry("Arm/PID/D", 22);

    logger.startDoubleEntry("Arm/PID/Target{deg}", 17);
    logger.startDoubleEntry("Arm/PID/Current{deg}", 18);
    logger.startDoubleEntry("Arm/PID/CurrentMotor{deg}", 24);
    logger.startDoubleEntry("Arm/PID/Error", 19);
    logger.startDoubleEntry("Arm/PID/P", 20);
    logger.startDoubleEntry("Arm/PID/I", 21);
    logger.startDoubleEntry("Arm/PID/D", 22);
    logger.startDoubleEntry("Arm/PID/Out", 23);

    logger.startDoubleArrayEntry("Robot/CenterPose", 24);
    logger.startDoubleArrayEntry("Robot/CenterPose(Blue)", 25);
    
    logger.startDoubleArrayEntry("Robot/GPS/GpsPose", 26);
    logger.startDoubleArrayEntry("Robot/GPS/GpsPose(Blue)", 27);
    logger.startInt64Entry("Robot/GPS/GpsQuality", 28);



    std::vector<vex::motor *> allMotors = {
        &leftMotorA, &leftMotorB, &leftMotorC,
        &rightMotorA, &rightMotorB, &rightMotorC,
        &intake};

    while (1)
    {
        std::vector<float> axesStates = {
            float(Controller1.Axis1.position()),
            float(Controller1.Axis2.position()),
            float(Controller1.Axis3.position()),
            float(Controller1.Axis4.position())};
        std::vector<bool> buttonStates = {
            Controller1.ButtonUp.pressing(),
            Controller1.ButtonRight.pressing(),
            Controller1.ButtonDown.pressing(),
            Controller1.ButtonLeft.pressing(),
            Controller1.ButtonX.pressing(),
            Controller1.ButtonA.pressing(),
            Controller1.ButtonB.pressing(),
            Controller1.ButtonY.pressing(),
            Controller1.ButtonL1.pressing(),
            Controller1.ButtonL2.pressing(),
            Controller1.ButtonR1.pressing(),
            Controller1.ButtonR2.pressing(),
        };

        std::vector<float> motorCommands = {};
        std::vector<float> motorSpeeds = {};
        std::vector<float> motorCurrents = {};
        std::vector<float> motorTemperatures = {};

        for (size_t i = 0; i < allMotors.size(); i++)
        {
            motorCommands.push_back(allMotors[i]->voltage(vex::volt));
            motorSpeeds.push_back(allMotors[i]->velocity(vex::percent));
            motorCurrents.push_back(allMotors[i]->current(vex::amp));
            motorTemperatures.push_back(allMotors[i]->temperature(vex::celsius));
        }

        std::vector<double> robotPose = {
            art::Length(smartDrive.m_pos.x).meters(),
            art::Length(smartDrive.m_pos.y).meters(),
            art::Angle(smartDrive.m_dir).degrees()};

        std::vector<double> robotPoseBlue = {
            1.8 + art::Length(smartDrive.m_pos.x).meters(),
            1.8 + art::Length(smartDrive.m_pos.y).meters(),
            -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
        };

        std::vector<double> targetPose = {
            art::Length(target.x).meters(),
            art::Length(target.y).meters(),
            art::Angle(smartDrive.m_dir).degrees() // converted to FRC scheme
        };

        std::vector<double> targetPoseBlue = {
            1.8 + art::Length(target.x).meters(),
            1.8 + art::Length(target.y).meters(),
            -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
        };

        std::vector<double> robotCenterPose = {
            art::Length(smartDrive.m_centerPos.x).meters(),
            art::Length(smartDrive.m_centerPos.y).meters(),
            art::Angle(smartDrive.m_dir).degrees()};

        std::vector<double> robotCenterPoseBlue = {
            1.8 + art::Length(smartDrive.m_centerPos.x).meters(),
            1.8 + art::Length(smartDrive.m_centerPos.y).meters(),
            -(smartDrive.m_dir - art::Degrees(90)) // converted to FRC scheme
        };

        std::vector<double> robotGpsPose = {
            art::Inches(gpsSensor.xPosition(vex::inches)).meters(),
            art::Inches(gpsSensor.yPosition(vex::inches)).meters(),
            art::Degrees(gpsSensor.heading(vex::degrees)).degrees()};

        std::vector<double> robotGpsPoseBlue = {
            1.8 + art::Inches(gpsSensor.xPosition(vex::inches)).meters(),
            1.8 + art::Inches(gpsSensor.yPosition(vex::inches)).meters(),
            -(gpsSensor.heading(vex::degrees) - 90) // converted to FRC scheme
        };

        std::vector<float> povs = {
            -1
        };

        logger.logFloatArrayEntry(1, timePassed(), axesStates);
        logger.logBooleanArrayEntry(2, timePassed(), buttonStates);
        logger.logFloatArrayEntry(29, timePassed(), povs);


        logger.logFloatArrayEntry(3, timePassed(), motorCommands);
        logger.logFloatArrayEntry(4, timePassed(), motorSpeeds);
        logger.logFloatArrayEntry(5, timePassed(), motorCurrents);
        logger.logFloatArrayEntry(6, timePassed(), motorTemperatures);

        logger.logDoubleArrayEntry(7, timePassed(), robotPose);
        logger.logDoubleArrayEntry(8, timePassed(), robotPoseBlue);

        logger.logDoubleArrayEntry(9, timePassed(), targetPose);
        logger.logDoubleArrayEntry(10, timePassed(), targetPoseBlue);

        logger.logInt64Entry(11, timePassed(), logger.getDataSize());
        logger.logInt64Entry(12, timePassed(), logger.getCapacity());
        logger.logFloatEntry(13, timePassed(), logTimePassed());

        logger.logFloatEntry(14, timePassed(), smartDrive.m_cmdY);
        logger.logFloatEntry(15, timePassed(), smartDrive.m_cmdRot);

        logger.logFloatEntry(16, timePassed(), intake.get());

        logger.logDoubleEntry(17, timePassed(), armTarget.degrees());//"ARM/PID/Target"
        logger.logDoubleEntry(18, timePassed(), armRot.angle());//"ARM/PID/Current"
        logger.logDoubleEntry(24, timePassed(), arm.position(vex::degrees));//"ARM/PID/CurrentMotor"
        logger.logDoubleEntry(19, timePassed(), shortestTurnPath(armTarget - art::Degrees(armRot.angle())));//"ARM/PID/Error"
        logger.logDoubleEntry(20, timePassed(), armPID.getProportional());//"ARM/PID/P"
        logger.logDoubleEntry(21, timePassed(), armPID.getIntegral());//"ARM/PID/I"
        logger.logDoubleEntry(22, timePassed(), armPID.getDerivative());//"ARM/PID/D"
        logger.logDoubleEntry(23, timePassed(), armOut);//"ARM/PID/Out"

        logger.logDoubleArrayEntry(24, timePassed(), robotCenterPose);
        logger.logDoubleArrayEntry(25, timePassed(), robotCenterPoseBlue);
        logger.logDoubleArrayEntry(26, timePassed(), robotGpsPose);
        logger.logDoubleArrayEntry(27, timePassed(), robotGpsPoseBlue);

        logger.logInt64Entry(28, timePassed(), gpsSensor.quality());

        if (Competition.AUTONOMOUS)
        {
            logger.logStringEntry(100, timePassed(), "Auton Started");
        }
        if (Competition.DRIVER_CONTROL)
        {
            logger.logStringEntry(100, timePassed(), "Driver Control Started");
        }
        if (Competition.DISABLED)
        {
            logger.logStringEntry(100, timePassed(), "Robot Disabled");
        }

        if (logger.getDataSize() > 10000)
        {
            last_logged = std::chrono::high_resolution_clock::now();
            logger.writeToFile("TestLog.wpilog");
        }

        vex::this_thread::sleep_for(20);
    }
}

void followPath(Jath::Path p, art::Length lookaheadDist)
{

    static bool followPathInit = false;

    if (!followPathInit)
    {
        followPathInit = true;

        logger.startFloatArrayEntry("Paths/currentPath", 69);
        logger.startFloatArrayEntry("Paths/currentPath(Blue)", 70);

        // logger.startDoubleArrayEntry("Paths/drive", 400);
        // logger.startDoubleArrayEntry("Paths/currentPath(Blue)", 401);
    }

    logger.logStringEntry(100, timePassed(), "followingPath");

    std::vector<float> pathLog;
    std::vector<float> pathLogBlue = {
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

    logger.logFloatArrayEntry(69, timePassed(), pathLog);
    logger.logFloatArrayEntry(70, timePassed(), pathLogBlue);

    logger.logStringEntry(100, timePassed(), "logged Path");

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
}

art::Vec2 target;
art::Vec2 travel;

void blueSoloAWP()
{
	logger.logStringEntry(100, timePassed(), "BlueSoloAWP Started");

	// Grab Goal1
	smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25), art::Tiles(-1.0));
	smartDrive.m_dir = art::Degrees(90);

	target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-1));
	travel = art::Vec2(target - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	smartDrive.driveFor(travel.magnitude() * -.78, -50);
	clamp.set(true);
	logger.logStringEntry(100, timePassed(), "Goal Grabbed");
	smartDrive.arcade(0, 0);

	// score preload
	intake.set(100);
	vex::wait(0.75, vex::sec);

	// Grab and score ring2
	target = art::Vec2::XandY(art::Tiles(1), art::Tiles(-2));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveFor(travel.magnitude() * .75, 35);
	smartDrive.arcade(0, 0);

	vex::wait(0.25, vex::sec);
	clamp.set(false);
	intake.set(-30);
	smartDrive.arcade(-20, 0);
	vex::wait(0.5, vex::sec);
	clamp.set(true);
	intake.set(100);
	smartDrive.arcade(0, 0);
	vex::wait(0.25, vex::sec);

	// drop goal & drive to centerline
	target = art::Vec2::XandY(art::Tiles(2), art::Tiles(0));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveForPID(travel.magnitude() * 0.85);
	clamp.set(false);
	logger.logStringEntry(100, timePassed(), "Goal Grabbed");
	smartDrive.arcade(0, 0);

	// Grab Goal2
	target = art::Vec2::XandY(art::Tiles(1), art::Tiles(1));
	travel = art::Vec2(target - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	// smartDrive.driveFor(travel.magnitude() * -.80, -50);//disabled to hard code instead

	smartDrive.turnToPID(art::Degrees(-40) + art::Degrees(180));
	smartDrive.driveFor(art::Inches(-35), -50);
	smartDrive.arcade(0, 0);

	clamp.set(true);

	// // Grab ring2 and score

	smartDrive.turnToPID(art::Degrees(0));
	intake.set(100);
	smartDrive.driveFor(art::Inches(12), 75);
	smartDrive.turnToPID(art::Degrees(-15));
	smartDrive.arcade(0, 0);
	vex::wait(0.35, vex::sec);
	smartDrive.driveFor(art::Inches(-30), -100);
	smartDrive.arcade(0, 0);

	vex::wait(4, vex::sec);

	intake.set(0);
	smartDrive.arcade(0, 0);
}
void redSoloAWP()
{
	logger.logStringEntry(100, timePassed(), "RedSoloAWP Started");
	double xFlip = -1.0;

	// Grab Goal1
	smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25) * -1, art::Tiles(-1.0));
	smartDrive.m_dir = art::Degrees(90 * -1);

	target = art::Vec2::XandY(art::Tiles(1) * -1, art::Tiles(-1));
	travel = art::Vec2(target - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	smartDrive.driveFor(travel.magnitude() * -.78, -50);
	clamp.set(true);
	logger.logStringEntry(100, timePassed(), "Goal Grabbed");
	smartDrive.arcade(0, 0);

	// score preload
	intake.set(100);
	vex::wait(0.75, vex::sec);

	// Grab and score ring2
	target = art::Vec2::XandY(art::Tiles(1) * -1, art::Tiles(-2));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveFor(travel.magnitude() * .5, 35);
	smartDrive.arcade(0, 0);

	vex::wait(0.25, vex::sec);
	clamp.set(false);
	intake.set(-30);
	smartDrive.arcade(-20, 0);
	vex::wait(0.5, vex::sec);
	clamp.set(true);
	intake.set(100);
	smartDrive.arcade(0, 0);
	vex::wait(0.25, vex::sec);

	// drop goal & drive to centerline
	target = art::Vec2::XandY(art::Tiles(2) * -1, art::Tiles(0));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.driveForPID(travel.magnitude() * 0.85);
	clamp.set(false);
	smartDrive.arcade(0, 0);

	// Grab Goal2
	target = art::Vec2::XandY(art::Tiles(1) * -1, art::Tiles(1));
	travel = art::Vec2(target - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	// smartDrive.driveFor(travel.magnitude() * -.80, -50);//disabled to hard code instead

	smartDrive.turnToPID(art::Degrees(-40 * -1) + art::Degrees(180));
	intake.set(-100);
	smartDrive.driveFor(art::Inches(-35), -50);
	smartDrive.arcade(0, 0);

	clamp.set(true);
	logger.logStringEntry(100, timePassed(), "Goal Grabbed");

	// // Grab ring2 and score

	smartDrive.turnToPID(art::Degrees(0));
	intake.set(100);
	smartDrive.driveFor(art::Inches(12), 75);
	smartDrive.turnToPID(art::Degrees(-15));
	smartDrive.arcade(0, 0);
	vex::wait(0.45, vex::sec);
	smartDrive.driveFor(art::Inches(-30), -100);
	smartDrive.arcade(0, 0);

	vex::wait(4, vex::sec);

	intake.set(0);
	smartDrive.arcade(0, 0);
}

void blueElims()
{
	logger.logStringEntry(100, timePassed(), "BlueElims Started");

	int xFlip = 1.0;

	smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25 * xFlip), art::Tiles(-1.0));
	smartDrive.m_dir = art::Degrees(90 * xFlip);

	target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-1));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.driveFor(travel.magnitude() * -.78, -50);
	clamp.set(true);
	logger.logStringEntry(100, timePassed(), "Goal Grabbed");

	intake.set(100);
	smartDrive.arcade(0, 0);
	vex::wait(0.5, vex::sec);
	smartDrive.arcade(30, 0);
	vex::wait(0.45, vex::sec);

	// smartDrive.turnToPID(art::Degrees(125));
	// smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
	// clamp.set(false);
	// logger.logStringEntry(100, timePassed(), "Goal Dropped");

	// vex::wait(0.25, vex::sec);

	// target = art::Vec2::XandY(art::Tiles(0 * xFlip), art::Tiles(-2));
	// travel = art::Vec2(target - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	// smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
	// smartDrive.driveFor(travel.magnitude() * -.75 , -35);
	// clamp.set(true);
	// logger.logStringEntry(100, timePassed(), "Goal Grabbed");
	// smartDrive.arcade(0, 0);

	// vex::wait(0.25, vex::sec);

	target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-2));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.arcade(0, 0);
	vex::wait(0.25, vex::sec);

	intake.set(100);
	smartDrive.driveFor(travel.magnitude() * .7, 45);
	smartDrive.arcade(0, 0);

	intake.set(100);
	smartDrive.arcade(0, 50);

	vex::wait(0.5, vex::sec);

	smartDrive.arcade(0, 0);
	intake.set(100);

	vex::wait(1, vex::sec);
	intake.set(0);

	smartDrive.turnToPID(art::Degrees(-90) * xFlip);
	clamp.set(false);
	smartDrive.turnToPID(art::Degrees(90) * xFlip);

	smartDrive.driveFor(art::Inches(-2), -30);
}
void redElims()
{
	logger.logStringEntry(100, timePassed(), "RedElims Started");

	int xFlip = -1.0;

	smartDrive.m_pos = art::Vec2::XandY(art::Tiles(2.25 * xFlip), art::Tiles(-1.0));
	smartDrive.m_dir = art::Degrees(90 * xFlip);

	target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-1));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.driveFor(travel.magnitude() * -.78, -50);
	clamp.set(true);
	logger.logStringEntry(100, timePassed(), "Goal Grabbed");

	intake.set(100);
	smartDrive.arcade(0, 0);
	vex::wait(0.5, vex::sec);
	smartDrive.arcade(30, 0);
	vex::wait(0.45, vex::sec);

	// smartDrive.turnToPID(art::Degrees(125));
	// smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
	// clamp.set(false);
	// logger.logStringEntry(100, timePassed(), "Goal Dropped");

	// vex::wait(0.25, vex::sec);

	// target = art::Vec2::XandY(art::Tiles(0 * xFlip), art::Tiles(-2));
	// travel = art::Vec2(target - smartDrive.m_pos);

	// smartDrive.turnToPID(travel.direction() + art::Degrees(180));
	// smartDrive.arcade(0,0); vex::wait(0.25,vex::sec);
	// smartDrive.driveFor(travel.magnitude() * -.75 , -35);
	// clamp.set(true);
	// logger.logStringEntry(100, timePassed(), "Goal Grabbed");
	// smartDrive.arcade(0, 0);

	// vex::wait(0.25, vex::sec);

	target = art::Vec2::XandY(art::Tiles(1 * xFlip), art::Tiles(-2));
	travel = art::Vec2(target - smartDrive.m_pos);

	smartDrive.turnToPID(travel.direction());
	smartDrive.arcade(0, 0);
	vex::wait(0.25, vex::sec);

	intake.set(100);
	smartDrive.driveFor(travel.magnitude() * .7, 45);
	smartDrive.arcade(0, 0);

	intake.set(100);
	smartDrive.arcade(0, 50);

	vex::wait(0.5, vex::sec);

	smartDrive.arcade(0, 0);
	intake.set(100);

	vex::wait(1, vex::sec);
	intake.set(0);

	smartDrive.turnToPID(art::Degrees(-90) * xFlip);
	clamp.set(false);
	smartDrive.turnToPID(art::Degrees(90) * xFlip);

	smartDrive.driveFor(art::Inches(-2), -30);
}

std::vector<Jath::Point> redRushPath1Points = {Jath::Point(-141.052,-146.788,101), Jath::Point(-139.053,-146.77,101), Jath::Point(-137.053,-146.752,100.129), Jath::Point(-135.053,-146.733,99.883), Jath::Point(-133.053,-146.712,98.765), Jath::Point(-131.053,-146.689,97.648), Jath::Point(-129.053,-146.665,96.53), Jath::Point(-127.053,-146.639,95.413), Jath::Point(-125.053,-146.611,94.296), Jath::Point(-123.054,-146.581,93.178), Jath::Point(-121.054,-146.547,92.061), Jath::Point(-119.054,-146.511,90.943), Jath::Point(-117.055,-146.472,89.826), Jath::Point(-115.055,-146.43,88.709), Jath::Point(-113.056,-146.383,87.591), Jath::Point(-111.056,-146.333,86.474), Jath::Point(-109.057,-146.277,85.356), Jath::Point(-107.058,-146.217,84.239), Jath::Point(-105.059,-146.151,83.122), Jath::Point(-103.06,-146.078,82.004), Jath::Point(-101.062,-145.999,80.887), Jath::Point(-99.064,-145.912,79.77), Jath::Point(-97.066,-145.817,78.652), Jath::Point(-95.069,-145.713,77.535), Jath::Point(-93.072,-145.599,76.417), Jath::Point(-91.076,-145.474,75.3), Jath::Point(-89.081,-145.337,74.183), Jath::Point(-87.086,-145.188,73.065), Jath::Point(-85.093,-145.024,71.948), Jath::Point(-83.101,-144.846,70.83), Jath::Point(-81.11,-144.652,69.713), Jath::Point(-79.122,-144.441,68.596), Jath::Point(-77.135,-144.212,70.306), Jath::Point(-75.15,-143.965,72.015), Jath::Point(-73.168,-143.697,73.725), Jath::Point(-71.189,-143.41,75.435), Jath::Point(-69.213,-143.101,77.145), Jath::Point(-67.24,-142.772,78.855), Jath::Point(-65.271,-142.421,80.565), Jath::Point(-63.306,-142.049,82.275), Jath::Point(-61.345,-141.657,83.985), Jath::Point(-59.388,-141.245,85.695), Jath::Point(-57.435,-140.814,87.405), Jath::Point(-55.486,-140.365,89.115), Jath::Point(-53.541,-139.899,89.115), Jath::Point(-51.6,-139.417,89.115), Jath::Point(-49.662,-138.921,89.115), Jath::Point(-47.728,-138.411,89.115), Jath::Point(-45.798,-137.889,89.115), Jath::Point(-43.87,-137.357,89.115), Jath::Point(-41.945,-136.815,89.115), Jath::Point(-40.022,-136.265,89.115), Jath::Point(-38.101,-135.707,89.115), Jath::Point(-36.182,-135.143,89.115), Jath::Point(-34.265,-134.573,89.115), Jath::Point(-32.35,-133.999,89.115), Jath::Point(-30.435,-133.42,89.115), Jath::Point(-28.522,-132.838,89.115), Jath::Point(-26.609,-132.253,89.115), Jath::Point(-24.697,-131.666,89.115), Jath::Point(-22.658,-131.038,89.115), Jath::Point(-22.658,-131.038,0)};
Jath::Path redRushPath1 = Jath::Path::cm(redRushPath1Points);

void redRushAWP()
{
    logger.logStringEntry(100, timePassed(), "RedRushAWP Started");

    smartDrive.m_pos = art::Vec2::XandY(art::Tiles(-2.25), art::Tiles(-2.5));
	smartDrive.m_dir = art::Degrees(90);

    doinkerDeploy.set(true);

    followPath(redRushPath1, art::Inches(15));

    doinkerClamp.set(true);
    smartDrive.driveForPID(art::Inches(-24));
    doinkerClamp.set(false);


}  
