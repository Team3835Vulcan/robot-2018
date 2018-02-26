#include "DriveStraight.h"
#include <iostream>

DriveStraight::DriveStraight(double dist) : m_dist(dist) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Chassis::GetInstance());
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
	Path p({{0,0}, {0,m_dist}});
	GenerateCatmullRom(p);
	Trajectory t(DEFAULT_CONFIG, std::move(p));
	m_controller.SetTrajectory(std::move(t));
	m_controller.Configure(0,0,VELOCITY_FEEDFORWARD,
				1, ACCELERATION_FEEDFORWARD, K_HEADING);
	Chassis::GetInstance().ResetEncoders();
	Chassis::GetInstance().ZeroYaw();
	m_controller.Reset();
	m_controller.Enable();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
	std::cout << "calculating\n";
	const DriveSignal signal = m_controller.Calculate();
	std::cout << "got signal";
	std::cout << signal.speed << '\n' << signal.curve << '\n';
	Chassis::GetInstance().CurveDrive(signal.speed, signal.curve);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() {
	return m_controller.IsOnTarget();
}

// Called once after isFinished returns true
void DriveStraight::End() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}
