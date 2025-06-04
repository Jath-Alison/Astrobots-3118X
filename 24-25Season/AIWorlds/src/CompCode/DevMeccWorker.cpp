#include "RobotConfig/RobotConfig.h"

#if CURRENT_ROBOT == Dev_Mecc_Worker
void pre_auton(void) {
  RobotName = "Dev_Mecc_Worker";
  link.received(receive_message);
}

void autonomous(void) {
}

std::string currentCmd = "";
void receive_message( const char *message, const char *linkname, int32_t index, double value ){
  // message is the received message
  // linkname is the link name for the message_link that received the message
  // index is optional int32_t variable
  // value is optional double variable

  currentCmd = message;
}

int counter = 0;

void usercontrol(void) {
  while (1) {

    if (Controller1.ButtonA.pressing()) {
      mot_lf.spin(vex::fwd, 50, vex::percent);
      mot_lb.spin(vex::fwd, 50, vex::percent);
      mot_rf.spin(vex::fwd, 50, vex::percent);
      mot_rb.spin(vex::fwd, 50, vex::percent);
    } else if (Controller1.ButtonX.pressing()) {
      mot_lf.spin(vex::fwd, -50, vex::percent);
      mot_lb.spin(vex::fwd, -50, vex::percent);
      mot_rf.spin(vex::fwd, -50, vex::percent);
      mot_rb.spin(vex::fwd, -50, vex::percent);
    }else if(currentCmd == "TurnFor1Sec"){
      mot_lf.spin(vex::fwd, 50, vex::percent);
      mot_lb.spin(vex::fwd, 50, vex::percent);
      mot_rf.spin(vex::fwd, -50, vex::percent);
      mot_rb.spin(vex::fwd, -50, vex::percent);
      currentCmd = ""; // Reset command after execution
      counter = 50;
    }else{
      if (counter > 0){
        counter--;
      }else{
        mot_lf.stop();
        mot_lb.stop();
        mot_rf.stop();
        mot_rb.stop();
      }
    }
    

    vex::wait(20, vex::msec);
  }
}

void periodic(void) {
  while (1)
  {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(RobotName.c_str());

    Brain.Screen.setCursor(2, 1);//time
    Brain.Screen.print("Time: %d:%02d", (int)vex::timer::system() / (60 * 1000), (int)vex::timer::system() % (60 * 1000));

    
    
    vex::wait(20, vex::msec);
  }
}
#endif
