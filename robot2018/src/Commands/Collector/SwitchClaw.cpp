#include "SwitchClaw.h"

SwitchClaw::SwitchClaw(Collector::CLAWMODE mode) : m_mode(mode) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void SwitchClaw::Initialize() {
	Collector::GetInstance().SwitchClaw(m_mode);
}

// Called repeatedly when this Command is scheduled to run
void SwitchClaw::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SwitchClaw::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SwitchClaw::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwitchClaw::Interrupted() {

}
