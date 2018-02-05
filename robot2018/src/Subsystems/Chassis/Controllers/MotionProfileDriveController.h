/*
 * MotionProfileDriveController.h
 *
 *  Created on: 22 בינו׳ 2018
 *      Author: Coding Monkeys
 */

#ifndef SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILEDRIVECONTROLLER_H_
#define SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILEDRIVECONTROLLER_H_

#include <Subsystems/Chassis/Chassis.h>
#include <util/motion/MotionProfile.h>
#include <util/PIDController.h>

#include <Constants.h>
#include <Timer.h>
#include <memory>

namespace vulcan {

class MotionProfileDriveController {
private:
	Timer time;

	float m_tolerance;
	const float m_dt;
	bool m_enabled;

	float m_goalDist;
	float m_goalTime;
	float m_currDist;
	float m_currVel;
	float m_currTime;
	float m_prevTime;

	std::unique_ptr<vulcan::PIDController> m_velController;
	std::unique_ptr<vulcan::MotionProfile> m_profile;

	double output;

public:
	MotionProfileDriveController(float tolerance, float dt);
	MotionProfileDriveController(float tolerance);

	void Enable();
	void Disable();

	void SetPID(double p, double i, double d);
	void SetProfile(const vulcan::MotionProfile& profile);
	void SetTolerance(float tolerance);

	void Calculate();
	const double GetOutput() const;

	bool IsOnTarget();
};

} /* namespace vulcan */

#endif /* SRC_SUBSYSTEMS_CHASSIS_CONTROLLERS_MOTIONPROFILEDRIVECONTROLLER_H_ */
