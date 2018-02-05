/*
 * PIDController.cpp
 *
 *  Created on: 9 בינו׳ 2018
 *      Author: Coding Monkeys
 */

#include "PIDController.h"

namespace vulcan {

PIDController::PIDController(double p, double i, double d) :
m_p(p), m_i(i), m_d(d), m_f(0), m_setpoint(0), m_prevError(0),
m_error(0), m_totalError(0), m_tolerance(0), m_output(0), m_minInput(0), m_maxInput(0),
m_minOutput(0), m_maxOutput(0), m_prevTime(0), m_currTime(0), m_isEnabled(false)
{}

PIDController::PIDController(double p, double i, double d, double f) :
m_p(p), m_i(i), m_d(d), m_f(f), m_setpoint(0), m_prevError(0),
m_error(0), m_totalError(0), m_tolerance(0), m_output(0), m_minInput(0), m_maxInput(0),
m_minOutput(0), m_maxOutput(0), m_prevTime(0), m_currTime(0), m_isEnabled(false)
{}

double PIDController::Limit(double value, double min, double max){
	if(value < min)
		return min;
	else if(value > max)
		return max;
	return value;
}

double PIDController::GetP(){
	return m_p;
}

double PIDController::GetI(){
	return m_i;
}

double PIDController::GetD(){
	return m_d;
}

double PIDController::GetF(){
	return m_f;
}

void PIDController::SetP(double p){
	m_p = p;
}

void PIDController::SetI(double i){
	m_i = i;
}

void PIDController::SetD(double d){
	m_d = d;
}

void PIDController::SetPID(double p, double i,  double d){
	m_p = p;
	m_i = i;
	m_d = d;
}

void PIDController::SetF(double f){
	m_f = f;
}

void PIDController::SetInputRange(double min, double max){
	if(min > max){
		m_minInput = max;
		m_maxInput = min;
	}
	else{
		m_minInput = min;
		m_maxInput = max;
	}
}

void PIDController::SetOutputRange(double min, double max){
	if(min > max){
		m_minOutput = max;
		m_maxOutput = min;
	}
	else{
		m_minOutput = min;
		m_maxOutput = max;
	}
}

void PIDController::SetTolerance(double tolerance){
	m_tolerance = tolerance;
}

void PIDController::SetPercentTolerance(double percent){
	if(!(percent > 1 || percent < 0) && m_setpoint != 0)
		m_tolerance = percent * m_setpoint;
}

void PIDController::SetSetpoint(double setpoint){
	m_setpoint = setpoint;
}

void PIDController::SetRelativeSetpoint(double delta){
	m_setpoint += delta;
}

void PIDController::Calculate(double input){
	if(m_isEnabled){
		m_error = m_setpoint - input;
		m_currTime = frc::RobotController::GetFPGATime();
		double dt = m_currTime - m_prevTime;
		m_totalError += m_error * dt;
		double diffTerm = (m_error - m_prevError) / dt;

		m_prevError = m_error;
		m_prevTime = m_currTime;

		double output = m_p * m_error + m_i * m_totalError + m_d * diffTerm + m_f * m_setpoint;
		m_output = Limit(output, m_minOutput, m_maxOutput);
	}
}

double PIDController::GetOutput(){
	return m_output;
}

void PIDController::Enable(){
	m_isEnabled = true;
	m_prevTime = frc::RobotController::GetFPGATime();
}

void PIDController::Disable(){
	m_isEnabled = false;
}

void PIDController::Reset(){
	Disable();
	m_prevTime = 0;
	m_currTime = 0;
	m_setpoint = 0;
	m_totalError = 0;
	m_output = 0;
}

bool PIDController::IsOnTarget(){
	return m_error <= m_tolerance;
}

} /* namespace vulcan */
