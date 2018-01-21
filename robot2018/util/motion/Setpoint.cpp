#include "../include/Setpoint.h"



Setpoint::Setpoint(float time, float dist, float velocity) :
	m_time(time), m_pos(dist), m_velocity(velocity) {}

const float Setpoint::GetTime() const{
	return m_time;
}

const float Setpoint::GetPos() const{
	return m_pos;
}

const float Setpoint::GetVelocity() const{
	return m_velocity;
}
