/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      10/18/2024, 8:30:35 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <WPILogger.h>

WPILogger wpi;

int main()
{

    wpi.logHeader();
    wpi.startBooleanEntry("ButtonLeft", 1);
    wpi.startBooleanEntry("ButtonRight", 2);
    wpi.startInt64Entry("Xpos", 3);
    wpi.startInt64Entry("Ypos", 4);
    wpi.startDoubleEntry("SomeVal", 5);
    wpi.startStringEntry("Alerts", 6);

    while (1)
    {

        Brain.Screen.setCursor(1, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Time = %f", timePassed()/1000000.f);

        Brain.Screen.setCursor(2, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("XPos = %d", Controller1.Axis4.position());
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("YPos = %d", Controller1.Axis3.position());

        Brain.Screen.setCursor(5, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("ButtonLeftPressing = %d", Controller1.ButtonLeft.pressing());

        Brain.Screen.setCursor(6, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("ButtonRightPressing = %d", Controller1.ButtonRight.pressing());

        // logger.putData("Xpos", (int)Controller1.Axis4.position());
        // logger.putData("Ypos", (int)Controller1.Axis3.position());

        wpi.logInt64Entry(3, timePassed(),Controller1.Axis4.position());
        wpi.logInt64Entry(4, timePassed(),Controller1.Axis3.position());
        wpi.logDoubleEntry(5, timePassed(), Controller1.Axis4.position()/Controller1.Axis3.position());
        

        if (Controller1.ButtonLeft.PRESSED)
        {
            wpi.logStringEntry(6, timePassed(), "ButtonLeft Pressed");
        }
        if (Controller1.ButtonRight.PRESSED)
        {
            wpi.logStringEntry(6, timePassed(), "ButtonRight Pressed");
        }

        wpi.logBooleanEntry(1, timePassed(),Controller1.ButtonLeft.pressing());
        wpi.logBooleanEntry(2, timePassed(),Controller1.ButtonRight.pressing());
        // logger.putData("ButtonRightPressing", Controller1.ButtonRight.pressing());

        if(Controller1.ButtonA.PRESSED){
            // logger.writeToFile("X:Log.csv");
            wpi.writeToFile("log.wpilog");
        }

        // Allow other tasks to run
        vex::this_thread::sleep_for(10);
    }
}
