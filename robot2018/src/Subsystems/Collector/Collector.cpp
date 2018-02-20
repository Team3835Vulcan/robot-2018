#include "Collector.h"
#include <Constants.h>
#include <SmartDashboard/SmartDashboard.h>

Collector::Collector() : Subsystem("Collector"),
	m_rCollector(std::make_unique<WPI_VictorSPX>(COLL1_MOTOR)),
	m_lCollector(std::
			make_unique<WPI_VictorSPX>(COLL2_MOTOR)),
	m_collectSwitch(std::make_unique<frc::DigitalInput>(CUBE_SWITCH)),
	m_rotor(std::make_unique<WPI_VictorSPX>(ROTOR_MOTOR)),
	m_downSwitch(std::make_unique<frc::DigitalInput>(DOWN_COLL_SWITCH)),
	m_upSwitch(std::make_unique<frc::DigitalInput>(UP_COLL_SWITCH)),
	m_claw(std::make_unique<frc::DoubleSolenoid>(CLAW_FORWARD, CLAW_BACKWARD))
	{}

Collector& Collector::GetInstance(){
	static Collector instance;
	return instance;
}

void Collector::InitDefaultCommand() {
	// Set the default command for a subsystem here.
//	SetDefaultCommand(new ManualRotor());
}

void Collector::Periodic(){
	frc::SmartDashboard::PutBoolean("cube in", CubeIn());
	frc::SmartDashboard::PutBoolean("rotor down", IsDown());
	frc::SmartDashboard::PutBoolean("rotor up", IsUp());
}

void Collector::Collect(COLLECTMODE mode){
	if(mode == COLLECT){
		m_rCollector->Set(-1);
		m_lCollector->Set(1);
	}
	else{
		m_rCollector->Set(1);
		m_lCollector->Set(-1);
	}
}
void Collector::StopCollect(){
	m_rCollector->Set(0);
	m_lCollector->Set(0);
}

void Collector::Rotate(double val){
	m_rotor->Set(val);
}

bool Collector::IsUp(){
	return !m_upSwitch->Get();
}

bool Collector::IsDown(){
	return !m_downSwitch->Get();
}

bool Collector::CubeIn(){
	return !m_collectSwitch->Get();
}

void Collector::SwitchClaw(CLAWMODE mode){
	if(mode == CLAWMODE::CLOSE)
		m_claw->Set(frc::DoubleSolenoid::Value::kForward);
	else
		m_claw->Set(frc::DoubleSolenoid::Value::kReverse);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
