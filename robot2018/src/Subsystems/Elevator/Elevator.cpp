#include "Elevator.h"
#include <Constants.h>

Elevator::Elevator() : Subsystem("Elevator"), m_eng1(std::make_unique<frc::Spark>(ELEV1_MOTOR)),
					   m_eng2(std::make_unique<frc::Spark>(ELEV2_MOTOR)),
					   m_elevUp(std::make_unique<frc::DigitalInput>(ELEV_UP_SWITCH)),
					   m_elevDown(std::make_unique<frc::DigitalInput>(ELEV_DOWN_SWITCH)){
	m_eng2->SetInverted(true);
}

Elevator& Elevator::GetInstance(){
	static Elevator instance;
	return instance;
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
