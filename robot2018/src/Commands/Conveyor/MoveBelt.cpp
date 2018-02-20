#include "MoveBelt.h"

MoveBelt::MoveBelt(Conveyor::SIDE s) : TimedCommand(1), m_side(s) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Conveyor::GetInstance());
}

// Called just before this Command runs the first time
void MoveBelt::Initialize() {
	Conveyor::GetInstance().Eject(m_side);
}

// Called repeatedly when this Command is scheduled to run
void MoveBelt::Execute() {

}

// Called once after isFinished returns true
void MoveBelt::End() {
	Conveyor::GetInstance().Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveBelt::Interrupted() {
	Conveyor::GetInstance().Stop();
}
