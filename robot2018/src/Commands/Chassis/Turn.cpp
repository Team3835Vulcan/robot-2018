#include "Turn.h"
#include <Subsystems/Chassis/Chassis.h>
#include <cmath>

Turn::Turn(double angle) : m_angle(angle), m_controller(0,0,0),
	m_timeout(angle/45.0) {
	// Use Requires() here to declare subsystem dependencies
	m_controller.SetPID(0.025,0,0.0015);
	m_controller.SetInputRange(0,360);
	m_controller.SetOutputRange(-1,1);
	m_controller.SetTolerance(1);
	Requires(&Chassis::GetInstance());

}

// Called just before this Command runs the first time
void Turn::Initialize() {
	t.Reset();
	m_controller.Reset();
	m_controller.SetSetpoint(std::fmod(
			Chassis::GetInstance().GetAngle() + m_angle, 360.0));
	m_controller.Enable();
	t.Start();
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	m_controller.Calculate(Chassis::GetInstance().GetAngle());
	double output = -m_controller.GetOutput();
	Chassis::GetInstance().TankDrive(output, -output);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	return m_controller.IsOnTarget() || t.Get() >= m_timeout;
}

// Called once after isFinished returns true
void Turn::End() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0, 0);
	t.Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0, 0);
	t.Stop();
}
