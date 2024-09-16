#pragma once
#include "vex.h"
#include "x\ColorSet.h"
#include "leds.h"
#include <stdint.h>
#include <initializer_list>
#include <vector>

namespace x{

    class Leds : public ColorSet{
    public:
        enum mode{
            STATIC,
            LOOP,
            BOUNCE,
            PULSE,
            STROBE,
            ANIMATION
        };

        std::vector<uint32_t>& getMirroredColors(){ 
            m_mirroredBuffer = *(*this);
                for (int i = 0 ; i<m_mirroredBuffer.size()/2; i++) {
                    m_mirroredBuffer [m_mirroredBuffer.size() -1 - i] = m_mirroredBuffer[i];
                }
            return m_mirroredBuffer;        
        }

        Leds(std::uint8_t strip_length) : ColorSet(strip_length), m_end(strip_length) { m_mode = STATIC; }

        mode getMode (){ return m_mode; }
        void setMode (mode newMode){ m_mode = newMode; }

        int getSpeed (){return m_speed;}
        void setSpeed (int speed) {m_speed = speed;}

        void setLimits (int start, int end){ m_start = start; m_end = end;}
        void setFillerColor (vex::color color){ m_fillerColor = color; }

        void setStrobeColors(std::initializer_list<vex::color> list){
            m_strobeColors.clear();
            for( auto elem : list )
            {
                m_strobeColors.push_back(elem);
            }
        }
        void setStrobeColors(std::vector<vex::color> list){
            m_strobeColors = list;
        }
        void setStrobeSpeed(int speed){m_stobeSpeed = speed;}

        void setMirrored(bool mirrored){m_mirrored = mirrored;}

        void update(addressable_led* led){
            switch (m_mode) {
            case STATIC:
                break;
            case LOOP:
                loop(m_speed);
                break;
            case BOUNCE:
                bounce(m_start, m_end, m_speed);
                break;
            case PULSE:
                pulse(m_speed, m_fillerColor);
                break;
            case STROBE:
                strobe(m_strobeColors, m_stobeSpeed);
                break;
            }
            if (m_mirrored) {
                if(led){
                    // led->set_buffer(getMirroredColors());
                    std::vector<uint32_t> temp = (getMirroredColors());
                    led->set(&temp[0] , 0, colors.size(), 0);
                }
            }else {
                if(led){
                    std::vector<uint32_t> temp = (*(*this));
                    led->set(&temp[0] , 0, colors.size(), 0);
                    // led->set_buffer(*(*this));
                }
            }
}

        

    private:
        mode m_mode;

        int m_speed{1};

        int m_start{0};
        int m_end;

        bool m_mirrored{false};

        std::vector<vex::color> m_strobeColors = {};
        int m_stobeSpeed{5};

        vex::color m_fillerColor{vex::color::black};

        std::vector <uint32_t> m_mirroredBuffer;
    };
}

// void ledTest1(){
//   xleds.setMode(x::Leds::mode::PULSE);
//   xleds.setSpeed(2);
//   xleds.setFillerColor(vex::color(0,0,25));
//   xleds.set(0,5, vex::color::yellow);
// }
// void ledTest2(double pct){
//   xleds.setMode(x::Leds::mode::STATIC);
//   xleds.setPos();
//   xleds.setAll(vex::color(25,25,25));
//   if(pct > 0){
//     xleds.set(0, (xleds.getColors().size()*(pct/100.f)), vex::color(0,100,0));
//   }else if(pct < 0){
//     xleds.set((xleds.getColors().size()* (1-(-pct/100.f)) ) ,xleds.getColors().size(), vex::color(100,0,0));
//   }else{

//   }
// }
// void ledTest3(){
//   xleds.setSpeed(1);
//   xleds.gradient(0,64,0,300);
//   xleds.setMode(x::Leds::mode::LOOP);
// }