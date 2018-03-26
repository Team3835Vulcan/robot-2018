/*
 * TrajectoryController.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Coding Monkeys
 */

#include "TrajectoryController.h"
#include <iostream>
#include <cmath>

TrajectoryController::TrajectoryController() :
	m_traj(nullptr), m_kp(0), m_kd(0), m_kv(0),
	m_kpv(0), m_ka(0), m_totalError(0),
	m_currDist(0),m_goalDist(0), m_currVel(0),
	m_goalVel(0), m_tolerance(0), m_enabled(false){}


void TrajectoryController::Configure
	(double kp, double kd, double kv,
	double kpv, double ka){
	m_kp = kp;
	m_kd = kd;
	m_kv = kv;
	m_kpv = kpv;
	m_ka = ka;
}

void TrajectoryController::SetTrajectory(Trajectory& traj){
	m_traj = &traj;
	m_goalDist = m_traj->GetDistance();
	m_tolerance = m_traj->GetConfig().tolerance;
}

bool TrajectoryController::IsOnTarget() {
	return std::fabs(m_goalDist - m_currDist) <= m_tolerance;
}

void TrajectoryController::Enable(){
	m_enabled = true;
}
void TrajectoryController::Disable(){
	m_enabled = false;
}
void TrajectoryController::Reset(){
	m_currDist = 0;
	m_currVel = 0;
}

double TrajectoryController::Calculate(double dist, double vel){
	if(m_enabled){

		m_currDist = dist + m_tolerance;
		m_currVel =  vel;

		auto& trajpoint = m_traj->GetTrajPointD(m_currDist);

		m_goalVel = trajpoint.GetVelocity();
		double currAccel = trajpoint.GetAcceleration();
		double deltaDist = m_goalDist - m_currDist;
		double deltaVel = m_goalVel - m_currVel;

		double output = m_kp * deltaDist + m_kv * m_goalVel +
				m_kpv * deltaVel + m_ka * currAccel;
		output = Clamp(output, -1, 1);

		return output;
	}
	return 0;
}

double TrajectoryController::Clamp(double val, double min, double max){
	if(val < min)
		return min;
	if(val > max)
		return max;
	return val;
}
