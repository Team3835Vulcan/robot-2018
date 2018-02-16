#ifndef DriveStraightWithMotionProfile_H
#define DriveStraightWithMotionProfile_H

#include <Commands/Command.h>
#include <Subsystems/Chassis/Controllers/MotionProfileDriveController.h>
#include <memory>

namespace vulcan{
	class PIDController;
	class MotionProfile;
}

class DriveStraightWithMotionProfile : public frc::Command {
private:
	std::unique_ptr<vulcan::MotionProfileDriveController> m_controller;

	const double m_angleKP = 0.3;
	const double m_yaw0;

	const float m_dist;

public:
	DriveStraightWithMotionProfile(double dist);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveStraightWithMotionProfile_H
