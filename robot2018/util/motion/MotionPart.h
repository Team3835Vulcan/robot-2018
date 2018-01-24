#pragma once

#include <memory>
#include "Setpoint.h"

/*
	MotionPart describes a motion between two setpoints which has linear acceleration
*/

class MotionPart {
private:
	
	const Setpoint m_start;
	const Setpoint m_end;
	
	const float m_distance;
	const float m_time;
	const float m_acc;
	
public:
	MotionPart(const Setpoint& start, const Setpoint& end);

	const bool IsValid() const;

	const bool ContainsTime(float t) const;
	const bool ContainsPos(float pos) const;
	
	const Setpoint& GetStart() const;
	const Setpoint& GetEnd() const;

	//returns null if setpoint if time is not contained
	std::unique_ptr<Setpoint> FindSetpoint(float t) const;
};
