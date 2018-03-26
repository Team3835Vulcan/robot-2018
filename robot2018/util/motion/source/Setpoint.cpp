#include "../Setpoint.h"



Setpoint::Setpoint(double time, double dist, double velocity, double acceleration) :
	m_time(time), m_pos(dist), m_velocity(velocity), m_acceleration(acceleration) {}

Setpoint::Setpoint(double time, double dist, double velocity) :
	m_time(time), m_pos(dist), m_velocity(velocity), m_acceleration(0) {}

Setpoint::Setpoint(double dist) :
	m_time(0), m_pos(dist), m_velocity(0), m_acceleration(0) {}

const double Setpoint::GetTime() const{
	return m_time;
}

const double Setpoint::GetPos() const{
	return m_pos;
}

const double Setpoint::GetVelocity() const{
	return m_velocity;
}

const double Setpoint::GetAcceleration() const {
	return m_acceleration;
}
