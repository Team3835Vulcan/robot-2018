#pragma once

#include <memory>
#include <unordered_map>
#include "Setpoint.h"

/*
	MotionPart describes a motion between two setpoints which has linear acceleration
*/

class MotionPart {
private:
	const Setpoint m_start;
	const Setpoint m_end;
	
	const double m_distance;
	const double m_time;
	const double m_acc;
	const double m_dt;

public:
	MotionPart(const Setpoint& start, const Setpoint& end);
	MotionPart(const Setpoint& start, const Setpoint& end, float dt);

	const bool IsValid() const;

	const bool ContainsTime(double t) const;
	const bool ContainsPos(double pos) const;
	
	const Setpoint& GetStart() const;
	const Setpoint& GetEnd() const;

	//returns null if setpoint if time is not contained
	std::unique_ptr<Setpoint> FindSetpointT(double t) const;
	std::unique_ptr<Setpoint> FindSetpointD(double d) const;
};
