#include "DrivePath.h"
#include <iostream>
#include <Constants.h>

DrivePath::DrivePath(const Path& path, double headingf) :
	m_path(path), m_headingf(headingf){
	// Use Requires() here to declare subsystem dependencies
	std::cout << "copy ctor\n";
	m_controller.Configure(0,0,VELOCITY_FEEDFORWARD,
					0.7, ACCELERATION_FEEDFORWARD, 0.1);
	Requires(&Chassis::GetInstance());
}

DrivePath::DrivePath(const Path&& path, double headingf) :
	m_path(std::move(path)), m_headingf(headingf){
	// Use Requires() here to declare subsystem dependencies
	std::cout << "move ctor\n";
	m_controller.Configure(0,0,VELOCITY_FEEDFORWARD,
					0.7, ACCELERATION_FEEDFORWARD, 0.1);
	Requires(&Chassis::GetInstance());
}
// Called just before this Command runs the first time
void DrivePath::Initialize() {
	double heading0 = Chassis::GetInstance().GetAngle();
	if(m_headingf != 999)
		GenerateCatmullRom(m_path, heading0, m_headingf);
	else
		GenerateCatmullRom(m_path, heading0);
	Trajectory t(DEFAULT_CONFIG, std::move(m_path));
	m_controller.SetTrajectory(std::move(t));
	Chassis::GetInstance().ResetEncoders();
	m_controller.Reset();
	m_controller.Enable();
}

// Called repeatedly when this Command is scheduled to run
void DrivePath::Execute() {
	std::cout << "calculating\n";
	const DriveSignal signal = m_controller.Calculate();
	std::cout << "got signal";
	std::cout << signal.speed << '\n' << signal.curve << '\n';
	Chassis::GetInstance().CurveDrive(signal.speed, signal.curve);
}

// Make this return true when this Command no longer needs to run execute()
bool DrivePath::IsFinished() {
	return m_controller.IsOnTarget();
}

// Called once after isFinished returns true
void DrivePath::End() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivePath::Interrupted() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}
