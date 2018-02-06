#include "RotorAction.h"
#include <Subsystems/Collector/Collector.h>

RotorAction::RotorAction(double val) : m_val(val) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Collector::GetInstance());
}

// Called just before this Command runs the first time
void RotorAction::Initialize() {
	Collector::GetInstance().Rotate(m_val);
}

// Called repeatedly when this Command is scheduled to run
void RotorAction::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool RotorAction::IsFinished() {
	if(m_val > 0)
		return Collector::GetInstance().IsUp();
	else
		return Collector::GetInstance().IsDown();
	//return Collector::GetInstance().IsDown();
}

// Called once after isFinished returns true
void RotorAction::End() {
	Collector::GetInstance().Rotate(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotorAction::Interrupted() {
	Collector::GetInstance().Rotate(0);
}
