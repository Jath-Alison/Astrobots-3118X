/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      8/15/2023, 10:25:34 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <iostream>

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::rotation rot(vex::PORT6);

// define your global instances of motors and other devices here

int serial_monitor(){
  while (true) {
    // use print if to transform some data you want
    // the name of the data(things before the ":") is very import.
    // it should be maintained the same in the same in both cpp file and py file

    printf("Data-Time:%f\n", Brain.timer(vex::sec));
    printf("Data-Pos:%f\n", rot.position(vex::degrees));
    printf("Data-Vel:%f\n", rot.velocity(vex::rpm));

    printf("Data-End\n");
    wait(0.1, vex::sec);
  }
}

int main() {
    vex::task serialM(serial_monitor); // run the function in a muti-task
    Brain.Screen.printAt( 10, 50, "Hello V5" );

    std::cout << "Hello World\n";
   
    while(1) {
        
        // Allow other tasks to run
        vex::this_thread::sleep_for(10);
    }
}
