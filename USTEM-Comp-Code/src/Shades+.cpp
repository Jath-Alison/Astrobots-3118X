#include "shades+.h"

void shadesInit()
{
    const char * xml = R"(
    <?xml version="1.0" encoding="utf-8"?>
    <root>
      <shades>
        <screen id="home">
          <box id="box" x="0" y="0" width="480" height="240" callback="" color="0x4287F5FF"/>
          <text id="title" x="15" y="15" text="3118B - Astrobots" color="0xFCB040FF" />
          <text id="title" x="15" y="45" text="Shades" color="0xFCB040FF" />

          <image id="0" x="7" y="107" src="AstrobotsLogo.png" callback="" />

          <box id="auton_button" x="260" y="15" width="200" height="60" color="0xFFFFFFFF" callback="auton" />
          <text id="0" x="275" y="25" text="Auton Select" color="0x000000FF" callback="" />

          <box id="stats_home_button" x="260" y="90" width="200" height="60" color="0xFFFFFFFF" callback="stats_home" />
          <text id="0" x="275" y="100" text="Robot Stats" color="0x000000FF" callback="" />

          <box id="0" x="260" y="165" width="200" height="60" color="0xFFFFFFFF" callback="" />
          <text id="programData" x="260" y="175" text="" color="0x000000FF" callback="" />
        </screen>
        
        <screen id="auton">
          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <text id="autonDisplay" x="55" y="5" text="Auton Selector" color="0xFCB040FF" callback="" />

          <box id="0" x="15" y="65" width="130" height="72" color="0xFF0000FF" callback="" />
          <box id="0" x="15" y="152" width="130" height="72" color="0xFF0000FF" callback="" />

          <image id="fieldImage" x="160" y="65" src="Over Under field.png" callback="" />

          <box id="0" x="335" y="65" width="130" height="72" color="0x0000FFFF" callback="" />
          <box id="0" x="335" y="152" width="130" height="72" color="0x0000FFFF" callback="" />
        </screen>

        <screen id="stats_home">
          <box id="0" x="0" y="0" width="480" height="50" color="0xFF0000FF" callback="" />
          <text id="0" x="65" y="15" text="Motor Temperature" color="0x000000FF" callback="" />

          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <image id="Motor1" x="17" y="50" src="Motor.png" callback="" />
          <image id="Motor2" x="125" y="50" src="Motor.png" callback="" />
          <image id="Motor3" x="234" y="50" src="Motor.png" callback="" />
          <image id="Motor4" x="343" y="50" src="Motor.png" callback="" />

          <image id="Motor5" x="17" y="144" src="Motor.png" callback="" />
          <image id="Motor6" x="125" y="144" src="Motor.png" callback="" />
          <image id="Motor7" x="234" y="144" src="Motor.png" callback="" />
          <image id="Motor8" x="343" y="144" src="Motor.png" callback="" />
          
          <text id="0" x="20" y="110" text="Left-F" color="0xFFFFFFFF" callback="" />
          <text id="0" x="128" y="110" text="Right-F" color="0xFFFFFFFF" callback="" />
          <text id="0" x="237" y="110" text="Intake-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="346" y="110" text="Intake-L" color="0xFFFFFFFF" callback="" />
          
          <text id="0" x="20" y="204" text="Left-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="128" y="204" text="Right-R" color="0xFFFFFFFF" callback="" />
          <text id="0" x="237" y="204" text="Catapult" color="0xFFFFFFFF" callback="" />
          <text id="0" x="346" y="204" text="Climb" color="0xFFFFFFFF" callback="" />

          <box id="0" x="450" y="60" width="30" height="120" color="0xFFFFFFFF" callback="stats_extend" />

        </screen>
        <screen id="stats_extend">
          <box id="0" x="0" y="0" width="480" height="50" color="0xFF0000FF" callback="" />
          <text id="0" x="65" y="15" text="Location Stats" color="0x000000FF" callback="" />

          <circle id="returnHome" x="25" y="25" radius="20" color="0xFFFFFFFF" callback="home" />
          <image id="0" x="5" y="5" src="Home.png" callback="" />

          <box id="0" x="0" y="60" width="30" height="120" color="0xFFFFFFFF" callback="stats_home" />
        </screen>
      </shades>
    </root>    
  )";

    if(Brain.SDcard.isInserted()){
        sds::Screen::initialize();
    }else{
        sds::Screen::initialize(xml);
    }

    sds::Screen::addCallback("Auton1",auton1);
    sds::Screen::addCallback("Auton2",auton2);
    sds::Screen::addCallback("Auton3",auton3);
    sds::Screen::addCallback("Auton4",auton4);

    vex::thread eventThread(sds::Screen::eventLoop);
    vex::thread displayThread(sds::Screen::displayLoop);
    vex::thread updateThread(updateAll);
}

void updateTitleText()
{
    if(sds::Screen::getScreenId() == "home"){
        sds::displayable* title = sds::Screen::getElementById("title2").get();
        if(title){
            title->setText("AutonDisabled");
        }
    }
}

void updateMotors()
{
    for (size_t i = 0; i < motorWatchers.size(); i++)
    {
        sds::displayable* ptr = sds::Screen::getElementById(motorWatchers[i].id).get();
        if(ptr){
            ptr->setText(motorWatchers[i].getSrc());
        }
    }
    
}


void auton1()
{
    selectedAuton = "Auton1";
    initPos = x::XandY(0,0);
    initDir = x::Angle();
    sds::Screen::load("home");
}
void auton2()
{
    selectedAuton = "Auton2";
    sds::Screen::load("home");
}
void auton3()
{
    selectedAuton = "Auton3";
    sds::Screen::load("home");
}
void auton4()
{
    selectedAuton = "Auton4";
    sds::Screen::load("home");
}

int updateAll()
{
    while(true){
        updateTitleText();
        updateMotors();
        wait(1,vex::sec);
    }
}

std::string motorWatcher::getSrc()
{
    if(Brain.Screen.pressing()){
        return "Motorb.png";
    }
    
    return "Motor.png";
}