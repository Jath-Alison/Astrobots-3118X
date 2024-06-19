#pragma once

#include "Jath\Sensors.h"
#include "Jath\Units.h"
#include "Jath\PID.h"

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <map>

namespace Jath
{

    class SmartMotor : public vex::motor
    {
    public:
        enum ControlMode
        {
            DUTY_CYCLE,
            POSITION,
            ANGLE,
            VELOCITY,
            FOLLOWER,
            DISABLED
        };

        SmartMotor(std::string name, vex::motor mot);
        SmartMotor(SmartMotor& motor);
        ~SmartMotor();

        std::string getName();
        
        ControlMode getControlMode();
        std::string getControlModeString();
        SmartMotor& withControlMode(SmartMotor::ControlMode mode);

        SmartMotor& withPID(PID p);
        
        SmartMotor& withLeader(SmartMotor* leader);
        SmartMotor& withFollower(vex::motor mot);
        SmartMotor& withSensor(Sensor* sensor);

        double get();
        double getOutput();
        double getFeedback();

        void set(double cmd);
        void operator =(double cmd);

        void update();
        bool isCompleted();

    private:

        static std::map<ControlMode, std::string> ModeToString;

        std::string m_name;

        ControlMode m_controlMode{DISABLED};
        PID m_pid;

        std::shared_ptr<Sensor> m_sensor;

        SmartMotor* m_leaderMotor{nullptr};
        std::vector<std::shared_ptr <SmartMotor> > m_followingMotors;

        double m_cmd{0};
        double m_output{0};
        double m_feedback{0};

    private:
        static std::vector<SmartMotor *> m_allMotors;
    public:
        static SmartMotor& getMotor(std::string name);
        static void updateAllMotors();
    };

    int updateMotorLoop();

} // namespace Jath