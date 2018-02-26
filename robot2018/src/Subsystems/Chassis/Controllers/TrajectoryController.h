/*
 * TrajectoryController.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Coding Monkeys
 */

#ifndef SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_TRAJECTORYCONTROLLER_H_
#define SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_TRAJECTORYCONTROLLER_H_

#include <memory>
#include <util/motion/Trajectory.h>
#include <RobotController.h>
#include "../Chassis.h"

struct DriveSignal{
	double speed;
	double curve;
};

class TrajectoryController {
private:
	std::unique_ptr<Trajectory> m_traj;

	double m_kp;
	double m_ki;
	double m_kd;
	double m_kv;
	double m_kpv; //kp for velocity
	double m_ka;
	double m_kt; //rotation parameter

	double m_currTime;
	double m_goalTime;
	Timer time;

	double m_totalError;
	double m_currDist;
	double m_goalDist;

	double m_currVel;
	double m_goalVel;

	double m_currHeading;
	double m_goalHeading;

	double m_tolerance;

	double m_output;

	bool m_enabled;

	double Clamp(double val, double min, double max);
public:
	TrajectoryController();

	void Configure(double kp, double ki, double kd, double kv, double kpv, double ka, double kt);
	void SetTrajectory(const Trajectory& traj);

	bool IsOnTarget();

	void Enable();
	void Disable();
	void Reset();

	const DriveSignal Calculate();

};

#endif /* SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_TRAJECTORYCONTROLLER_H_ */
