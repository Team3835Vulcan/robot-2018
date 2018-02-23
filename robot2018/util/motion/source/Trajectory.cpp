#include "../Trajectory.h"

TrajPoint::TrajPoint(const Setpoint& sp, const Waypoint& wp) : m_sp(sp), m_wp(wp) {}

Trajectory::Trajectory(const MotionProfileConfig& config, const Path& p) :
		m_config(config),
		m_path(p),
		m_profile(Setpoint(0),Setpoint(m_path.GetLength()),m_config){
}

MotionProfileConfig& Trajectory::GetConfig(){
	return m_config;
}

const TrajPoint Trajectory::GetTrajPoint(double t) {
	auto sp = m_profile.GetSetpoint(t);
	auto wp = m_path.GetWaypoint(sp->GetPos());
	return TrajPoint(*sp, wp);

}

const MotionProfile& Trajectory::GetProfile() const {
	return m_profile;
}

const Path& Trajectory::GetPath() const {
	return m_path;
}

const double Trajectory::GetDistance() const{
	return m_profile.GetDist();
}

const double Trajectory::GetTime() const{
	return m_profile.GetTime();
}
