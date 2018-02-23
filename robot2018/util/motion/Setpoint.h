#pragma once
class Setpoint
{
private:
	const float m_time;
	const float m_pos;
	const float m_velocity;
	const float m_acceleration;
public:
	Setpoint(float time, float pos, float velocity, float acceleration);
	Setpoint(float time, float pos, float velocity);
	Setpoint(float pos);
	const float GetTime() const;
	const float GetPos() const;
	const float GetVelocity() const;
	const float GetAcceleration() const;
};

