#include "Collector.h"
#include <Constants.h>
#include <SmartDashboard/SmartDashboard.h>

Collector::Collector() : Subsystem("Collector"),
	m_rCollector(COLL1_MOTOR),
	m_lCollector(COLL2_MOTOR),
	m_collectSwitch(CUBE_SWITCH),
	m_rotor(ROTOR_MOTOR),
	m_downSwitch(DOWN_COLL_SWITCH),
	m_upSwitch(UP_COLL_SWITCH),
	m_potentiometer(0),
	m_claw(CLAW_FORWARD, CLAW_BACKWARD),
	ROTOR_VOLT_UP(m_potentiometer.GetAverageVoltage()),
	ROTOR_VOLT_DOWN(0.002441406){
		m_potentiometer.ResetAccumulator();
	}

Collector& Collector::GetInstance(){
	static Collector instance;
	return instance;
}

void Collector::InitDefaultCommand() {
}

void Collector::Periodic(){
	frc::SmartDashboard::PutBoolean("cube in", CubeIn());
	frc::SmartDashboard::PutBoolean("rotor down", IsDown());
	frc::SmartDashboard::PutBoolean("rotor up", IsUp());
	frc::SmartDashboard::PutNumber("rotor position",
			m_potentiometer.GetAverageVoltage());
	frc::SmartDashboard::PutNumber("rotor volt up", ROTOR_VOLT_UP);
	frc::SmartDashboard::PutNumber("rotor volt down", ROTOR_VOLT_DOWN);
}

void Collector::Collect(COLLECTMODE mode){
	if(mode == COLLECT){
		m_rCollector.Set(-1);
		m_lCollector.Set(1);
	}
	else{
		m_rCollector.Set(1);
		m_lCollector.Set(-1);
	}
}
void Collector::StopCollect(){
	m_rCollector.Set(0);
	m_lCollector.Set(0);
}

void Collector::Rotate(double val){
	m_rotor.Set(val);
}
double Collector::GetRotorPos() const{
	return m_potentiometer.GetAverageVoltage();
}

bool Collector::IsUp(){
	return !m_upSwitch.Get();
}
bool Collector::IsDown(){
	return !m_downSwitch.Get();
}
bool Collector::CubeIn(){
	return !m_collectSwitch.Get();
}

void Collector::SwitchClaw(CLAWMODE mode){
	if(mode == CLAWMODE::CLOSE)
		m_claw.Set(frc::DoubleSolenoid::Value::kForward);
	else
		m_claw.Set(frc::DoubleSolenoid::Value::kReverse);
}

Collector::CLAWMODE Collector::GetClawMode() const{
	if(m_claw.Get() == frc::DoubleSolenoid::Value::kReverse)
		return CLAWMODE::OPEN;
	return CLAWMODE::CLOSE;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
