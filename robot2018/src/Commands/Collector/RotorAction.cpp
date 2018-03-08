#include "RotorAction.h"
#include <Constants.h>
#include <iostream>

RotorAction::RotorAction(Collector::ROTOR_POS pos) : m_pos(pos),
	m_controller(std::make_unique<vulcan::PIDController>(0,0,0)){
	// Use Requires() here to declare subsystem dependencies
	Requires(&Collector::GetInstance());
}

// Called just before this Command runs the first time
void RotorAction::Initialize() {
	m_controller->Reset();
	if(Collector::GetInstance().manualRotor == false) {
		double up = Collector::GetInstance().ROTOR_VOLT_UP; //min
		double down = Collector::GetInstance().ROTOR_VOLT_DOWN; //max
		m_controller->SetInputRange(up, down);
		m_controller->SetOutputRange(-0.4,1);
		if(m_pos == Collector::ROTOR_POS::UP){
			m_controller->SetSetpoint(up);
			m_controller->SetPID(0.6,0,0.3);
		}
		else{
			m_controller->SetSetpoint(down);
			m_controller->SetPID(0.18,0,0.8);
		}
		m_controller->SetTolerance(0.05);
		m_controller->Enable();
	}
}

// Called repeatedly when this Command is scheduled to run
void RotorAction::Execute() {
	if(Collector::GetInstance().manualRotor == false){
		double pos = Collector::GetInstance().GetRotorPos();
		m_controller->Calculate(pos);
		double output = m_controller->GetOutput();
		std::cout << output << '\n';
		Collector::GetInstance().Rotate(-output);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RotorAction::IsFinished() {
	if(Collector::GetInstance().manualRotor)
		return true;
	else{
		if(m_controller->IsOnTarget())
			return true;
		else{
			if(m_pos == Collector::ROTOR_POS::UP)
				return Collector::GetInstance().IsUp();
			else
				return Collector::GetInstance().IsDown();
		}
	}
}

// Called once after isFinished returns true
void RotorAction::End() {
	Collector::GetInstance().Rotate(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RotorAction::Interrupted() {
	Collector::GetInstance().Rotate(0);
}
