#pragma once

#include "vex.h"
#include "Units.h"

namespace jwb{

    class Sensor{
    public:
        enum Type{
        Null = 0,
        RotationSensor,
        Encoder,
        Pot,
        PotV2
        };
        virtual Type getType() = 0;
        virtual double getPosition() {return 0;};
        virtual double getVelocity() {return 0;}; 
        virtual Angle getAngle() {return 0;};
    };

    class RotationSensor : public Sensor, public vex::rotation{
    public:
        RotationSensor(vex::rotation port) : vex::rotation(port) {
        // m_type = Type::RotationSensor;
        };
        Angle getAngle() override {return Degrees( angle(vex::degrees) );}
        double getPosition() override {return position(vex::degrees);}
        double getVelocity() override {return velocity(vex::rpm);}
        Type getType() override{
        return Sensor::Type::RotationSensor;
        }
    };

    class Encoder : public Sensor, public vex::encoder{
    public:
        Encoder(vex::triport::port& t) : vex::encoder(t){
        // m_type = Type::Encoder;
        }; 
        double getPosition() override {return Degrees( position(vex::degrees));}
        double getVelocity() override {return velocity(vex::rpm);}
        Type getType() override{
        return Sensor::Type::Encoder;
        }
    };

    class Pot : public Sensor, public vex::pot{
    public:
        Pot(vex::triport::port& t) : vex::pot(t){
        // m_type = Type::Pot;
        }; 
        double getPosition() override {return Degrees(angle(vex::degrees));}
        Angle getAngle() override {return Degrees(angle(vex::degrees));}
        Type getType() override{
        return Sensor::Type::Pot;
        }
    };  
    class PotV2 : public Sensor, public vex::potV2{
    public:
        PotV2(vex::triport::port& t) : vex::potV2(t){
        // m_type = Type::PotV2;
        }; 
        double getPosition() override {return Degrees(angle(vex::degrees));}
        Angle getAngle() override {return Degrees(angle(vex::degrees));}
        Type getType() override{
        return Sensor::Type::PotV2;
        }
    };  
}