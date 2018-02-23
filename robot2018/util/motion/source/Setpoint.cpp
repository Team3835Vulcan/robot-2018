#include "../Setpoint.h"



Setpoint::Setpoint(float time, float dist, float velocity, float acceleration) :
	m_time(time), m_pos(dist), m_velocity(velocity), m_acceleration(acceleration) {}

Setpoint::Setpoint(float time, float dist, float velocity) :
	m_time(time), m_pos(dist), m_velocity(velocity), m_acceleration(0) {}

Setpoint::Setpoint(float dist) :
	m_time(0), m_pos(dist), m_velocity(0), m_acceleration(0) {}

const float Setpoint::GetTime() const{
	return m_time;
}

const float Setpoint::GetPos() const{
	return m_pos;
}

const float Setpoint::GetVelocity() const{
	return m_velocity;
}

const float Setpoint::GetAcceleration() const {
	return m_acceleration;
}
