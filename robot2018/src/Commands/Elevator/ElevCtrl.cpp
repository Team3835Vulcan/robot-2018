#include "ElevCtrl.h"
#include <Subsystems/Elevator/Elevator.h>
#include <iostream>
#include <SmartDashboard/SmartDashboard.h>

ElevCtrl::ElevCtrl(ELEVPOS pos) : m_pos(pos) {
	// Use Requires() here to declare subsystem dependencies
	Requires(&Elevator::GetInstance());
}

// Called just before this Command runs the first time
void ElevCtrl::Initialize() {
	if(m_pos == ELEVPOS::UP)
		Elevator::GetInstance().Set(-1);
	else
		Elevator::GetInstance().Set(1);
}

// Called repeatedly when this Command is scheduled to run
void ElevCtrl::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool ElevCtrl::IsFinished() {
	if(m_pos == ELEVPOS::UP)
		return Elevator::GetInstance().IsUp();
	else
		return Elevator::GetInstance().IsDown();
}

// Called once after isFinished returns true
void ElevCtrl::End() {
	Elevator::GetInstance().Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevCtrl::Interrupted() {
	Elevator::GetInstance().Set(0);
}
