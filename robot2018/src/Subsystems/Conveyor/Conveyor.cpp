#include "Conveyor.h"
#include <Constants.h>

Conveyor::Conveyor() : Subsystem("Conveyor"),
					   m_engine(CONV_MOTOR){}


void Conveyor::Set(double val){
	m_engine->Set(val);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
