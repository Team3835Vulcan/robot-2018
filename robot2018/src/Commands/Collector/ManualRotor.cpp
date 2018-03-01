#include "ManualRotor.h"
#include <Subsystems/Collector/Collector.h>
#include <OI.h>

ManualRotor::ManualRotor() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Collector::GetInstance());
}

// Called just before this Command runs the first time
void ManualRotor::Initialize() {
	Collector::GetInstance().manualRotor = true;
}

// Called repeatedly when this Command is scheduled to run
void ManualRotor::Execute() {
	Collector::GetInstance().Rotate(OI::GetInstance().GetOPLY());
}

// Make this return true when this Command no longer needs to run execute()
bool ManualRotor::IsFinished() {
	return !Collector::GetInstance().manualRotor;
}

// Called once after isFinished returns true
void ManualRotor::End() {
	Collector::GetInstance().manualRotor = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualRotor::Interrupted() {
	Collector::GetInstance().manualRotor = false;
}
