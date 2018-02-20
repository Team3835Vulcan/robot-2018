#include "Collect.h"
#include <Timer.h>

Collect::Collect(Collector::COLLECTMODE mode) : m_mode(mode){
	// Use Requires() here to declare subsystem dependencies
	Requires(&Collector::GetInstance());
}

// Called just before this Command runs the first time
void Collect::Initialize() {
	Collector::GetInstance().Collect(m_mode);
}

// Called repeatedly when this Command is scheduled to run
void Collect::Execute() {

}

bool Collect::IsFinished(){
	if(m_mode == Collector::COLLECTMODE::COLLECT)
		return false;
	else
		return true;
}

// Called once after isFinished returns true
void Collect::End() {
	Wait(1);
	Collector::GetInstance().StopCollect();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Collect::Interrupted() {
	Wait(1);
	Collector::GetInstance().StopCollect();
}
