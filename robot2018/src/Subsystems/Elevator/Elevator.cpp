#include "Elevator.h"
#include <Constants.h>

Elevator::Elevator() : Subsystem("Elevator"), m_eng1(ELEV1_MOTOR),
					   m_eng2(ELEV2_MOTOR), m_elevUp(ELEV_UP_SWITCH),
					   m_elevDown(ELEV_DOWN_SWITCH){}

Elevator& Elevator::GetInstance(){
	static Elevator instance;
	return instance;
}

void Elevator::Set(double val){
	m_eng1->Set(val);
	m_eng2->Set(val);
}

bool Elevator::IsUp(){
	return !m_elevUp->Get();
}

bool Elevator::IsDown(){
	return !m_elevDown->Get();
}
