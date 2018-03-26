/*
 * MotionProfileController.h
 *
 *  Created on: Mar 12, 2018
 *      Author: Coding Monkeys
 */

#ifndef SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILECONTROLLER_H_
#define SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILECONTROLLER_H_

#include <memory>
#include <util/motion/MotionProfile.h>
#include "../Chassis.h"

class MotionProfileController {
private:
	std::unique_ptr<MotionProfile> m_traj;

	double m_kp;
	double m_kd;
	double m_kv;
	double m_kpv; //kp for velocity

	double m_totalError;
	double m_currDist;
	double m_goalDist;

	double m_currVel;
	double m_goalVel;

public:
	MotionProfileController();
};

#endif /* SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILECONTROLLER_H_ */
