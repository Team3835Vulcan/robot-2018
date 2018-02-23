#include "Conveyor.h"
#include <Constants.h>

Conveyor::Conveyor() : Subsystem("Conveyor"),
					   m_engine(std::make_unique<Talon>(CONV_MOTOR)){}


Conveyor& Conveyor::GetInstance(){
	static Conveyor instance;
	return instance;
}

void Conveyor::Eject(SIDE s){
	if(s == LEFT){
		m_engine->Set(0.8);
	}
	else{
		m_engine->Set(-0.8);
	}
}

void Conveyor::Stop(){
	m_engine->Set(0);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
