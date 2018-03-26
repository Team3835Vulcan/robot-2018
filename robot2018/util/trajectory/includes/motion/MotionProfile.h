#pragma once
#include <vector>
#include "Setpoint.h"
#include "MotionPart.h"

/*
Defines constraints for the the profile
*/

struct MotionProfileConfig {
	double dt;
	double maxAcc;
	double maxVel;
	double tolerance;
};

/*
Defines the parameters of the movement created by the profile
*/
struct MotionProfileParams {
	double accel;
	double decel;
	double cruiseVel;
	double dist;
	double time;
};

/*
Defines a trapezoidal/triangular velocity to time function.
Calculation will be made time-optimal unless specified otherwise
*/
class MotionProfile {
private:
	MotionProfileParams m_params;
	Setpoint m_start, m_end;
	MotionProfileConfig m_config;
	std::vector<MotionPart> m_parts;
	bool m_reversed;

	void GenerateParams();
	void Generate();

public:	
	MotionProfile(const Setpoint& start, const Setpoint& end, 
		const MotionProfileConfig& config, bool reversed = false);

	const Setpoint& GetStart() const;
	const Setpoint& GetEnd() const;

	const std::vector<MotionPart>& GetParts() const;
	const Setpoint GetSetpointT(double t) const;
	const Setpoint GetSetpointD(double d) const;

	const double GetDist() const;
	const double GetTime() const;
};

