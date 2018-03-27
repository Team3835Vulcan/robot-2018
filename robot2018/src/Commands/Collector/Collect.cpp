#include "Collect.h"
#include <Subsystems/Collector/Collector.h>
#include <OI.h>

Collect::Collect() {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Collector::GetInstance());
}

// Called just before this Command runs the first time
void Collect::Initialize() {
	Collector::GetInstance().Collect(Collector::COLLECTMODE::COLLECT);
	OI::GetInstance().RumbleXbox(0.7);
}

// Called repeatedly when this Command is scheduled to run
void Collect::Execute() {

}

bool Collect::IsFinished(){
	return false;
}

// Called once after isFinished returns true
void Collect::End() {
	Collector::GetInstance().StopCollect();
	OI::GetInstance().RumbleXbox(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Collect::Interrupted() {
	Collector::GetInstance().StopCollect();
	OI::GetInstance().RumbleXbox(0);
}
