#include "TurnAngle.h"
#include <Subsystems\Chassis\Chassis.h>

TurnAngle::TurnAngle(double angle) : m_angle(angle){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void TurnAngle::Initialize()
{
	Chassis::GetInstance()->ZeroYaw();
	m_turnController->SetPID(0, 0, 0);
	m_turnController->SetSetpoint(m_angle);
	m_turnController->SetTolerance(0.5);
	m_turnController->SetInputRange(-360, 360);
	m_turnController->SetOutputRange(-1, 1);
	m_turnController->Enable();
}

// Called repeatedly when this Command is scheduled to run
void TurnAngle::Execute() {
	m_turnController->Calculate(Chassis::GetInstance()->GetAngle());
	double engineParameter = m_turnController->GetOutput();
	Chassis::GetInstance()->TankDrive(engineParameter, -engineParameter);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnAngle::IsFinished() {
	return m_turnController->IsOnTarget();
}

// Called once after isFinished returns true
void TurnAngle::End() {
	Chassis::GetInstance()->TankDrive(0, 0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnAngle::Interrupted() {
	Chassis::GetInstance()->TankDrive(0, 0);

}
