#pragma once

#include "vex.h"

#include <cstdint>
#include <cmath>
#include <ostream>
#include <stdint.h>
#include <sys/stat.h>
#include <vector>
#include <iostream>

namespace x {


    struct ColorSet{
        static const int32_t MAX_LEDS = 64;
        ColorSet(int32_t max = MAX_LEDS){
            colors.resize(max);
            colorInts.resize(max);
        }

        std::vector<uint32_t>& operator*(){ 
            colorInts.clear();
            for (int i = 0; i < colors.size(); i++) {
                colorInts.push_back(colors[i]);
            }
            return colorInts;        
        }
        std::vector<vex::color>& getColors(){ 
            return colors;        
        }
        uint32_t& operator[](uint32_t index){ uint32_t c = colors[index]; return c; }

        void setAll(vex::color col){
            for (int i = 0; i < colors.size(); i++) {
                colors[i] = col;
            }
        }
        void setAll(std::vector<vex::color> cols){
            colors = cols;
        }
        void setAll(std::vector<uint32_t> cols){
            std::vector<vex::color> temp = {};
            for(uint32_t i : cols){
                temp.push_back(vex::color(i));
            }
            colors = temp;
        }
        void set(int pos, vex::color col, bool offset = false){
            
            int newPos = pos;

            if(offset){newPos += getPos();}
            if(newPos >= colors.size()){newPos -= colors.size();}

            if(pos >= 0 && pos < colors.size()){
                colors[newPos] = col;
            }
        }
        void set(int begin, int end, vex::color col, bool offset = false){

            int newBegin = begin;
            int newEnd = end;


            if(offset){newBegin += getPos(); newEnd += getPos();
                if(newBegin >= colors.size()){newBegin -= colors.size();}
                if(newEnd >= colors.size()){newEnd -= colors.size();}
            }

            if(newBegin < 0){
                newBegin = 0;
            }
            if (newEnd > colors.size()) {
                newEnd = colors.size();
            }
            for (int i = newBegin; i<newEnd; i++) {
                colors[i] = col;
            }
        }

        void gradient(int32_t start, int32_t end, double col1, double col2){

            if (start < 0){start = 0;}
            if (end >= colors.size()){end = colors.size()-1;}

            double unit = (col2 - col1) / (double)(end - start);

            double out = (double)col1;

            for (int32_t i=start; i<end; i++) {

                vex::color c;
                colors [i] = c.hsv(out,1,.25);
                
                out += unit;
            }
        }

        void loop(int speed){
            for (int i = 0; i < speed; i++) {
                colors.insert(colors.begin() , colors.back());
                colors.pop_back();
            }
        }

        void bounce(int start, int end, int speed = 1){
            if(dir){
                for (int i = 0; i < speed; i++) {
                    colors.insert(colors.begin() , colors.back());
                    colors.pop_back();
                    pos ++;
                }
                if(pos >= end - 1){dir = false;}
            }else {
                for (int i = 0; i < speed; i++) {
                    colors.push_back(colors.front());
                    colors.erase(colors.begin());
                    pos --;
                }
                if(pos <= start){dir = true;}
            }

        }
        int getPos(){return pos;}
        void setPos (int newPos = 0){pos = newPos;}

        void pulse(int speed, vex::color fillerCol){
            for (int i = 0; i < speed; i++) {
                colors.insert(colors.begin() , fillerCol);
                colors.pop_back();
            }
        }

        void strobe(std::vector<vex::color> strobeColors, int duration){
            static int counter = 0;
            static int current = 0;

            if(counter > duration){
                counter = 0;
                current ++;
            }

            if(current >= strobeColors.size()){current = 0;}

            setAll(strobeColors[current]);

            counter++;
        }

        protected:
            std::vector<vex::color> colors = {};
            std::vector<uint32_t> colorInts = {};

            int pos = 0;
            bool dir = true;
    };

}