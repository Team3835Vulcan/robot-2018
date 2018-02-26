#include "DriveStraight.h"
#include "DrivePath.h"
#include <Commands/Scheduler.h>

DriveStraight::DriveStraight(double dist) : m_dist(dist) {
	// Use Requires() here to declare subsystem dependencies
	//Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
	Path p({{0,0}, {0,m_dist}});
	GenerateCatmullRom(p);
	Trajectory t(DEFAULT_CONFIG, p);
	frc::Scheduler::GetInstance()->AddCommand(new DrivePath(t));
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void DriveStraight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {

}
