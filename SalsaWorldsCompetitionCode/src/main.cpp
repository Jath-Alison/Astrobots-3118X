/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      6/6/2024, 3:42:38 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <string>
#include <fstream>
#include <sstream>

#include "RobotConfig.h"

#include "Jath\Vec2.h"
#include "Jath\Path.h"
#include "Jath\Motors\jMotorGroup.h"
#include "Jath\Graph.h"

#include "Command.h"
#include "AutonPaths.h"
#include "Vision.h"

// A global instance of competition
vex::competition Competition;

void waitForInert(){
    while(smartDrive.m_inert.isCalibrating()){
        vex::wait(5, vex::msec);
    }
}

void pre_auton(void)
{
}

void auto_isolation(void) {

    smartDrive.m_pos = testPathU.m_points.front().m_pos;
    smartDrive.m_dir = Jath::Degrees(90);

    followPath(testPathU, Jath::Inches(10));
    smartDrive.turnTo(Jath::Degrees(90));
    
    smartDrive.arcade(0,75,0);
    intake.set(-100);

    vex::wait(3, vex::sec);
    smartDrive.arcade(0,0,0);
    // smartDrive.turnTo(Jath::Degrees(0));
    // smartDrive.driveTo(Jath::Tiles(1));
    // smartDrive.turnTo(Jath::Degrees(-90));
}

void auto_interaction(void) {
    intake.set(-100);

    smartDrive.driveTo(Jath::Tiles(-1));

    smartDrive.arcade(0,0,0);
    vex::wait(3, vex::sec);
    smartDrive.arcade(0,0,0);


    // smartDrive.turnTo(Jath::Degrees(180));
    // smartDrive.driveTo(Jath::Tiles(1));
    // smartDrive.turnTo(Jath::Degrees(0));
}

bool firstAutoFlag = true;

void autonomous_main(void)
{
    waitForInert();
    if (firstAutoFlag)
    {
        firstAutoFlag = false;
        auto_isolation();
    }
    else
    {
        auto_interaction();
    }
}

void usercontrol(void)
{
    waitForInert();
    // User control code here, inside the loop
    while (1)
    {
        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("pose: %f, %f, %f", Jath::Distance(smartDrive.m_pos.x).inches(), Jath::Distance(smartDrive.m_pos.y).inches(), smartDrive.m_dir.degrees());
    // Brain.Screen.setCursor(2,1);
    //   Brain.Screen.print("isReceiving %d", link.isReceiving());
    // Brain.Screen.setCursor(3,1);
        smartDrive.driveToGraph.drawGraph(
                    Jath::Vec2::XandY(0,100),
                    Jath::Vec2::XandY(400,200)
                );


        smartDrive.LeftSplitArcadeCurved(controller1);

        if (controller1.ButtonR1.pressing())
        {
            intake.set(100);
        }
        else if (controller1.ButtonR2.pressing())
        {
            intake.set(-100);
        }
        else
        {
            intake.set(0);
        }

        if (controller1.ButtonUp.PRESSED)
        {
            smartDrive.turnTo(Jath::Degrees(0));
        }
        else if (controller1.ButtonRight.PRESSED)
        {
            smartDrive.turnTo(Jath::Degrees(90));
        }else if (controller1.ButtonLeft.PRESSED)
        {
            smartDrive.turnTo(Jath::Degrees(-90));
        }else if (controller1.ButtonDown.PRESSED)
        {
            smartDrive.turnTo(Jath::Degrees(180));
        }

        if (controller1.ButtonX.PRESSED)
        {
            smartDrive.driveToHoldAngle(Jath::Inches(24));
        }
        else if (controller1.ButtonB.PRESSED)
        {
            smartDrive.driveToHoldAngle(Jath::Inches(-24));
        }else if (controller1.ButtonA.PRESSED)
        {
            // smartDrive.m_pos = testPathU.m_points.front().m_pos;
            // smartDrive.m_dir = Jath::Degrees(90);
            // followPath(testPathU, Jath::Inches(20));
            driveTowardBall(true);
            while(driveTowardBall(false) == false && smartDrive.m_pos.y < Jath::Tiles(2)){
                vex::wait(20,vex::msec);
            }
            smartDrive.driveToPoint(Jath::Vec2::XandY(0,0));
            smartDrive.turnTo(Jath::Degrees(90));
            intake.set(-50);
            vex::wait(1,vex::sec);
        }else if (controller1.ButtonA.pressing()){
            // driveTowardBall(false);
        }

        vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
                                  // prevent wasted resources.
    }
}

void track() { 
    waitForInert();
    smartDrive.track(); }

int main()
{

    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous_main);
    Competition.drivercontrol(usercontrol);

    vex::thread tracking(track);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true)
    {
        vex::wait(100, vex::msec);
    }
}
