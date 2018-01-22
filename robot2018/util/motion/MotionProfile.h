#pragma once
#include <vector>
#include <forward_list>
#include "Setpoint.h"
#include "MotionPart.h"


namespace vulcan{
/*
Defines constraints for the the profile
*/

struct MotionProfileConfig {
	const float m_maxAcc;
	const float m_maxVel;

	MotionProfileConfig(float maxAcc, float maxVel) :
		m_maxAcc(maxAcc), m_maxVel(maxVel) {}
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
	std::unique_ptr<Setpoint> GetSetpoint(float t) const;
	MotionProfile(const Setpoint& start, const Setpoint& end, const MotionProfileConfig& config);
	void Generate();
};

}
