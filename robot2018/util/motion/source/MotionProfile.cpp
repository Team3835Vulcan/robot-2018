#include "../MotionProfile.h"
#include <cmath>

MotionProfile::MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config) :
	m_config(config), m_start(start), m_end(end){
		Generate();
	}

const MotionProfileConfig& MotionProfile::GetConfig() const {
	return m_config;
}

const std::vector<MotionPart>& MotionProfile::GetParts() const {
	return m_parts;
}
void MotionProfile::AddPart(const MotionPart& part) {
	m_parts.emplace_back(part);
}

const Setpoint& MotionProfile::GetStart() const {
	return m_start;
}

const Setpoint& MotionProfile::GetEnd() const {
	return m_end;
}

std::unique_ptr<Setpoint> MotionProfile::GetSetpointT(double t) const {
	for (std::size_t i = 0; i < m_parts.size(); ++i) {
		auto s = m_parts.at(i).FindSetpointT(t);
		if (s)
			return s;
	}
	return nullptr;
}
std::unique_ptr<Setpoint> MotionProfile::GetSetpointD(double d) const {
	for (std::size_t i = 0; i < m_parts.size(); ++i) {
		auto s = m_parts.at(i).FindSetpointD(d);
		if (s)
			return s;
	}
	return nullptr;
}

/*
while reading this function take note that time variables represent a coordinate and not the time to complete an action, which is called an interval.
*/
void MotionProfile::Generate() {
	float goalDist = m_end.GetPos() - m_start.GetPos();
	float maxAcc = m_config.m_maxAcc;
	float decel = -maxAcc;
	float maxVel = sqrtf(goalDist*maxAcc);
	float cruiseVel = fmin(maxVel, m_config.m_maxVel);	
	float deltaVStart = cruiseVel - m_start.GetVelocity();
	float deltaVEnd = m_end.GetVelocity() - cruiseVel;
	float accelInterval = deltaVStart / maxAcc;
	float accelDist = (m_start.GetVelocity() + cruiseVel) * accelInterval / 2;
	float decelInterval = deltaVEnd / decel;
	float decelDist = (cruiseVel + m_end.GetVelocity()) * decelInterval / 2;
	float cruiseDist = goalDist - accelDist - decelDist;

	float timeToCruise = m_start.GetTime() + accelInterval;
	float accelPos = m_start.GetPos() + accelDist;

	Setpoint toCruise(timeToCruise, accelPos, cruiseVel);
	m_parts.push_back(MotionPart(m_start, toCruise, m_config.m_dt));

	//triangular profile
	if (cruiseDist == 0) {	
		float endTime = timeToCruise + decelInterval;
		float endPos = accelPos + decelDist;

		Setpoint end(endTime, endPos, m_end.GetVelocity());
		m_parts.push_back(MotionPart(toCruise, end, m_config.m_dt));
		
	}
	//trapezoidal
	else {
		float cruiseInterval = cruiseDist / cruiseVel;
		float cruiseTime = cruiseInterval + timeToCruise; 
		float endCruisePos = cruiseDist + accelPos;
		Setpoint cruiseEnd(cruiseTime, endCruisePos, cruiseVel);
		m_parts.push_back(MotionPart(toCruise, cruiseEnd, m_config.m_dt));

		float endTime = cruiseTime + decelInterval;
		float endPos = endCruisePos + decelDist;

		Setpoint end(endTime, endPos, m_end.GetVelocity());
		m_parts.push_back(MotionPart(cruiseEnd, end, m_config.m_dt));
	}
	m_time = m_parts.at(m_parts.size() - 1).GetEnd().GetTime() - m_start.GetTime();
	m_dist = fabs(m_parts.at(m_parts.size() - 1).GetEnd().GetPos() - m_start.GetPos());
}


const double MotionProfile::GetDist() const {
	return m_dist;
}

const double MotionProfile::GetTime() const {
	return m_time;
}



