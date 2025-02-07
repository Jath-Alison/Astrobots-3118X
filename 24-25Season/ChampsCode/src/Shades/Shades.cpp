#include "Shades/Shades.h"
#include "SubAutons.h"
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
            <text id="title" x="15" y="15" text="3118B - Astrobots" color="0xD07F07" bkgColor="0x4287F5FF" />

            <box id="0" x="0" y="77" width="480" height="54" color="0x0000FF" callback="" />
            <box id="0" x="0" y="210" width="480" height="32" color="0x32bff4" callback="" />

            <!-- <box id="0" x="150" y="0" width="20" height="77" color="0x000000" callback="" />
            <box id="0" x="170" y="77" width="20" height="54" color="0x000000" callback="" />
            <box id="0" x="150" y="131" width="20" height="77" color="0x000000" callback="" /> -->

            <box id="RedAutonsButton" x="5" y="136" width="150" height="67" color="0x000000" callback="RedAutons" outlineWidth="3" outlineColor="0xFF0000" />
            <box id="ZeroGyroButton" x="163" y="136" width="150" height="67" color="0x000000" callback="ZeroGyro" outlineWidth="3" outlineColor="0x00FF00" />
            <box id="BlueAutonsButton" x="320" y="136" width="150" height="67" color="0x000000" callback="BlueAutons" outlineWidth="3" outlineColor="0x0000FF" />

            <text id="TitleMimicL" x="10" y="232" text="Selected Auton Info" color="0x000000" bkgColor="0x32bff4"  font="prop20" />
            <text id="TitleMimicR" x="250" y="232" text="Current Rotation: " color="0x000000" bkgColor="0x32bff4"  font="prop20" />

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

        vex::thread eventThread(sds::Screen::eventLoop);
        vex::thread displayThread(sds::Screen::displayLoop);
        vex::thread dataUpdateThread(sds::dataUpdateLoop);
    }
    int dataUpdateLoop()
    {

        while (true)
        {

            std::shared_ptr<sds::displayable> d;
            std::stringstream ss;

            if(sds::Screen::getCurrentScreen() == "home"){
                d = sds::Screen::getElementById("TitleMimicR");
                ss.clear();
                if (d)
                {
                    ss << d->getBaseText() << smartDrive.m_dir.degrees();
                    d->setText(ss.str().c_str());
                }
            }

            vex::wait(100, vex::msec);
        }

        return 0;
    }
} // namespace sds
