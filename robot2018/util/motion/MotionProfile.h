#pragma once
#include <vector>
#include <forward_list>
#include "Setpoint.h"
#include "MotionPart.h"

/*
Defines constraints for the the profile
*/

struct MotionProfileConfig {
	const float m_dt;
	const float m_maxAcc;
	const float m_maxVel;
	const float m_tolerance;

	MotionProfileConfig(float dt, float maxAcc, float maxVel, float tolerance) :
		m_dt(dt), m_maxAcc(maxAcc), m_maxVel(maxVel), m_tolerance(tolerance) {}
};

/*
Defines a time-optimal trapezoidal/triangular velocity to time function.
as such the time of the end setpoint is ignored in calculations
*/

class MotionProfile
{
private:
	MotionProfileConfig m_config;
	Setpoint m_start, m_end;
	std::vector<MotionPart> m_parts;
	
public:

	const Setpoint& GetStart() const;
	const Setpoint& GetEnd() const;
	const std::vector<MotionPart>& GetParts() const;
	MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config);
	void Generate();
};

