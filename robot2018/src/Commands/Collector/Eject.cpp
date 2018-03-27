#include "Eject.h"
#include <Subsystems/Collector/Collector.h>

Eject::Eject() : TimedCommand(1){
	// Use Requires() here to declare subsystem dependencies
	Requires(&Collector::GetInstance());
}

// Called just before this Command runs the first time
void Eject::Initialize() {
	Collector::GetInstance().Collect(Collector::COLLECTMODE::EJECT);
}

// Called repeatedly when this Command is scheduled to run
void Eject::Execute() {

}

// Called once after isFinished returns true
void Eject::End() {
	Collector::GetInstance().StopCollect();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Eject::Interrupted() {
	Collector::GetInstance().StopCollect();
}
