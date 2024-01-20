#pragma once

#include "vex.h"
#include "Units.h"
#include "PID.h"
#include "Sensor.h"

#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <map>

class SmartMotor : public vex::motor{
public:

    enum ControlMode{
        DutyCycle,
        Position,
        Angle,
        Velocity,
        Follower,
        Disabled
    };

    SmartMotor(std::string name, vex::motor mot);
    // SmartMotor(SmartMotor& motor);
    ~SmartMotor();

    void setConstants(double kp, double ki, double kd);
    void setConstants(double kp, double ki, double kd, double ff);
    SmartMotor& withConstants(double kp, double ki, double kd);
    SmartMotor& withConstants(double kp, double ki, double kd, double ff);

    void setControlMode(SmartMotor::ControlMode mode);
    SmartMotor& withControlMode(SmartMotor::ControlMode mode);

    ControlMode getControlMode();
    std::string getControlModeString();

    void setLeader(SmartMotor* leader);
    SmartMotor& withLeader(SmartMotor* leader);

    void addFollower(vex::motor mot);
    SmartMotor& withFollower(vex::motor mot);

    void setSensor(Sensor* sensor);
    SmartMotor& withSensor(Sensor* sensor);

    double get();
    operator double();
    double getOutput();

    void set(double cmd);
    void operator =(double cmd);

    void update();
    bool isCompleted();

private:

    static std::map<ControlMode, std::string> ModeToString;

    std::string m_name;

    ControlMode m_controlMode{Disabled};
    PID m_pid;

    SmartMotor* m_leaderMotor{nullptr};
    std::vector<std::shared_ptr <SmartMotor> > m_followingMotors;

    Sensor* m_sensor;

    double m_cmd{0};
    double m_output{0};
public:
    static std::vector< SmartMotor* > m_allMotors;
};