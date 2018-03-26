#pragma once
class Setpoint {
private:
	double m_pos;
	double m_time;
	double m_velocity;
	double m_acceleration;
public:
	Setpoint(double pos, double time=0, double velocity=0, double acceleration=0);
	const double GetTime() const;
	const double GetPos() const;
	const double GetVelocity() const;
	const double GetAcceleration() const;
};