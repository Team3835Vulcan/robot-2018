#include "ElevCtrl.h"
#include <Subsystems/Elevator/Elevator.h>

ElevCtrl::ElevCtrl(double val) : m_val(val) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Elevator::GetInstance());
}

// Called just before this Command runs the first time
void ElevCtrl::Initialize() {
	Elevator::GetInstance().Set(m_val);
}

// Called repeatedly when this Command is scheduled to run
void ElevCtrl::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ElevCtrl::IsFinished() {
	if(m_val > 0)
		return Elevator::GetInstance().IsUp();
	else
		return Elevator::GetInstance().IsDown();
}

// Called once after isFinished returns true
void ElevCtrl::End() {
	Elevator::GetInstance.Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevCtrl::Interrupted() {
	Elevator::GetInstance.Set(0);
}
