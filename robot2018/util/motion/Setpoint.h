#pragma once
class Setpoint
{
private:
	const double m_time;
	const double m_pos;
	const double m_velocity;
	const double m_acceleration;
public:
	Setpoint(double time, double pos, double velocity, double acceleration);
	Setpoint(double time, double pos, double velocity);
	Setpoint(double pos);
	const double GetTime() const;
	const double GetPos() const;
	const double GetVelocity() const;
	const double GetAcceleration() const;
};

