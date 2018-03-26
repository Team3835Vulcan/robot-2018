/*
 * TrajectoryController.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Nadav Strahilevitz
 *
 *  This class maintains an encoder and a trajectory
 *  and determines according to the encoder what output to give
 *  to the engine
 */

#ifndef SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_TRAJECTORYCONTROLLER_H_
#define SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_TRAJECTORYCONTROLLER_H_

#include <Trajectory.h>
#include <RobotController.h>
#include <Encoder.h>

class TrajectoryController {
private:

	Trajectory* m_traj;

	double m_kp;
	double m_kd;
	double m_kv;
	double m_kpv; //kp for velocity
	double m_ka;

	double m_totalError;
	double m_currDist;
	double m_goalDist;

	double m_currVel;
	double m_goalVel;

	double m_tolerance;

	bool m_enabled;

	double Clamp(double val, double min, double max);
public:
	TrajectoryController();

	void Configure(double kp, double kd, double kv, double kpv, double ka);
	void SetTrajectory(Trajectory& traj);

	bool IsOnTarget();

	void Enable();
	void Disable();
	void Reset();

	double Calculate(double dist, double vel);

};

#endif /* SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_TRAJECTORYCONTROLLER_H_ */
