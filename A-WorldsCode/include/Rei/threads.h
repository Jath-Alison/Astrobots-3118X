#pragma once
#include "Rei/screenfunctions.h"
#include "robotConfig.h"

namespace Rei
{
    using namespace vex;
    

    // set up diagnostics...////////////////////////////////////////////////////////////////////////////////////////////////
    // diag1 variables
    double dgx = 0, dgy = 0, dgvis = 0, dgvis2 = 0, dgcataw = 0, dgop = 0, dgop2 = 0;
    // diag2 variables
    double dgtemp = 0, dgw = 0, dglw = 0, dgrw = 0, dgctemp = 0, dgcw = 0;

    //:<
    int updateDiag()
    {
        while (1)
        {
            if (scrstate == DIAGNOSTICS_1)
            {
                dgx = smartDrive.m_pos.x;
                dgy = smartDrive.m_pos.y;
            }
            else if (scrstate == DIAGNOSTICS_2)
            {
                dgtemp = base.temperature(celsius);
                dgw = (smartDrive.m_left.power() + smartDrive.m_right.power()) / 2.0;
                dglw = smartDrive.m_left.power();
                dgrw = smartDrive.m_right.power();
            }
            this_thread::sleep_for(50);
        }
        return 0;
    }

    // configure screens/////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
      Some colors I like that are a bit complicated:
      Lavendar: 128,128,255
      Light cyan: 128,255,255
      Normal cyan:    0,255,255
      Teal: 0, 128,128
      Peach/apricot: 255,128,155
      Orange: 255,128,50
      Dark Green:   0,150,100
      Purple:  075,  0,200
    */
    vex::color lavendar(128, 128, 255);
    vex::color light_cyan(128, 255, 255);
    vex::color reg_cyan(0, 255, 255);
    vex::color teal(20, 255, 128);
    vex::color apricot(255, 128, 155);
    vex::color dark_green(0, 150, 100);
    vex::color purple_2(075, 0, 200);

    // set buttons
    scrButton nullb(1); // no button

    // AUTON SELECTION MENUES

    // select1 buttons and menu:
    // scrButton back1("back",nullv,MAIN_MENU_1,black);//color grey
    scrButton leftauton("Left  (Near)", auton::setLeft, SELECTING_2, 255, 0, 0);  // color red
    scrButton rightauton("Right (Far)", auton::setRight, SELECTING_2, 0, 0, 255); // color blue
    scrButton skillsauton("Skills", auton::setSkills, SELECTING_2, 0, 255, 0);    // color green
    scrButton solowpauton("Solowp", auton::setSolowp, SELECTING_2, 255, 255, 0);  // color yellow
    scrButton testing("test", auton::setTest, MAIN_MENU_1);                       // color grey
    scrMenu select1("   SELECT SIDE", 1, circle, leftauton, rightauton, solowpauton, skillsauton, testing, MAIN_MENU_1);
    // select2
    scrAuton select2v2("", 1, square, SELECTING_1);

    // mainmenu buttons
    // Screen 1:
    scrButton toSelect("Autons", nullv, SELECTING_1, 0, 255, 255);      // color teal
    scrButton toField("Field", nullv, FIELD_PRINTING, 58, 0, 255);      // color purple
    scrButton toVision("Vision", nullv, VISION_PRINTING, 255, 70, 200); // color lavendar
    scrButton toCata("Catapult", nullv, CATA_PRINTING, 75, 255, 75);
    // Screen 2:
    scrButton toSignal("Signalling", nullv, SIGNALLING, 255, 70, 70); // color pink
    scrButton toDiag1("Stats", nullv, DIAGNOSTICS_1, 255, 128, 155);  // color peach
    scrButton toDiag2("Health", nullv, DIAGNOSTICS_2, 255, 193, 0);   // color light orange
    // Navigation:
    scrButton toMenu1("<-back", nullv, MAIN_MENU_1);
    scrButton toMenu2("->next", nullv, MAIN_MENU_2);

