#include "Shades/Shades.h"
#include "SubAutons.h"
#include "AutonSelect.h"
#include <sstream>

namespace sds
{
    void shadesInit()
    {
        const char *xml = R"(
    <?xml version="1.0" encoding="utf-8"?>
<root>
    <shades>
        <screen id="home">
            <box id="box" x="0" y="0" width="480" height="240" callback="" color="0x4287F5FF"/>

            <box id="ChainBar" x="0" y="77" width="480" height="54" color="0x777777" callback="" />
            <box id="BottomBar" x="0" y="210" width="480" height="32" color="0x32bff4" callback="" />

            <text id="AutonTitle" x="7" y="55" text="" color="0x000000" bkgColor="0x4287F5FF" font="propXL" />

            <!-- <box id="0" x="150" y="0" width="20" height="77" color="0x000000" callback="" />
            <box id="0" x="170" y="77" width="20" height="54" color="0x000000" callback="" />
            <box id="0" x="150" y="131" width="20" height="77" color="0x000000" callback="" /> -->

            <box id="RedAutonsButton" x="5" y="136" width="150" height="67" color="0x000000" callback="RedAutons" outlineWidth="3" outlineColor="0xFFFFFF" />
            <text id="RedAutonsLabel" x="36" y="175" text="Autons" color="0xFFFFFF" bkgColor="0x0000" font="prop20" />

            <box id="ZeroGyroButton" x="163" y="136" width="150" height="67" color="0x000000" callback="ZeroGyro" outlineWidth="3" outlineColor="0x00FF00" />
            <text id="ZeroGyroLabel" x="195" y="175" text="Zero Gyro" color="0x00FF00" bkgColor="0x0000" font="prop20" />

            <!-- <box id="BlueAutonsButton" x="321" y="136" width="150" height="67" color="0x000000" callback="BlueAutons" outlineWidth="3" outlineColor="0x0000FF" />
            <text id="BlueAutonsLabel" x="351" y="175" text="Blue Autons" color="0x0000FF" bkgColor="0x0000" font="prop20" /> -->

            <text id="TitleMimicL" x="10" y="232" text="Status: " color="0x000000" bkgColor="0x32bff4" font="prop20" />
            <text id="TitleMimicR" x="250" y="232" text="Current Rotation: " color="0x000000" bkgColor="0x32bff4" font="prop20" />

        </screen>

        <screen id="RedAutons">
            <box id="ChainBar" x="0" y="77" width="480" height="54" color="0xFF0000" callback="" />
            <box id="BottomBar" x="0" y="210" width="480" height="32" color="0x32bff4" callback="" />

            <box id="LeftAutonButton" x="5" y="136" width="230" height="67" color="0x000000" callback="LeftAuton" outlineWidth="3" outlineColor="0xFF0000" />
            <text id="LeftAutonButtonLabel" x="10" y="175" text="" color="0xFF0000" bkgColor="0x0000" font="prop20" />

            <box id="RightAutonButton" x="245" y="136" width="230" height="67" color="0x000000" callback="RightAuton" outlineWidth="3" outlineColor="0x0000FF" />
            <text id="RightAutonButtonLabel" x="250" y="175" text="" color="0x0000FF" bkgColor="0x0000" font="prop20" />

            <box id="HomeButton" x="163" y="5" width="150" height="64" color="0x000000" callback="home" outlineWidth="3" outlineColor="0x00FF00" />
            <text id="HomeLabel" x="195" y="45" text="Home" color="0x00FF00" bkgColor="0x0000" font="prop20" />

            <box id="AutonScrollLeft" x="5" y="5" width="150" height="64" color="0x000000" callback="ScrollAutonLeft" outlineWidth="3" outlineColor="0xFF0000" />
            <text id="AutonScrollLeftLabel" x="36" y="45" text="Scroll Left" color="0xFF0000" bkgColor="0x0000" font="prop20" />
            <box id="AutonScrollRight" x="321" y="5" width="150" height="64" color="0x000000" callback="ScrollAutonRight" outlineWidth="3" outlineColor="0x0000FF" />
            <text id="AutonScrollRightLabel" x="351" y="45" text="Scroll Right" color="0x0000FF" bkgColor="0x0000" font="prop20" />

            <text id="TitleMimicL" x="10" y="232" text="" color="0x000000" bkgColor="0x32bff4" font="prop20" />
            <text id="TitleMimicR" x="250" y="232" text="Current Rotation: " color="0x000000" bkgColor="0x32bff4" font="prop20" />
        </screen>

        <screen id="BlueAutons">
            <box id="ChainBar" x="0" y="77" width="480" height="54" color="0x0000FF" callback="" />
            <box id="BottomBar" x="0" y="210" width="480" height="32" color="0x32bff4" callback="" />


            <text id="TitleMimicL" x="10" y="232" text="Selected Auton Info" color="0x000000" bkgColor="0x32bff4" font="prop20" />
            <text id="TitleMimicR" x="250" y="232" text="Current Rotation: " color="0x000000" bkgColor="0x32bff4" font="prop20" />
        </screen>

    </shades>
</root>
  )";

