#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
//bad ports: 6, 12, 16, 18 
brain Brain;
controller c;

//base motors:
  //Left Side
  motor topR= motor(PORT14, ratio6_1, false);
  motor frtR= motor(PORT15, ratio6_1, true);
  motor botR= motor(PORT13, ratio6_1, true);
  //Right Side
  motor topL= motor(PORT17, ratio6_1, true);
  motor frtL= motor(PORT16, ratio6_1, false);
  motor botL= motor(PORT18, ratio6_1, false);

//other motors:
  motor cata1 = motor(PORT12, ratio18_1, true);//left catamotor
  motor cata2 = motor(PORT20, ratio18_1, false);//right catamotor

//Pneumatics:
  //Auton stick:
  pneumatics astick = pneumatics(Brain.ThreeWirePort.C);
  //Wings:
  pneumatics wingR = pneumatics(Brain.ThreeWirePort.B);
  pneumatics wingL = pneumatics(Brain.ThreeWirePort.A);
  //Blocker fupddeadfwsf
  //pneumatics bonnetfold = pneumatics(Brain.ThreeWirePort.C);

  //Not really used for the v1 robot:
  //odom lifter
  //pneumatics odomlift = pneumatics (Brain.ThreeWirePort.F);
  //Hang:
  pneumatics hangup = pneumatics(Brain.ThreeWirePort.D);
  pneumatics hangdown=pneumatics(Brain.ThreeWirePort.E);


  //pneumatics intakelift = pneumatics(Brain.ThreeWirePort.G);

//Sensors:
  //odometry
  inertial gero = inertial(PORT11);
  rotation eside = rotation(PORT19, false);
  rotation evert = rotation(PORT1, false);
  
  //catapult
  rotation ecata = rotation(PORT21, true);
  limit catalimit = limit(Brain.ThreeWirePort.G);
  optical cataoptical =optical(PORT2,0);

  //vision
  vision vis = vision (PORT4, 50, MOGO_R, DISK);
	//signature BASKET_R= signature (1, 1109, 5401, 3255, -481, 1479, 499, 0.9, 0);
	signature DISK = signature (2, -1, 245, 122, -3551, -2707, -3129, 3.6, 0);
	signature MOGO_R = signature (1, 7061, 12025, 9544, -877, 103, -388, 2.3, 0);
  //
	signature ACORN_R = signature (1, 7061, 12025, 9544, -877, 103, -388, 2.3, 0);
	signature ACORN_GR = signature (1, 7061, 12025, 9544, -877, 103, -388, 2.3, 0);
	signature ACORN_B = signature (1, 7061, 12025, 9544, -877, 103, -388, 2.3, 0);





/*/*
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}
/*double pids(double target, double sensor, double kp, double ki, double kd, double kilimit = 0)
{
  double error, integral=0, derivative, preverror=0, output;
  error = target-sensor;
  integral = integral+error;
  derivative = error-preverror;
  wait(5,msec);
  preverror = error;
  output = (kp*error)+(ki+integral)+(kd+derivative);
  return output; 
}*/


