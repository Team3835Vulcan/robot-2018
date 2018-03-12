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
#include "../Chassis.h"

struct DriveSignal{
	double speed;
	double curve;
};

class TrajectoryController {
private:
	double m_ka;
	double m_kt; //rotation parameter

	double m_currHeading;
	double m_goalHeading;

	double m_tolerance;

	bool m_enabled;

	double Clamp(double val, double min, double max);
public:
	TrajectoryController();

	void Configure(double kp, double kd, double kv, double kpv, double ka, double kt);
	void SetTrajectory(const Trajectory& traj);

	bool IsOnTarget();

	void Enable();
	void Disable();
	void Reset();

	const DriveSignal Calculate();
};

#endif /* SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_TRAJECTORYCONTROLLER_H_ */