        if (Brain.SDcard.isInserted() && Brain.SDcard.exists("ConfigFile.xml"))
        {
            sds::Screen::initialize();
        }
        else
        {
            sds::Screen::initialize(xml);
        }

        sds::Screen::addCallback("ZeroGyro", zeroGyro);
        sds::Screen::addCallback("ScrollAutonRight", incAutonView);
        sds::Screen::addCallback("ScrollAutonLeft", decAutonView);

        sds::Screen::addCallback("LeftAuton", selectAutonLeft);
        sds::Screen::addCallback("RightAuton", selectAutonRight);

        vex::thread eventThread(sds::Screen::eventLoop);
        vex::thread displayThread(sds::Screen::displayLoop);
        vex::thread dataUpdateThread(sds::dataUpdateLoop);
    }
    int dataUpdateLoop()
    {

        int leftId = 0;

        while (true)
        {

            std::shared_ptr<sds::displayable> d;
            std::stringstream ss;

            if (sds::Screen::getCurrentScreen() == "home")
            {
                // resetAutonView();
                d = sds::Screen::getElementById("TitleMimicR");
                ss.clear();
                ss.str("");

                if (d)
                {
                    // ss << d->getBaseText() << asyncDrive.getDir().degrees();
                    ss << "Pos: (" << int(4*art::Length(asyncDrive.getPos().x).inches())/4.0 << "," << int(4*art::Length(asyncDrive.getPos().y).inches())/4.0 << ")";
                    d->setText(ss.str().c_str());
                }

                d = sds::Screen::getElementById("AutonTitle");
                ss.clear();
                ss.str("");

                if (d)
                {
                    ss << d->getBaseText() << autonSelect.getAutonName(currentAutonId);
                    d->setText(ss.str().c_str());
                }

                d = sds::Screen::getElementById("TitleMimicL");
                ss.clear();
                ss.str("");

                if (d)
                {
                    if(currentAutonId == 0)
                        ss << d->getBaseText() << "Auton Not Selected";
                    else if (!gyroZeroed)
                        ss << d->getBaseText() << "Gyro Not Zeroed";
                    else
                        ss << d->getBaseText() << "Ready to Run";
                    d->setText(ss.str().c_str());
                }
            }
            else if (sds::Screen::getCurrentScreen() == "RedAutons")
            {
                d = sds::Screen::getElementById("LeftAutonButtonLabel");
                ss.clear();
                ss.str("");

                if (d)
                {
                    ss << d->getBaseText() << autonSelect.getAutonName(currentAutonView);
                    d->setText(ss.str().c_str());
                }

                d = sds::Screen::getElementById("RightAutonButtonLabel");
                ss.clear();
                ss.str("");

                if (d)
                {
                    ss << d->getBaseText() << autonSelect.getAutonName(currentAutonView + 1) << currentAutonId;
                    d->setText(ss.str().c_str());
                }

                d = sds::Screen::getElementById("TitleMimicR");
                ss.clear();
                ss.str("");

                if (d)
                {
                    ss << d->getBaseText() << asyncDrive.getDir().degrees();
                    d->setText(ss.str().c_str());
                }

                d = sds::Screen::getElementById("AutonTitle");
                ss.clear();
                ss.str("");

                if (d)
                {
                    ss << d->getBaseText() << autonSelect.getAutonName(currentAutonId);
                    d->setText(ss.str().c_str());
                }

                d = sds::Screen::getElementById("TitleMimicL");
                ss.clear();
                ss.str("");

                if (d)
                {
                    if(currentAutonId == 0)
                        ss << d->getBaseText() << "Auton Not Selected";
                    else if (!gyroZeroed)
                        ss << d->getBaseText() << "Gyro Not Zeroed";
                    else
                        ss << d->getBaseText() << "Ready to Run";
                    d->setText(ss.str().c_str());
                }
            }

            vex::wait(100, vex::msec);
        }

        return 0;
    }
} // namespace sds
