#ifndef DriveStraightWithMotionProfile_H
#define DriveStraightWithMotionProfile_H

#include <Commands/Command.h>
#include "../../../util/PIDController.h"
#include "../../../util/motion/MotionProfile.h"
#include <Timer.h>
#include <memory>

namespace vulcan{
	class PIDController;
	class MotionProfile;
}

class DriveStraightWithMotionProfile : public frc::Command {
private:
	std::unique_ptr<Timer> time;

	std::unique_ptr<vulcan::MotionProfile> m_driveProfile;
	std::unique_ptr<vulcan::PIDController> m_velController;
	const double m_angleKP = 0.0;

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
