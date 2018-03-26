#include "Conveyor.h"
#include <Constants.h>

Conveyor::Conveyor() : frc::Subsystem("Conveyor"),
   m_engine(CONV_MOTOR){}


Conveyor& Conveyor::GetInstance(){
	static Conveyor instance;
	return instance;
}

void Conveyor::Eject(SIDE s){
	if(s == LEFT){
		m_engine.Set(1);
	}
	else{
		m_engine.Set(-1);
	}
}

void Conveyor::Stop(){
	m_engine.Set(0);
}

