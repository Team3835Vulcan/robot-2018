#include "../include/MotionProfile.h"

MotionProfile::MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config) :
	m_start(start), m_end(end), m_config(config) {
}

const std::vector<MotionPart>& MotionProfile::GetParts() const {
	return m_parts;
}

const Setpoint& MotionProfile::GetStart() const {
	return m_start;
}

const Setpoint& MotionProfile::GetEnd() const {
	return m_end;
}


/*
while reading this function take note that time variables represent a coordinate and not the time to complete an action, which is called an interval.
*/
void MotionProfile::Generate() {
	float distCovered = 0;
	float goalDist = m_end.GetPos() - m_start.GetPos();
	float goalTime = m_end.GetTime() - m_start.GetTime();
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
	m_parts.push_back(MotionPart(m_start, toCruise));

	//triangular profile
	if (cruiseDist == 0) {	
		float endTime = timeToCruise + decelInterval;
		float endPos = accelPos + decelDist;

		Setpoint end(endTime, endPos, m_end.GetVelocity());
		m_parts.push_back(MotionPart(toCruise, end));
		
	}
	//trapezoidal
	else {
		float cruiseInterval = cruiseDist / cruiseVel;
		float cruiseTime = cruiseInterval + timeToCruise; 
		float endCruisePos = cruiseDist + accelPos;
		Setpoint cruiseEnd(cruiseTime, endCruisePos, cruiseVel);
		m_parts.push_back(MotionPart(toCruise, cruiseEnd));

		float endTime = cruiseTime + decelInterval;
		float endPos = endCruisePos + decelDist;

		Setpoint end(endTime, endPos, m_end.GetVelocity());
		m_parts.push_back(MotionPart(cruiseEnd, end));
		
	}
}




