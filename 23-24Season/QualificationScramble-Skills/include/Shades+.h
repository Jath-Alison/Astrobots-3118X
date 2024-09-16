#pragma once

#include "Shades\Shades.h"
#include <string>
#include <vector>
#include "vex.h"
#include "robotConfig.h"

inline std::string selectedAuton = "no Auton selected";

struct motorWatcher{
    std::string id;
    vex::motor mot;
    motorWatcher(std::string id, vex::motor mot):id(id),mot(mot){}
    std::string getSrc();
};
inline std::vector<motorWatcher> motorWatchers = {
    motorWatcher("LeftMotors", LeftMotors),
    motorWatcher("RightMotors", RightMotors),
};

void shadesInit();

void updateTitleText();
void updateMotors();

void auton1();
void auton2();
void auton3();
void auton4();

int updateAll();