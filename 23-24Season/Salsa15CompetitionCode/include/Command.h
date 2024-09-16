#pragma once
#include <string>
#include <map>
#include <sstream>
#include <memory>

enum CommandCode{
    INVALID_COMMAND,
    SIGNAL_ONE,
    SIGNAL_TWO,
    SIGNAL_THREE,
    SIGNAL_FOUR,
    SIGNAL_FIVE,
    DRIVE_TO,
    TURN_TO,
    INTAKE_SET
};

inline std::map <std::string, CommandCode> commandToCode = {
    {"SIGNAL_ONE", SIGNAL_ONE},
    {"SIGNAL_TWO", SIGNAL_TWO},
    {"SIGNAL_THREE", SIGNAL_THREE},
    {"SIGNAL_FOUR", SIGNAL_FOUR},
    {"SIGNAL_FIVE", SIGNAL_FIVE},
    {"DRIVE_TO", DRIVE_TO},
    {"TURN_TO", TURN_TO},
    {"INTAKE_SET", INTAKE_SET},
};
inline std::map <CommandCode, std::string> codeToCommand = {
    {SIGNAL_ONE, "SIGNAL_ONE"},
    {SIGNAL_TWO, "SIGNAL_TWO"},
    {SIGNAL_THREE, "SIGNAL_THREE"},
    {SIGNAL_FOUR, "SIGNAL_FOUR"},
    {SIGNAL_FIVE, "SIGNAL_FIVE"},
    {DRIVE_TO, "DRIVE_TO"},
    {TURN_TO, "TURN_TO"},
    {INTAKE_SET, "INTAKE_SET"},
};

class Command{
    // std::string m_commandName;
    CommandCode m_code;
public:
    Command(CommandCode code): m_code(code){}

    virtual void run() = 0;
    CommandCode getCommandCode(){return m_code; };
    
    virtual std::string send() = 0;
    virtual void recieve(std::istringstream& stream) = 0;
};

class InvalidCommand : public Command{
public:
    InvalidCommand() : Command(INVALID_COMMAND) {}
    void run() override;
    
    virtual std::string send() override{
        std::stringstream stream;
        stream << codeToCommand[getCommandCode()] << " ";
        return stream.str();
    };
    void recieve(std::istringstream& stream) override{}
};

class SignalCommand : public Command{
public:
    SignalCommand(CommandCode c) : Command(c) {}
    void run() override;
    
    virtual std::string send() override{
        std::stringstream stream;
        stream << codeToCommand[getCommandCode()] << " ";
        return stream.str();
    };
    void recieve(std::istringstream& stream) override{}
};

class DriveToCommand : public Command{
    double m_distance{0};
public:
    DriveToCommand() : Command(DRIVE_TO) {}
    DriveToCommand(double distance) : Command(DRIVE_TO), m_distance(distance) {}
    void run() override;
    
    virtual std::string send() override{
        std::stringstream stream;
        stream << codeToCommand[getCommandCode()] << " ";
        stream << m_distance << " ";
        return stream.str();
    };
    void recieve(std::istringstream& stream) override{
        stream >> m_distance;
    };
};
class TurnToCommand : public Command{
    double m_angle{0};
public:
    TurnToCommand() : Command(TURN_TO) {}
    TurnToCommand(double angle) : Command(TURN_TO), m_angle(angle) {}
    void run() override;
    
    virtual std::string send() override{
        std::stringstream stream;
        stream << codeToCommand[getCommandCode()] << " ";
        stream << m_angle << " ";
        return stream.str();
    };
    void recieve(std::istringstream& stream) override{
        stream >> m_angle;
    };
};

class IntakeSetCommand : public Command{
    double m_speed{0};
public:
    IntakeSetCommand() : Command(INTAKE_SET) {}
    IntakeSetCommand(double speed) : Command(INTAKE_SET), m_speed(speed) {}
    void run() override;
    
    virtual std::string send() override{
        std::stringstream stream;
        stream << codeToCommand[getCommandCode()] << " ";
        stream << m_speed << " ";
        return stream.str();
    };
    void recieve(std::istringstream& stream) override{
        stream >> m_speed;
    };
};

std::shared_ptr<Command> recieveCommand(std::string& str);