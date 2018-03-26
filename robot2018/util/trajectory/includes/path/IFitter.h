#pragma once

class Trajectory;

class IFitter {
public:
	virtual void Fit(const Trajectory& traj) = 0;

	virtual ~IFitter() {}
};