#include "SmartMotor.h"

std::map<SmartMotor::ControlMode, std::string> SmartMotor::ModeToString{
        {SmartMotor::ControlMode::DutyCycle, "DutyCycle"},
        {SmartMotor::ControlMode::Position, "Position"},
        {SmartMotor::ControlMode::Angle, "Angle"},
        {SmartMotor::ControlMode::Velocity, "Velocity"},
        {SmartMotor::ControlMode::Follower, "Follower"},
        {SmartMotor::ControlMode::Disabled, "Disabled"},
    };

std::vector< SmartMotor* > SmartMotor::m_allMotors;

SmartMotor::SmartMotor(std::string name, vex::motor mot) : vex::motor(mot), m_name(name), m_log(name)
{
  m_log.addLogItemD("time", [this]{ return Jath::timePassed(); });
  m_log.addLogItemS("cmdType", [this]{return ModeToString[getControlMode()]; });
  m_log.addLogItemD("cmd", [this]{return get(); });
  m_log.addLogItemD("kp", [this]{return m_pid.getkp(); });
  m_log.addLogItemD("ki", [this]{return m_pid.getki(); });
  m_log.addLogItemD("kd", [this]{return m_pid.getkd(); });
  m_log.addLogItemD("velocity", [this]{ return velocity(vex::rpm); });
  m_log.addLogItemD("torque", [this]{ return torque(); });
  m_log.addLogItemD("temprature", [this]{return temperature(); });
  m_log.addLogItemD("output%", [this]{return getOutput()*100/12.f; });
  m_log.addLogItemD("pos", [this]{ return position(vex::degrees); }); 
  if(Brain.SDcard.isInserted()){
    m_log.logHeader();
  }
  m_allMotors.push_back(this);
}

// SmartMotor::SmartMotor(SmartMotor & motor)
//  : vex::motor(motor)
//  , m_name(motor.m_name)
//  , m_controlMode(motor.m_controlMode)
//  , m_pid(motor.m_pid)
//  , m_leaderMotor(motor.m_leaderMotor)
//  , m_followingMotors(motor.m_followingMotors)
//  , m_sensor(motor.m_sensor)
// {
//   m_allMotors.push_back(this);
// }

SmartMotor::~SmartMotor()
{
  for(int i = 0; i < m_allMotors.size(); i++){
      if(m_allMotors[i] == this){
          m_allMotors.erase(m_allMotors.begin() + i);
      }
  }
}

void SmartMotor::setConstants(double kp, double ki, double kd) { m_pid.setConstants(kp, ki, kd); }
void SmartMotor::setConstants(double kp, double ki, double kd, double ff) { m_pid.setConstants(kp, ki, kd, ff); }

SmartMotor & SmartMotor::withConstants(double kp, double ki, double kd) { m_pid.setConstants(kp, ki, kd); return *this; }
SmartMotor & SmartMotor::withConstants(double kp, double ki, double kd, double ff) { m_pid.setConstants(kp, ki, kd, ff); return *this; }

void SmartMotor::setControlMode(SmartMotor::ControlMode mode) { m_controlMode = mode; }
SmartMotor& SmartMotor::withControlMode(SmartMotor::ControlMode mode) { m_controlMode = mode; return *this; }

SmartMotor::ControlMode SmartMotor::getControlMode(){ return m_controlMode; }
std::string SmartMotor::getControlModeString(){ return ModeToString[ m_controlMode ]; }

void SmartMotor::setLeader(SmartMotor * leader) { m_leaderMotor = leader; }
SmartMotor & SmartMotor::withLeader(SmartMotor * leader) { m_leaderMotor = leader; return *this; }

void SmartMotor::addFollower(vex::motor mot) { 
    int count = m_followingMotors.size() + 1;
    
    std::stringstream s;
    s << m_name << "follower " << count;

    std::shared_ptr <SmartMotor> temp = std::make_shared<SmartMotor> ( s.str(), mot );

    temp->setLeader( this );
    temp->setControlMode( Follower );

    m_followingMotors.push_back( temp );
}
SmartMotor& SmartMotor::withFollower(vex::motor mot) { addFollower(mot); return *this; }

void SmartMotor::setSensor(Sensor * sensor) { m_sensor = sensor; }
SmartMotor & SmartMotor::withSensor(Sensor * sensor) { m_sensor = sensor; return *this; }

double SmartMotor::get() { return m_cmd; }
SmartMotor::operator double() { return get(); }

double SmartMotor::getOutput() { return m_output; }

void SmartMotor::set(double cmd) { m_cmd = cmd; }
void SmartMotor::operator=(double cmd){ set(cmd); }

void SmartMotor::update()
{
    double turnError = 0;
    class Angle value;

        switch(m_controlMode){
          case DutyCycle:
            m_output = m_cmd * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Position:
            if(m_sensor){
              value = m_sensor->getPosition();
            }else {
              value = Degrees(position(vex::degrees) );
            }            
            m_output = m_pid.calculate(m_cmd, value) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Angle:
            if(m_sensor){
              value = m_sensor->getAngle();
              turnError = m_cmd - value;
              if(m_sensor->getType() != Sensor::Type::Pot && m_sensor->getType() != Sensor::Type::PotV2){
                turnError = shortestTurnPath(turnError);
              }
            }else {
              value = Degrees( position(vex::degrees) );
              turnError = shortestTurnPath(m_cmd - value);
            }

            m_output = m_pid.calculate(turnError) * 12/100.f;

            spin(vex::fwd, m_output, vex::volt);
            break;
          case Velocity:
            if(m_sensor){
              value = m_sensor->getVelocity();
            }else {
              value = velocity(vex::rpm);
            }
              m_output += m_pid.calculate(m_cmd, value) * 12/100.f;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Follower:
            if(m_leaderMotor){
              m_cmd = m_leaderMotor->voltage();
            }
            m_output = m_cmd;
            spin(vex::fwd, m_output, vex::volt);
            break;
          case Disabled:
            break;
        }
  if(Brain.SDcard.isInserted()){
    m_log.log();
  }
}

bool SmartMotor::isCompleted() { return m_pid.isCompleted(); }

