#include "SwitchClaw.h"
#include <Subsystems/Collector/Collector.h>

SwitchClaw::SwitchClaw() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void SwitchClaw::Initialize() {
	if(Collector::GetInstance().GetClawMode() == Collector::CLAWMODE::OPEN)
		Collector::GetInstance().SwitchClaw(Collector::CLAWMODE::CLOSE);
	else
		Collector::GetInstance().SwitchClaw(Collector::CLAWMODE::OPEN);
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
