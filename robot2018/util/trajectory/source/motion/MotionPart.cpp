#include <motion/MotionPart.h>
#include <cmath>

MotionPart::MotionPart(const Setpoint& start, const Setpoint& end, double dt, bool reversed) :
	m_start(start), 
	m_end(end),
	m_distance(m_end.GetPos() - m_start.GetPos()), 
	m_time(m_end.GetTime() - m_start.GetTime()),
	m_acc((m_end.GetVelocity() - m_start.GetVelocity()) / m_time), 
	m_dt(dt),
	m_reversed(reversed){}

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

const Setpoint MotionPart::FindSetpointT(double t) const {
	if (ContainsTime(t)) {
		double dt = t - m_start.GetTime();
		double pos = m_start.GetPos() + (m_acc * dt * dt / 2) + m_start.GetVelocity() * dt;
		double velocity = m_start.GetVelocity() + (m_acc * dt);
		double acc = m_acc;

		if (m_reversed) {
			pos = m_end.GetPos() - pos;
			velocity *= -1;
			acc *= -1;
		}

		return{ pos, t, velocity, acc };
	}
	return{ 0,0,0,0 };
}
const Setpoint MotionPart::FindSetpointD(double d) const {
	if (ContainsPos(d)) {
		double deltaX = d - m_start.GetPos();
		double veli2 = m_start.GetVelocity() * m_start.GetVelocity(); //vi^2
		double vel = std::sqrt(deltaX * m_acc * 2 + veli2);
		double t = 2 * deltaX / (m_start.GetVelocity() + vel) + m_start.GetTime();
		double acc = m_acc;
		
		if (m_reversed) {
			vel *= -1;
			acc *= -1;
		}

		return {d, t, vel, acc};
	}
	return{ 0,0,0,0 };
}
