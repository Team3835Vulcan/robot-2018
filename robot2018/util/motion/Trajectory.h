#pragma once

#include <memory>
#include "MotionProfile.h"
#include "Path.h"

struct TrajPoint {
	Setpoint m_sp;
	Waypoint m_wp;

	TrajPoint(const Setpoint& sp, const Waypoint& wp);
};

class Trajectory
{
private:
	MotionProfileConfig m_config;
	Path m_path;
	MotionProfile m_profile;
public:
	Trajectory(const MotionProfileConfig& config, const Path& p);

	MotionProfileConfig& GetConfig();

	const TrajPoint GetTrajPointT(double t);
	const TrajPoint GetTrajPointD(double d);

	const MotionProfile& GetProfile() const;
	const Path& GetPath() const;

	const double GetDistance() const;
	const double GetTime() const;
};