    scrMenu mainMenu1(" WELCOME, 3118A", 1, square, toSelect, toField, toCata, toSignal, toMenu2);
    scrMenu mainMenu2(" WELCOME, 3118A", 1, square, toMenu1, toVision, toDiag1, toDiag2, nullb);
    // vision stuff
    scrVision ocular(MOGO_R, DISK);
    // diagnostics
    diagval cp1("robotx", dgx, 2, "  in");
    diagval cp2("roboty", dgy, 2, "  in");
    diagval cp3("robotr", base.cr, 2, " deg");
    diagval catae("cError", cata.error, 2, " deg");
    diagval cataw("cWound", dgcataw, 2, "deg");
    diagval catas("cStatus", catapult.statusA, 2);
    diagval aimrr("visError", dgvis, 2, "deg");
    diagval objx("Object center", dgvis2, 3, "px");
    diagval opthue("Hue value", dgop, 2);
    diagval opt2("Opt value", dgop2, 2);

    // screen 2
    diagval tempb("base temp", dgtemp, 2, "dg C");
    diagval pwr1("base power", dgw, 2, "W");
    diagval pwr2("Lpower", dglw, 2, "W");
    diagval pwr3("Rpower", dgrw, 2, "W");
    diagval tempc("intake temp", dgctemp, 2, "dg C");
    diagval pwrc("cata temp", dgcw, 2, "W");

    scrDiagnostics stats("STATS", cp1, cp2, cp3, catae, cataw, catas, aimrr, objx, opthue, opt2);
    scrDiagnostics health("HEALTH", tempb, pwr1, pwr2, pwr3, tempc, pwrc);

    // signalling stuff
    signalPack loading(0);
    scrSignal signalp = scrSignal(loading, catapult.signal);

    int buttonreturn = 0;
    int screenjunk()
    {
        // current screen control
        screen *currentscreen = &select1;
        int laststate;
        // button control
        bool brainpress;

        // auton selection
        int tempautonvalue; // temporary autonvalue to store auton category between screens 1 and 2

        scrstate = SELECTING_1; // initialize to field screen.

        // edit some things that can't be done in global space
        // change the formatiing of some of the diagnostics.
        tempb.setformatting(0, 16, 2);
        pwr1.setformatting(0, 16, 2);
        pwr2.setformatting(4, 16, 2);
        pwr3.setformatting(4, 16, 2);
        // set select1 to a return bar type screen.
        select1.bar.turnOn();
        // Assign auton programs to corresponding slots in bundles.
        auton::initializeBundles();

        while (true)
        {
            // Brain.Screen.clearScreen();
            laststate = scrstate;
            buttonreturn = 0;
            screenstep = 0;
            // switch screens according to the current screenstate
            switch (scrstate)
            {
            case MAIN_MENU_1:
            {
                currentscreen = &mainMenu1;
            }
            break;
            case MAIN_MENU_2:
            {
                currentscreen = &mainMenu2;
            }
            break;
            case SELECTING_1:
            {
                currentscreen = &select1;
            }
            break;
            case SELECTING_2:
            {
                currentscreen = &select2v2;
            }
            break;
            case FIELD_PRINTING:
            {
                currentscreen = &base.field;
            }
            break;
            case CATA_PRINTING:
            {
                currentscreen = &cataScreen;
            }
            break;
            case DIAGNOSTICS_1:
            {
                currentscreen = &stats;
            }
            break;
            case DIAGNOSTICS_2:
            {
                currentscreen = &health;
            }
            break;
            case VISION_PRINTING:
            {
                currentscreen = &ocular;
            }
            break;
            case SIGNALLING:
            {
                currentscreen = &signalp;
            }
            break;
            }

            // Initialize screen.
            currentscreen->On();
            currentscreen->print();
            currentscreen->resetPen();
            screenstep = 1;

            while (scrstate == laststate && buttonreturn == 0)
            {
                // update screen
                currentscreen->update();
                // disable press on first 2 frames; only allow button to return value on PRESSED mevent
                brainpress = Brain.Screen.PRESSED;
                buttonreturn =
                    currentscreen->returnvalue() // the screen's return value.
                    * (screenstep > 2)           // return 0 if on first 2 frames to prevent instantaneous button presses.
                    * brainpress;

                if (currentscreen->bar.isFull())
                { // exception for if the completion bar exits.
                    buttonreturn = 10;
                }

                screenstep++; // update diagnostic value
                this_thread::sleep_for(50);
            }

            // reset screen and pen.
            currentscreen->resetPen();
            currentscreen->Off(buttonreturn);
            screenstep = 2;
            this_thread::sleep_for(200);
        }
        return 0;
    }
} // namespace Rei
