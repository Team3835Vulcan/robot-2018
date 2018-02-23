#include "DrivePath.h"
#include <iostream>
#include <Constants.h>

DrivePath::DrivePath(const Trajectory& traj) :
	m_traj(traj){
	// Use Requires() here to declare subsystem dependencies
	Requires(&Chassis::GetInstance());
}

// Called just before this Command runs the first time
void DrivePath::Initialize() {
	m_controller.SetTrajectory(m_traj);
	m_controller.Configure(0,0,0,
			VELOCITY_FEEDFORWARD, ACCELERATION_FEEDFORWARD, K_HEADING);
	m_controller.Enable();
}

// Called repeatedly when this Command is scheduled to run
void DrivePath::Execute() {
	std::cout << "calculating\n";
	const DriveSignal signal = m_controller.Calculate();
	std::cout << "got signal";
	std::cout << signal.left << '\n' << signal.right << '\n';
	//Chassis::GetInstance().TankDrive(signal.left, signal.right);
}

// Make this return true when this Command no longer needs to run execute()
bool DrivePath::IsFinished() {
	return m_controller.IsOnTarget();
}

// Called once after isFinished returns true
void DrivePath::End() {
	Chassis::GetInstance().TankDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivePath::Interrupted() {
	Chassis::GetInstance().TankDrive(0,0);
}
