#include "Collect.h"
#include <Subsystems/Collector/Collector.h>
#include <Timer.h>

Collect::Collect(double val) : m_val(val){
	// Use Requires() here to declare subsystem dependencies
	Requires(&Collector::GetInstance());
}

// Called just before this Command runs the first time
void Collect::Initialize() {
	Collector::GetInstance().Collect(m_val);
}

// Called repeatedly when this Command is scheduled to run
void Collect::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool Collect::IsFinished() {
	if(m_val < 0)
		return Collector::GetInstance().CubeIn();
	else
		return true;
	//return false;
}

// Called once after isFinished returns true
void Collect::End() {
	Wait(1);
	Collector::GetInstance().Collect(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Collect::Interrupted() {
	Collector::GetInstance().Collect(0);
}
