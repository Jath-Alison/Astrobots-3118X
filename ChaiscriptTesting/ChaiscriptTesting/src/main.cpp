/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      6/22/2023, 10:28:43 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

#include <chaiscript/chaiscript.hpp>

double function(int i, double j)
{
  return i * j;
}


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here


int main() {

    chaiscript::ChaiScript chai;
    chai.add(chaiscript::fun(&function), "function");

    double d = chai.eval<double>("function(3, 4.75);");

    Brain.Screen.printAt( 10, 50, "Hello V5" );
   
    while(1) {
        
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
