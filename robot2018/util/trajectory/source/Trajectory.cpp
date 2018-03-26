#include "Trajectory.h"

TrajPoint::TrajPoint(const Setpoint& sp, const Waypoint& wp) : m_sp(sp), m_wp(wp) {}

const double TrajPoint::GetPos() const {
	return m_sp.GetPos();
}
const double TrajPoint::GetVelocity() const {
	return m_sp.GetVelocity();
}
const double TrajPoint::GetAcceleration() const {
	return m_sp.GetAcceleration();
}

const double TrajPoint::GetHeading() const {
	return m_wp.GetHeading();
}
const double TrajPoint::GetHeadingDegrees() const {
	return m_wp.GetHeadingInDegrees();
}

Trajectory::Trajectory(const Path& p, const MotionProfileConfig& config, double time, bool reversed) :
	m_path(p),
	m_config(config),
	m_time(time),
	m_reversed(reversed),
	m_profile(Setpoint(0), Setpoint(m_path.GetLength(), time), m_config, reversed){}

const MotionProfileConfig& Trajectory::GetConfig() const{
	return m_config;
}

const TrajPoint Trajectory::GetTrajPointT(double t) {
	auto sp = m_profile.GetSetpointT(t);
	auto wp = m_path.GetWaypoint(sp.GetPos());
	return TrajPoint(sp, wp);
}
const TrajPoint Trajectory::GetTrajPointD(double d) {
	if (m_reversed)
		d = GetDistance() - d;
	auto sp = m_profile.GetSetpointD(d);
	auto wp = m_path.GetWaypoint(d);
	return TrajPoint(sp, wp);
}


const MotionProfile& Trajectory::GetProfile() const {
	return m_profile;
}

const Path& Trajectory::GetPath() const {
	return m_path;
}
const std::vector<Waypoint>& Trajectory::GetWaypoints() const {
	return m_path.GetWaypoints();
}


const double Trajectory::GetDistance() const {
	return m_profile.GetDist();
}

const double Trajectory::GetTime() const {
	return m_profile.GetTime();
}
const bool Trajectory::IsReversed() const {
	return m_reversed;
}
