/*
 * MotionProfileDriveController.h
 *
 *  Created on: 22 בינו׳ 2018
 *      Author: Coding Monkeys
 */

#ifndef SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILEDRIVECONTROLLER_H_
#define SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILEDRIVECONTROLLER_H_
#include <util/PIDController.h>
#include <memory>

namespace vulcan {

class MotionProfileDriveController {
private:
	const float m_tolerance;
	const float m_dt = 0.02;

	std::unique_ptr<vulcan::PIDController> m_velController;


public:
	MotionProfileDriveController(float dist, float tolerance, float dt);
	MotionProfileDriveController(float dist, float tolerance);

	bool IsOnTarget();
};

} /* namespace vulcan */

#endif /* SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILEDRIVECONTROLLER_H_ */
