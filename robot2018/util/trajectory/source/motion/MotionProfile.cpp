#include <motion/MotionProfile.h>
#include <cmath>

MotionProfile::MotionProfile(const Setpoint& start, const Setpoint& end, 
	const MotionProfileConfig& config, bool reversed) :
	m_params({0,0,0,0,0}),
	m_start(start), 
	m_end(end), 
	m_config(config), 
	m_reversed(reversed) { Generate(); }

const std::vector<MotionPart>& MotionProfile::GetParts() const {
	return m_parts;
}

const Setpoint& MotionProfile::GetStart() const {
	return m_start;
}

const Setpoint& MotionProfile::GetEnd() const {
	return m_end;
}

const Setpoint MotionProfile::GetSetpointT(double t) const {
	for (const auto& part : m_parts) {
		if (part.ContainsTime(t))
			return part.FindSetpointT(t);
	}
}
const Setpoint MotionProfile::GetSetpointD(double d) const {
		for (const auto& part : m_parts) {
			if (part.ContainsPos(d))
				return part.FindSetpointD(d);
		}
}

/*
generates the parameters of motion for the profile, used once at the start of Generate
*/
void MotionProfile::GenerateParams() {
	m_params.dist = m_end.GetPos() - m_start.GetPos();
	m_params.time = m_end.GetTime() - m_start.GetTime();
	m_params.accel = m_config.maxAcc;
	m_params.decel = -m_params.accel;
	m_params.cruiseVel = std::fmin(std::sqrt(m_params.dist*m_params.accel), m_config.maxVel);

	if (m_params.time != 0) {
		double deltaV = m_params.cruiseVel - m_start.GetVelocity();
		double accelInterval = deltaV / m_params.accel;
		double accelDist = (m_start.GetVelocity() + m_params.cruiseVel) * accelInterval / 2;
		double cruiseDist = m_params.dist - (2 * accelDist);
		double cruiseInterval = cruiseDist / m_params.cruiseVel;
		double totalInterval = cruiseInterval + (2*accelInterval);

		//reconsider parameters only if requested time is above
		//higher than optimal time(otherwise we overshoot)
		if (totalInterval < m_params.time) {
			//prepare triangular profile
			if ((int)cruiseDist == 0) {
				m_params.accel = std::fmin(deltaV / (m_params.time / 2), m_config.maxAcc);
			}
			else {
				//prepare trapezoidal profile which keeps
				//the original proportion between cruise and acceleration time
				double timeProportion = cruiseInterval / accelInterval;
				accelInterval = m_params.time / (timeProportion + 2);
				cruiseInterval = m_params.time - (2 * accelInterval);
				double cruiseVel = std::fmin(m_params.dist * 2 / (m_params.time + cruiseInterval), m_config.maxVel);
				m_params.cruiseVel = cruiseVel;
				deltaV = m_params.cruiseVel - m_start.GetVelocity();
				m_params.accel = std::fmin(deltaV / accelInterval, m_config.maxAcc);
			}
		}
		m_params.decel = -m_params.accel;
	}
}

/*
while reading this function take note that time variables represent a coordinate and not the time to complete an action, which is called an interval.
*/
void MotionProfile::Generate() {
	GenerateParams();

	double accel = m_params.accel;
	double decel = m_params.decel;
	double cruiseVel = m_params.cruiseVel;
	
	double deltaVStart = cruiseVel - m_start.GetVelocity();
	double accelInterval = deltaVStart / accel;
	double accelDist = (cruiseVel + m_start.GetVelocity()) * accelInterval / 2;

	double deltaVEnd = m_end.GetVelocity() - cruiseVel;
	double decelInterval = deltaVEnd / decel;
	double decelDist = (cruiseVel + m_end.GetVelocity()) * decelInterval / 2;

	double cruiseDist = m_params.dist - accelDist - decelDist;

	double timeToCruise = m_start.GetTime() + accelInterval;
	double accelPos = m_start.GetPos() + accelDist;

	Setpoint toCruise(accelPos, timeToCruise, cruiseVel);
	m_parts.push_back({ m_start, toCruise, m_config.dt, m_reversed });

	//triangular profile
	//cast to int to round down
	if ((int)cruiseDist == 0) {	
		double endTime = timeToCruise + decelInterval;
		double endPos = accelPos + decelDist;

		Setpoint end(endPos, endTime, m_end.GetVelocity());
		m_end = end;
		m_parts.push_back({ toCruise, end, m_config.dt, m_reversed });
		
	}
	//trapezoidal
	else {
		double cruiseInterval = cruiseDist / cruiseVel;
		double cruiseTime = cruiseInterval + timeToCruise;
		double endCruisePos = cruiseDist + accelPos;
		Setpoint cruiseEnd(endCruisePos, cruiseTime, cruiseVel);
		m_parts.push_back({ toCruise, cruiseEnd, m_config.dt, m_reversed });

		double endTime = cruiseTime + decelInterval;
		double endPos = endCruisePos + decelDist;

		Setpoint end(endPos, endTime, m_end.GetVelocity());
		m_end = end;
		m_parts.push_back({ cruiseEnd, end, m_config.dt, m_reversed });
	}

	m_params.time = m_end.GetTime() - m_start.GetTime();
}


const double MotionProfile::GetDist() const {
	return m_params.dist;
}

const double MotionProfile::GetTime() const {
	return m_params.time;
}



