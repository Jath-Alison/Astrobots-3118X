#include "SubAutons.h"
#include <iostream>

void arcade(double drive, double rot)
{
    LeftMotors = drive + rot;
    RightMotors = drive - rot;

    jwb::SmartMotor::updateAllMotors();
}

void arcadeFor(double drive, double rot, double time)
{
    arcade(drive, rot);
    vex::wait(time, vex::seconds);
    arcade(0, 0);    
}

void driveTo(jwb::Distance target)
{
    jwb::RelativeUnit leftTravel ( []() { return jwb::Degrees(LeftMotors.position(vex::degrees)); }, jwb::Degrees(LeftMotors.position(vex::degrees)) );
    jwb::RelativeUnit rightTravel ( []() { return jwb::Degrees(RightMotors.position(vex::degrees)); }, jwb::Degrees(RightMotors.position(vex::degrees)) );

    jwb::PID pid = jwb::PID()
    .withConstants(30, 0.01, 20)
    .withIntegralZone(jwb::Degrees(45))
    .withTimeout( log( 2*target.inches() + 1 ) * 5 )
    .withSettleZone(jwb::Degrees( 10) )
    .withSettleTimeout(0.5);

    jwb::Angle targetAngle = jwb::Degrees( target.inches() / (3.14159 * 3.25) * (48.f/72.f) * 360);

    std::cout << "------target: " << targetAngle.degrees() << "\n";
    std::cout << "1: " << target.inches() << "\n";
    std::cout << "2: " << target.inches() / (3.14159 * 3.25) << "\n";
    std::cout << "3: " << target.inches() / (3.14159 * 3.25) * (72.f/48.f) << "\n";
    std::cout << "4: " << target.inches() / (3.14159 * 3.25) * (72.f/48.f) * 360 << "\n\n";
    // std::cout << "timePassed:" << pid.timePassed() << "\n";
    // std::cout << "settledTimePassed:" << pid.settledTimePassed() << "\n" << std::endl;

    while( !pid.isCompleted() ){
        double avg = (leftTravel + rightTravel) * 0.5;
        double temp = pid.calculate(targetAngle, avg);
        
        std::cout << "complete:" << pid.isCompleted() << "\n\t";
        std::cout << "left" << leftTravel << "\n\t";
        std::cout << "right" << rightTravel << "\n";
        std::cout << "error:" << jwb::Angle(targetAngle - avg).degrees() << "\n";
        std::cout << "output:" << temp << "\n";
        std::cout << "timePassed:" << pid.timePassed() << "\n\t";
        std::cout << "error:" << pid.m_error * pid.m_kp << "\n\t";
        std::cout << "deriv:" << pid.m_derivative * pid.m_kd << "\n\t";
        std::cout << "integ:" << pid.m_integral * pid.m_ki << "\n";
        std::cout << "settledTimePassed:" << pid.settledTimePassed() << "\n" << std::endl;


        arcade(temp, 0);

        vex::wait(20, vex::msec);
    }
}

void turnTo(jwb::Angle target)
{
    jwb::RelativeUnit rotTravel ( []() { return jwb::Degrees(inert.heading(vex::degrees)); }, 0); // jwb::Degrees(inert.heading(vex::degrees)) );

    jwb::PID pid = jwb::PID()
    .withConstants(50, 5, 50)
    .withIntegralZone(jwb::Degrees(15))
    .withTimeout( log( 5*target.revolutions() + 1 ) * 5 )
    .withSettleZone(jwb::Degrees( 3 ) )
    .withSettleTimeout(0.5);

    std::cout << "------target: " << target.degrees() << "\n";
    // std::cout << "timePassed:" << pid.timePassed() << "\n";
    // std::cout << "settledTimePassed:" << pid.settledTimePassed() << "\n" << std::endl;

    while( !pid.isCompleted() ){

        double error = jwb::shortestTurnPath(jwb::Angle(target - rotTravel));
        double temp = pid.calculate(error);
        
        std::cout << "complete:" << pid.isCompleted() << "\n\t";
        std::cout << "rotTravel" << rotTravel << "\n\t";
        std::cout << "error:" << jwb::Angle(target - rotTravel).degrees() << "\n";
        std::cout << "output:" << temp << "\n";
        std::cout << "timePassed:" << pid.timePassed() << "\n\t";
        std::cout << "error:" << pid.m_error * pid.m_kp << "\n\t";
        std::cout << "deriv:" << pid.m_derivative * pid.m_kd << "\n\t";
        std::cout << "integ:" << pid.m_integral * pid.m_ki << "\n";
        std::cout << "settledTimePassed:" << pid.settledTimePassed() << "\n" << std::endl;


        arcade(0, temp);

        vex::wait(20, vex::msec);
    }
}
