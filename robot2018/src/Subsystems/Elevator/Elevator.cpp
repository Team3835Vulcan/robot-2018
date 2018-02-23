#include "Elevator.h"
#include <Constants.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Commands/Elevator/ManualElevator.h>

Elevator::Elevator() : Subsystem("Elevator"), m_eng1(std::make_unique<Talon>(ELEV1_MOTOR)),
					   m_eng2(std::make_unique<Talon>(ELEV2_MOTOR)),
					   m_elevUp(std::make_unique<frc::DigitalInput>(ELEV_UP_SWITCH)),
					   m_elevDown(std::make_unique<frc::DigitalInput>(ELEV_DOWN_SWITCH)){
//	m_eng2->SetInverted(true);
}

Elevator& Elevator::GetInstance(){
	static Elevator instance;
	return instance;
}

void Elevator::InitDefaultCommand(){
	SetDefaultCommand(new ManualElevator());
}

void Elevator::Periodic(){
	frc::SmartDashboard::PutNumber("elevator rate", (m_eng1->Get() + m_eng2->Get()) / 2);
	frc::SmartDashboard::PutBoolean("elev up", !m_elevUp->Get());
	frc::SmartDashboard::PutBoolean("elev down", !m_elevDown->Get());
}

void Elevator::Set(double val){
	m_eng1->Set(-val);
	m_eng2->Set(-val);
}

bool Elevator::IsUp(){
	return !m_elevUp->Get();
}

bool Elevator::IsDown(){
	return !m_elevDown->Get();
}
