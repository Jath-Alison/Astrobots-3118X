#include "RobotConfig.h"
#include "Command.h"

void InvalidCommand::run(){}
void SignalCommand::run(){}
void DriveToCommand::run() {
    smartDrive.driveTo(m_distance);
}
void TurnToCommand::run() {
    smartDrive.turnTo(m_angle);
}
void IntakeSetCommand::run() {
    intake.set(m_speed);
}

std::shared_ptr<Command> recieveCommand(std::string& str){
    std::istringstream stream(str);

    std::string commandName;
    CommandCode commandCode;

    stream >> commandName;
    
    if(commandToCode.count(commandName) != 0){
        commandCode = commandToCode[commandName];
    }else{
        commandCode = INVALID_COMMAND;
    }

    switch (commandCode)
    {
    case INVALID_COMMAND:{
        std::shared_ptr<InvalidCommand> out = std::make_shared<InvalidCommand>();
        return out;
        break;
    }
    case SIGNAL_ONE:{
        std::shared_ptr<SignalCommand> out = std::make_shared<SignalCommand>(SIGNAL_ONE);
        return out;
        break;
    }
    case SIGNAL_TWO:{
        std::shared_ptr<SignalCommand> out = std::make_shared<SignalCommand>(SIGNAL_TWO);
        return out;
        break;
    }
    case SIGNAL_THREE:{
        std::shared_ptr<SignalCommand> out = std::make_shared<SignalCommand>(SIGNAL_THREE);
        return out;
        break;
    }
    case SIGNAL_FOUR:{
        std::shared_ptr<SignalCommand> out = std::make_shared<SignalCommand>(SIGNAL_FOUR);
        return out;
        break;
    }
    case SIGNAL_FIVE:{
        std::shared_ptr<SignalCommand> out = std::make_shared<SignalCommand>(SIGNAL_FIVE);
        return out;
        break;
    }
    case DRIVE_TO:{
        std::shared_ptr<DriveToCommand> out =  std::make_shared<DriveToCommand>();
        out->recieve(stream);
        return out;
        break;
    }
    case TURN_TO:{
        std::shared_ptr<TurnToCommand> out =  std::make_shared<TurnToCommand>();
        out->recieve(stream);
        return out;
        break;
    }
    case INTAKE_SET:{
        std::shared_ptr<IntakeSetCommand> out =  std::make_shared<IntakeSetCommand>();
        out->recieve(stream);
        return out;
        break;
    }
    default:{
        break;
    }
    }

    std::shared_ptr<InvalidCommand> out = std::make_shared<InvalidCommand>();
    return out;
}