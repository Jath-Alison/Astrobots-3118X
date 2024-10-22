#include "Autons.h"

// art::Vec2 travel;

void displayLoopFunction()
{
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
        Brain.Screen.print("Items: %u", logger.getDataSize());
        vex::this_thread::sleep_for(20);
    }
}

void logLoopFunction(){

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

    logger.startFloatArrayEntry("Controller/Axes", 1);
    logger.startBooleanArrayEntry("Controller/Buttons", 2);

    logger.startFloatArrayEntry("Motors/Command", 3);
    logger.startFloatArrayEntry("Motors/Speed", 4);
    logger.startFloatArrayEntry("Motors/Current", 5);
    logger.startFloatArrayEntry("Motors/Temperature", 6);

    logger.startDoubleArrayEntry("Robot/Pose", 7);
    logger.startDoubleArrayEntry("Robot/Pose(Blue)", 8);

    logger.startDoubleArrayEntry("Autons/TargetPos", 10);
    logger.startDoubleArrayEntry("Autons/TargetPos(Blue)", 11);

    std::vector<vex::motor*> allMotors = {
         &leftMotorA, &leftMotorB, &leftMotorC,
         &rightMotorA, &rightMotorB, &rightMotorC,
         &intake
        };

    while (1)
    {
        std::vector<float> axesStates = {
            float(Controller1.Axis1.position()),
            float(Controller1.Axis2.position()),
            float(Controller1.Axis3.position()),
            float(Controller1.Axis4.position())
            };
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
            art::Angle(smartDrive.m_dir).degrees()//converted to FRC scheme
        };

        std::vector<double> robotPoseBlue = {
            1.8 + art::Length(smartDrive.m_pos.x).meters(),
            1.8 + art::Length(smartDrive.m_pos.y).meters(),
            -(smartDrive.m_dir - art::Degrees(90))//converted to FRC scheme
        };

        std::vector<double> targetPose = {
            art::Length(travel.x).meters(),
            art::Length(travel.y).meters()
        };

        std::vector<double> targetPoseBlue = {
            1.8 + art::Length(travel.x).meters(),
            1.8 + art::Length(travel.y).meters(),
        };

        logger.logFloatArrayEntry(1, timePassed(), axesStates);
        logger.logBooleanArrayEntry(2, timePassed(), buttonStates);

        logger.logFloatArrayEntry(3, timePassed(), motorCommands);
        logger.logFloatArrayEntry(4, timePassed(), motorSpeeds);
        logger.logFloatArrayEntry(5, timePassed(), motorCurrents);
        logger.logFloatArrayEntry(6, timePassed(), motorTemperatures);

        logger.logDoubleArrayEntry(7, timePassed(), robotPose);
        logger.logDoubleArrayEntry(8, timePassed(), robotPoseBlue);

        logger.logDoubleArrayEntry(9, timePassed(), targetPose);
        logger.logDoubleArrayEntry(10, timePassed(), targetPoseBlue);

        if(Controller1.ButtonL1.pressing() && Controller1.ButtonR1.pressing()){
            logger.writeToFile("TestLog.wpilog");
        }
        
        vex::this_thread::sleep_for(20);
    }
}