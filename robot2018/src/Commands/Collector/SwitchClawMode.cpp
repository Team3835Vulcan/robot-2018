#include <Commands/Collector/SwitchClawMode.h>

SwitchClawMode::SwitchClawMode(Collector::CLAWMODE mode) : m_mode(mode) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void SwitchClawMode::Initialize() {
	Collector::GetInstance().SwitchClaw(m_mode);
}

// Called repeatedly when this Command is scheduled to run
void SwitchClawMode::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SwitchClawMode::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SwitchClawMode::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SwitchClawMode::Interrupted() {

}
