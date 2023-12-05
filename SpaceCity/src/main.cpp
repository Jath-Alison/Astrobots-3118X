/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jatha                                                     */
/*    Created:      11/18/2023, 9:49:47 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <string>
#include "robotConfig.h"
// #include "Shades\Shades.h"
#include "x\Vec2.h"
// #include "x\Logger.h"
// #include "shades+.h"
// #include "DataSet.h"

// A global instance of competition
vex::competition Competition;
namespace x{
template<typename T>
  inline T cap(T input, T limit){
    if(input > limit){
      return limit;
    }else {
      return input;
    }
  }

  template<typename T>
  inline T floor(T input, T limit){
    if(input < limit){
      return limit;
    }else {
      return input;
    }
  }
}
void ledTest1(){
  xleds.setMode(x::Leds::mode::PULSE);
  xleds.setSpeed(2);
  xleds.setFillerColor(vex::color(0,0,25));
  xleds.set(0,5, vex::color::yellow);
}
void ledTest2(double pct){
  xleds.setMode(x::Leds::mode::STATIC);
  xleds.setPos();
  xleds.setAll(vex::color(25,25,25));
  if(pct > 0){
    xleds.set(0, (xleds.getColors().size()*(pct/100.f)), vex::color(0,100,0));
  }else if(pct < 0){
    xleds.set((xleds.getColors().size()* (1-(-pct/100.f)) ) ,xleds.getColors().size(), vex::color(100,0,0));
  }else{

  }

  
}
void ledTest3(){
  xleds.setSpeed(1);
  xleds.gradient(0,64,0,300);
  xleds.setMode(x::Leds::mode::LOOP);
}

int getSign(double in){
  if (in<0){return -1;}
  if (in>0){return 1;}
  return 0;
}

void turnToFace(double deg){
  bool running = true;
  int count = 0;
  while(running){
    double error = deg - inert.yaw();
    double speed = error*0.5;
    if(abs(speed) > 50){speed*=.25;} else {speed *= 0.5;}
    smartDrive.arcade(0, 0, speed + getSign(error)*15);
    if(abs(error) < 5){count++;}else{count = 0;}
    if(count > 20){running = false;}
    wait(0.05, vex::msec);
  }
  smartDrive.arcade(0, 0, 0);
}


void DriveTo(double inch){

  leftMotors.setPosition(0, vex::deg);
  rightMotors.setPosition(0, vex::deg);
  double deg = inch/(3.25 * 3.1415) * 360;
  double error = deg - (leftMotors.position(vex::degrees) + leftMotors.position(vex::degrees))/2.f;
  int count = 0;
  
  while(count < 20){
    double error = deg - (leftMotors.position(vex::degrees) + leftMotors.position(vex::degrees))/2.f;
    double speed = error*0.5;
    if(abs(speed) > 50){speed*=.25;} else {speed *= 0.25;}
    smartDrive.arcade(0, speed + getSign(error)*15, 0);
    if(abs(error) < 5){count++;}else{count = 0;}
    wait(0.05, vex::msec);
  }
  smartDrive.arcade(0, 0, 0);
}
// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  waitUntil(smartDrive.m_inert.isCalibrating() == false);
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  intake.set(-75);
  wait(2,vex::sec);
  intake.set(0);

  // intake.spin(vex::fwd);
  // wait(.25,vex::sec);
  // intake.stop();

  // smartDrive.arcade(0,75,0);
  // wait(1.5,vex::sec);
  // smartDrive.arcade(0,-50,0);
  // wait(0.5,vex::sec);
  // smartDrive.arcade(0,0,0);//right score 1 auton

  // wings.open();
  // smartDrive.arcade(0,-35,0);
  // wait(0.35,vex::sec);
  // smartDrive.arcade(0,-25,25);
  // wait(.75,vex::sec);
  // wings.close();
  // smartDrive.arcade(0,50,0);
  // wait(.75,vex::sec);
  // smartDrive.arcade(0,0,0);

  // intake.spin(vex::fwd, 5, vex::volt);
  // wait(.25,vex::sec);
  // intake.stop();

  // smartDrive.arcade(0,0,-35);
  // wait(.35,vex::sec);
  // smartDrive.arcade(0,75,0);
  // wait(.5,vex::sec);
  // smartDrive.arcade(0,0,-50);
  // wait(.2,vex::sec);
  // smartDrive.arcade(0,20,0);//left awp


  // intake.spin(vex::fwd, 5, vex::volt);
  // wait(.25,vex::sec);
  // intake.stop();

  // turnToFace(45);
  // wait(.25,vex::sec);
  // smartDriveTo(24);
  // wait(.25,vex::sec);
  // turnToFace(0);
  // smartDrive.arcade(0,100,0);
  // wait(.125,vex::sec);
  // smartDriveTo(-10);
  // wait(.25,vex::sec);
  // turnToFace(-90);
  // wait(.25,vex::sec);
  // smartDriveTo(48);

  

}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  waitUntil(smartDrive.m_inert.isCalibrating() == false);

    // leds.clear();   

    // x::Vec2 origin = x::XandY(0,0);

    // smartDrive.m_pos = x::XandY(x::Tiles(-1),x::Tiles(-1));
    // std::cout << "pos: " << x::Distance (smartDrive.m_pos.x).tiles() << "," << x::Distance (smartDrive.m_pos.y).tiles() << "\n";

    // DataSet <10> broadSet;

  while (1) {
    // std::cout << "pos: " << x::Distance (smartDrive.m_pos.x).tiles() << ", " << x::Distance (smartDrive.m_pos.y).tiles() << ", " << smartDrive.m_dir.degrees() << "\n";

    if (controller1.ButtonR1.pressing()) {
      // leds.clear(vex::color::green);
      intake.set(100);
    }else if (controller1.ButtonR2.pressing()){
      // leds.clear(vex::color::red);
      intake.set(-100);
    }else if(controller1.ButtonR1.RELEASED ){
      intake.set(50);
    } else if(controller1.ButtonR2.RELEASED ){
      intake.set(0);
    }
    
    if (controller1.ButtonX.PRESSED) {
      flywheel.set( x::cap<double>( flywheel.get()+10, 100));
      // flywheel.spin(vex::fwd, 12, vex::volt);
    }else if (controller1.ButtonB.PRESSED){
      flywheel.set(x::floor<double>( flywheel.get()-10, -100));
      // flywheel.spin(vex::fwd, 12, vex::volt);
    }else if ( controller1.ButtonA.pressing()){
      flywheel.set(0);
    }


    // if(controller1.ButtonA.pressing()){
    //   // smartDrive.turnTo(x::Degrees(0));
    //   // smartDrive.driveTo(x::Tiles(1));
    //   // smartDrive.turnTo(smartDrive.m_pos.angleTo(x::XandY(0,0)));
    //   // while(smartDrive.driveToPoint(x::XandY(0,0)).inches() > 5){}
    // }else
    if(controller1.ButtonL1.pressing()){
      smartDrive.arcade(0,controller1.Axis3.position()/2.f,controller1.Axis1.position()/3.f);
    }else{
      smartDrive.LeftSplitArcade(controller1);
    }

    if(controller1.ButtonLeft.pressing()){
      climb.open();
    }else{
      climb.close();
    }

    if(controller1.ButtonL2.PRESSED){
      wings.open();
    }else if(controller1.ButtonL2.RELEASED){
      wings.close();
    }

    if (controller1.ButtonY.PRESSED) {
      // std::cout << "avg: " << broadSet.getAverage() << "median: " << broadSet.getMedian() << std::endl;
      
      // Vision.takeSnapshot(GREEN_BROAD);
      // for (size_t i = 0; i < 16; i++)
      // {
      //   vision::object obj = Vision.objects[i];
      //   if (obj.angle != 0 || obj.centerX != 0 || obj.centerY != 0)
      //   {
      //     // std::cout << i << ":\n"
      //     //   << "\t" << "angle: " << obj.angle << "\n"
      //     //   << "\t" << "centerX: " << obj.centerX << "\n"
      //     //   << "\t" << "centerY: " << obj.centerY << "\n"
      //     //   << "\t" << "width: " << obj.width << "\n"
      //     //   << "\t" << "height: " << obj.height << "\n";
      //     Brain.Screen.drawRectangle(obj.originX, obj.originY, obj.width, obj.height);
      //   }
      // }
    }

    if (controller1.ButtonY.pressing()) {
      // Vision.takeSnapshot(GREEN_BROAD);
      // broadSet.put(Vision.largestObject.centerX - (315/2.f));
      // intake.set(35);
      // std::cout << "median: " << broadSet.getMedian() << "\n";
      // smartDrive.arcade(0,35, broadSet.getMedian() * .25);
    }

    // std::string output = "";
    // output = string_format("Hello World %d", flywheel.get());
    // ledTest2(flywheel.get());
    // xleds.update(&leds);

    vex::wait(20, vex::msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int tracking(){ smartDrive.track(); return 0;}
//
// Main will set up the competition functions and callbacks.
//
int main() {

  // smartDrive.m_rotScale = [](double rot){}

  // shadesInit();

  vex::task track(tracking);

  inert.calibrate();

  // Set up callbacks for autonomous and smartDriver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    vex::wait(100, vex::msec);
  }
}
