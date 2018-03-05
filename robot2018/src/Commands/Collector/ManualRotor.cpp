#include "ManualRotor.h"
#include <Subsystems/Collector/Collector.h>
#include <OI.h>
#include <iostream>
#include <cmath>

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
	double val = OI::GetInstance().GetOPRY();
	if(val > 0.35)
		val = 0.35;
	else if(val < -0.8)
		val = -0.8;
	std::cout << val << '\n';
	Collector::GetInstance().Rotate(val);
}

// Make this return true when this Command no longer needs to run execute()
bool ManualRotor::IsFinished() {
	return false;
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
