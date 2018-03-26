#pragma once

#include <memory>
#include "motion/MotionProfile.h"
#include "path/Path.h"

/*
A Trajectory Point(or TrajPoint) combines info about a MotionProfile Setpoint and a Path Waypoint
and allows access specific to information for following the trajectory
*/

struct TrajPoint {
private:
	Setpoint m_sp;
	Waypoint m_wp;

public:
	TrajPoint(const Setpoint& sp, const Waypoint& wp);

	//Setpoint interface
	const double GetPos() const;
	const double GetVelocity() const;
	const double GetAcceleration() const;

	//Waypoint interface
	const double GetHeading() const;
	const double GetHeadingDegrees() const;

};

class Trajectory {
private:
	Path m_path;
	MotionProfileConfig m_config;
	double m_time;
	bool m_reversed;
	MotionProfile m_profile;
public:
	Trajectory(const Path& p, const MotionProfileConfig& config, double time = 0, bool reversed = false);

	const MotionProfileConfig& GetConfig() const;

	const TrajPoint GetTrajPointT(double t);
	const TrajPoint GetTrajPointD(double d);

	const MotionProfile& GetProfile() const;
	const Path& GetPath() const;
	const std::vector<Waypoint>& GetWaypoints() const;

	const double GetDistance() const;
	const double GetTime() const;
	const bool IsReversed() const;
};

