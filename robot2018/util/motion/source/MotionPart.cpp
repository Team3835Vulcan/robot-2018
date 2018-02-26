#include "../MotionPart.h"
#include <cmath>

MotionPart::MotionPart(const Setpoint& start, const Setpoint& end) : m_start(start), m_end(end), 
m_distance(m_end.GetPos() - m_start.GetPos()), m_time(m_end.GetTime() - m_start.GetTime()), 
m_acc((m_end.GetVelocity() - m_start.GetVelocity()) / m_time), m_dt(1e-3){
}

MotionPart::MotionPart(const Setpoint& start, const Setpoint& end, float dt) : m_start(start), m_end(end),
m_distance(m_end.GetPos() - m_start.GetPos()), m_time(m_end.GetTime() - m_start.GetTime()),
m_acc((m_end.GetVelocity() - m_start.GetVelocity()) / m_time), m_dt(dt){
}

const bool MotionPart::IsValid() const {
	return m_time >= 0;
}

const bool MotionPart::ContainsTime(double t) const {
	return t >= m_start.GetTime() && t <= m_end.GetTime();
}

const bool MotionPart::ContainsPos(double pos) const {
	if (m_distance < 0)
		return pos >= m_end.GetPos() && pos <= m_start.GetPos();
	return pos >= m_start.GetPos() && pos <= m_end.GetPos();
}

const Setpoint& MotionPart::GetStart() const {
	return m_start;
}

const Setpoint& MotionPart::GetEnd() const {
	return m_end;
}

std::unique_ptr<Setpoint> MotionPart::FindSetpointT(double t) const {
	if (ContainsTime(t)) {
		float dt = t - m_start.GetTime();
		float pos = m_start.GetPos() + (m_acc * dt * dt / 2) + m_start.GetVelocity() * dt;
		float velocity = m_start.GetVelocity() + (m_acc * dt);
		return std::make_unique<Setpoint>(t, pos, velocity, m_acc);
	}
	return nullptr;
}
std::unique_ptr<Setpoint> MotionPart::FindSetpointD(double d) const {
	if (ContainsPos(d)) {
		float deltaX = d - m_start.GetPos();
		float veli2 = m_start.GetVelocity() * m_start.GetVelocity(); //vi^2
		float vel = sqrtf(deltaX * m_acc * 2 + veli2);
		float t = 2 * deltaX / (m_start.GetVelocity() + vel) + m_start.GetTime();
		return std::make_unique<Setpoint>(t, d, vel, m_acc);
	}
	return nullptr;
}
