using namespace vex;

using signature = vision::signature;

extern brain Brain;
extern controller c;

//base motors:
extern motor topL;
extern motor topR;
extern motor frtL;
extern motor frtR;
extern motor botL;
extern motor botR;
//other motors:
extern motor cata1;
extern motor cata2;

//pneumatics:
extern pneumatics astick;
extern pneumatics hangup;
extern pneumatics hangdown;

extern pneumatics wingR;
extern pneumatics wingL;

extern pneumatics bonnetfold;
extern pneumatics odomlift;
extern pneumatics intakelift;

//sensors:
  //odom:
  extern inertial gero;
  extern rotation eside;
  extern rotation evert;
  //catapult stuff
  extern rotation ecata;
  extern limit catalimit;
  extern optical cataoptical;
  //Vision:
  extern vision vis;

//vision signatures
//extern signature BASKET_R;
extern signature DISK;
extern signature MOGO_R;
extern signature ACORN_GR;
extern signature ACORN_R;
extern signature ACORN_B;

extern signature Vision20__SIG_4;
extern signature Vision20__SIG_5;
extern signature Vision20__SIG_6;
extern signature Vision20__SIG_7;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
//double pids(doufewarawergnkjlo;jogqfwrijhpo[uq  wfee, double, double, double, double);
double absolute(double);
