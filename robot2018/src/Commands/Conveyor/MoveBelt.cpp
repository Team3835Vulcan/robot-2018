#include "MoveBelt.h"
#include <Subsystems/Conveyor/Conveyor.h>

MoveBelt::MoveBelt(double val) : m_val(val) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Conveyor::GetInstance());
}

// Called just before this Command runs the first time
void MoveBelt::Initialize() {
	Conveyor::GetInstance().Set(m_val);
}

// Called repeatedly when this Command is scheduled to run
void MoveBelt::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool MoveBelt::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveBelt::End() {
	Conveyor::GetInstance().Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveBelt::Interrupted() {
	Conveyor::GetInstance().Set(0);
}
