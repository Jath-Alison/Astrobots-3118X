/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      10/18/2024, 8:30:35 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Logger.h"

Logger logger;

int main()
{

    while (1)
    {

        Brain.Screen.setCursor(1, 1);
        Brain.Screen.clearLine();
        Brain.Screen.print("Time = %f", timePassed());

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

        logger.putData("Xpos", (int)Controller1.Axis4.position());
        logger.putData("Ypos", (int)Controller1.Axis3.position());

        if (Controller1.ButtonLeft.PRESSED)
        {
            logger.putData("ButtonEvent", std::string("ButtonLeftPressed"));
        }
        logger.putData("ButtonRightPressing", Controller1.ButtonRight.pressing());

        if(Controller1.ButtonA.PRESSED){
            logger.writeToFile("X:Log.csv");
        }

        // Allow other tasks to run
        vex::this_thread::sleep_for(10);
    }
}
