#include "Jath\Motors\SmartMotor.h"

namespace Jath
{
    std::map<SmartMotor::ControlMode, std::string> SmartMotor::ModeToString{
        {SmartMotor::ControlMode::DUTY_CYCLE, "DutyCycle"},
        {SmartMotor::ControlMode::POSITION, "Position"},
        {SmartMotor::ControlMode::ANGLE, "Angle"},
        {SmartMotor::ControlMode::VELOCITY, "Velocity"},
        {SmartMotor::ControlMode::FOLLOWER, "Follower"},
        {SmartMotor::ControlMode::DISABLED, "Disabled"},
    };

    std::vector<SmartMotor *> SmartMotor::m_allMotors;

    SmartMotor::SmartMotor(std::string name, vex::motor mot) : vex::motor(mot), m_name(name)
    {
        m_allMotors.push_back(this);
    }

    SmartMotor::SmartMotor(SmartMotor &motor)
        : vex::motor(motor), m_name(motor.m_name), m_controlMode(motor.m_controlMode), m_pid(motor.m_pid), m_leaderMotor(motor.m_leaderMotor), m_followingMotors(motor.m_followingMotors), m_sensor(motor.m_sensor)
    {
        // std::cout << "creating Motor:" << m_name << this << "\n";
        m_allMotors.push_back(this);
        for (size_t i = 0; i < m_followingMotors.size(); i++)
        {
            if (m_followingMotors[i])
            {
                m_followingMotors[i]->withLeader(this);
            }
            else
            {
                m_followingMotors.erase(m_followingMotors.begin() + i);
            }
        }
    }

    SmartMotor::~SmartMotor()
    {
        for (int i = 0; i < m_allMotors.size(); i++)
        {
            if (m_allMotors[i] == this)
            {
                m_allMotors.erase(m_allMotors.begin() + i);
                // std::cout << "erasing Motor:" << m_name << this << "\n";
            }
        }
    }

    std::string SmartMotor::getName() { return m_name; }

    SmartMotor::ControlMode SmartMotor::getControlMode() { return m_controlMode; }
    std::string SmartMotor::getControlModeString() { return ModeToString[m_controlMode]; }

    SmartMotor &SmartMotor::withControlMode(SmartMotor::ControlMode mode)
    {
        m_controlMode = mode;
        return *this;
    }

    SmartMotor &SmartMotor::withPID(PID p)
    {
        m_pid = p;
        return *this;
    }

    SmartMotor &SmartMotor::withLeader(SmartMotor *leader)
    {
        m_leaderMotor = leader;
        return *this;
    }
    SmartMotor &SmartMotor::withFollower(vex::motor mot)
    {
        m_followingMotors.push_back(std::make_shared<SmartMotor>(m_name + " follower", mot));
        m_followingMotors.back()->withLeader(this);
        return *this;
    }
    SmartMotor &SmartMotor::withSensor(Sensor *sensor) { return *this; }

    double SmartMotor::get() { return m_cmd; }
    double SmartMotor::getOutput() { return m_output; }
    double Jath::SmartMotor::getFeedback() { return m_feedback; }

    void SmartMotor::set(double cmd)
    {
        m_pid.reset();
        m_cmd = cmd;
    }
    void SmartMotor::operator=(double cmd)
    {
        m_pid.reset();
        m_cmd = cmd;
    }

    void SmartMotor::update()
    {
        double turnError = 0;
        Angle value;

        switch (m_controlMode)
        {
        case DUTY_CYCLE:
            m_feedback = m_cmd;
            m_output = m_cmd * 12 / 100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
        case POSITION:
            if (m_sensor)
            {
                value = m_sensor->getPosition();
            }
            else
            {
                value = Degrees(position(vex::degrees));
            }
            m_feedback = value;
            m_output = m_pid.calculate(m_cmd, value) * 12 / 100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
        case ANGLE:
            if (m_sensor)
            {
                value = m_sensor->getAngle();
                turnError = m_cmd - value;
                if (m_sensor->getType() != Sensor::Type::Pot && m_sensor->getType() != Sensor::Type::PotV2)
                {
                    turnError = shortestTurnPath(turnError);
                }
            }
            else
            {
                value = Degrees(position(vex::degrees));
                turnError = shortestTurnPath(m_cmd - value);
            }

            m_feedback = turnError;
            m_output = m_pid.calculate(turnError) * 12 / 100.f;

            spin(vex::fwd, m_output, vex::volt);
            break;
        case VELOCITY:
            if (m_sensor)
            {
                value = Revolutions( m_sensor->getVelocity() / 60.f );
            }
            else
            {
                value = Revolutions( velocity(vex::rpm) / 60.f );
            }
            m_feedback = value;
            m_output += m_pid.calculate(m_cmd, value) * 12 / 100.f;

            if(m_output > 12){ m_output = 12;}
            if(m_output < -12){ m_output = -12;}

            spin(vex::fwd, m_output, vex::volt);
            break;
        case FOLLOWER:
            if (m_leaderMotor)
            {
                m_cmd = m_leaderMotor->getOutput();
            }
            m_feedback = m_cmd;
            m_output = m_cmd;
            spin(vex::fwd, m_output, vex::volt);
            break;
        case DISABLED:
            break;
        }
    }

    bool SmartMotor::isCompleted() { return m_pid.isCompleted(); }

    SmartMotor &SmartMotor::getMotor(std::string name)
    {
        static SmartMotor invalidMotor("noMotorFound", vex::PORT21);

        SmartMotor *out = nullptr;

        for (size_t i = 0; i < m_allMotors.size(); i++)
        {
            if (m_allMotors[i]->getName() == name)
            {
                out = m_allMotors[i];
            }
        }

        if (out)
        {
            return *out;
        }
        return invalidMotor;
    }

    void SmartMotor::updateAllMotors()
    {
        for (size_t i = 0; i < m_allMotors.size(); i++)
        {
            m_allMotors[i]->update();
        }
    }

    int updateMotorLoop()
    {
        for (;;)
        {
            SmartMotor::updateAllMotors();
            vex::wait(20,vex::msec);
        }
        return 1; 
    }

}
