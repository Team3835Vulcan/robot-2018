/*
 * TrajectoryController.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Coding Monkeys
 */

#include <Subsystems/Chassis/Controllers/TrajectoryController.h>
#include <iostream>

TrajectoryController::TrajectoryController() :
	m_kp(0), m_ki(0), m_kd(0), m_kv(0), m_kpv(0), m_ka(0), m_kt(0), m_currTime(0),
	m_goalTime(0), m_totalError(0), m_currDist(0),m_goalDist(0), m_currVel(0),
	m_goalVel(0), m_currHeading(0),m_goalHeading(0), m_tolerance(0),
	m_output(0), m_enabled(false){}

void TrajectoryController::Configure(double kp, double ki, double kd,
		double kv, double kpv, double ka, double kt){
	m_kp = kp;
	m_ki = ki;
	m_kd = kd;
	m_kv = kv;
	m_kpv = kpv;
	m_ka = ka;
	m_kt = kt;
}
void TrajectoryController::SetTrajectory(const Trajectory& traj){
	if(m_traj.get())
		m_traj.release();

	m_traj = std::make_unique<Trajectory>(traj);
	m_goalDist = m_traj->GetDistance();
	m_goalTime = m_traj->GetTime();
	m_tolerance = m_traj->GetConfig().m_tolerance;
}

bool TrajectoryController::IsOnTarget() {
	return (m_goalDist - m_currDist) <= m_tolerance ||
			(m_goalTime - m_currTime) <= m_tolerance;
}

void TrajectoryController::Enable(){
	time.Start();
	m_enabled = true;
}
void TrajectoryController::Disable(){
	time.Stop();
	m_enabled = false;
}
void TrajectoryController::Reset(){
	m_currDist = 0;
	m_currVel = 0;
	m_currHeading = 0;
	time.Reset();
}

const DriveSignal TrajectoryController::Calculate(){
	if(m_enabled){
		m_currTime = time.Get();

		m_currDist = Chassis::GetInstance().GetDistance();
		m_currVel =  Chassis::GetInstance().GetVelocity();
		m_currHeading =  Chassis::GetInstance().GetAngle();

		auto& trajpoint = m_traj->GetTrajPoint(m_currTime);

		auto& waypoint = trajpoint.m_wp;
		auto& setpoint = trajpoint.m_sp;

		m_goalHeading = waypoint.GetHeadingInDegrees();
		m_goalVel = setpoint.GetVelocity();
		double currAccel = setpoint.GetAcceleration();
		double deltaDist = m_goalDist - m_currDist;
		double deltaVel = m_goalVel - m_currVel;
		double deltaTheta = m_goalHeading - m_currHeading;

		double turn = Clamp(-m_kt * deltaTheta, -1, 1);

		double output = m_kp * deltaDist + m_kv * m_goalVel +
				m_kpv * deltaVel + m_ka * currAccel;
		output = Clamp(output, -1, 1);

		return {output , turn};
	}
	return {0,0};
}

double TrajectoryController::Clamp(double val, double min, double max){
	if(val < min)
		return min;
	if(val > max)
		return max;
	return val;
}
