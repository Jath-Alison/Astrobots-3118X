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

    leftFlapper.spinTo(-90,vex::deg,false);
    rightFlapper.spinTo(-90,vex::deg,false);

    vex::wait(1, vex::sec);

    smartDrive.arcade(0,-50,0);
    vex::wait(0.75,vex::sec);

    smartDrive.arcade(0,100,0);
    vex::wait(3,vex::sec);

    smartDrive.arcade(0,-25,25);
    vex::wait(1,vex::sec);

    shooter.set(100);
    intake.set(100);
    while(true){

        leftFlapper.spinTo(30,vex::deg,false);
        rightFlapper.spinTo(30,vex::deg,false);

        vex::wait(1,vex::sec);

        leftFlapper.spinTo(-30,vex::deg,false);
        rightFlapper.spinTo(-30,vex::deg,false);

        vex::wait(1,vex::sec);
    }

    // smartDrive.m_pos = testPathU.m_points.front().m_pos;
    // smartDrive.m_dir = Jath::Degrees(90);

}

void auto_interaction(void) {
    smartDrive.arcade(0,-15,15);
    vex::wait(2,vex::sec);

    shooter.set(100);
    intake.set(100);
    while(true){

        leftFlapper.spinTo(30,vex::deg,false);
        rightFlapper.spinTo(30,vex::deg,false);

        vex::wait(1,vex::sec);

        leftFlapper.spinTo(-30,vex::deg,false);
        rightFlapper.spinTo(-30,vex::deg,false);

        vex::wait(1,vex::sec);
    }
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

        if (controller1.ButtonL1.pressing())
        {
            leftFlapper.spinTo(15,vex::deg,false);
            rightFlapper.spinTo(15,vex::deg,false);
        }
        else if (controller1.ButtonL2.pressing())
        {
            leftFlapper.spinTo(-30,vex::deg,false);
            rightFlapper.spinTo(-30,vex::deg,false);
        }
        else
        {
            leftFlapper.spinTo(0,vex::deg,false);
            rightFlapper.spinTo(0,vex::deg,false);
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
            shooter.set(100);
            // smartDrive.driveToHoldAngle(Jath::Inches(24));
        }
        else if (controller1.ButtonB.PRESSED)
        {
            shooter.set(-100);
            // smartDrive.driveToHoldAngle(Jath::Inches(-24));
        }else if (controller1.ButtonA.PRESSED)
        {
            shooter.set(0);
            // smartDrive.m_pos = testPathU.m_points.front().m_pos;
            // followPath(testPathU, Jath::Inches(10));
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
