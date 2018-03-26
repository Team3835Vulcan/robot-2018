#pragma once

#include <memory>
#include "Setpoint.h"

/*
	MotionPart describes a motion between two setpoints which has linear acceleration
*/

class MotionPart {
private:
	Setpoint m_start;
	Setpoint m_end;
	
	double m_distance;
	double m_time;
	double m_acc;
	double m_dt;

	bool m_reversed;

public:
	MotionPart(const Setpoint& start, const Setpoint& end, double dt = 1e-3, bool reversed = false);

	const bool IsValid() const;

	const bool ContainsTime(double t) const;
	const bool ContainsPos(double pos) const;
	
	const Setpoint& GetStart() const;
	const Setpoint& GetEnd() const;

	const Setpoint FindSetpointT(double t) const;
	const Setpoint FindSetpointD(double t) const;
};