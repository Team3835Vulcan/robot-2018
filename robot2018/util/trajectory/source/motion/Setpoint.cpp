#include <motion/Setpoint.h>

Setpoint::Setpoint(double pos, double time, double velocity, double acceleration) :
	m_pos(pos), m_time(time), m_velocity(velocity), m_acceleration(acceleration) {}

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