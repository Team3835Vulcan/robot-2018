#ifndef TurnAngle_H
#define TurnAngle_H

#include <Commands/Command.h>
#include <util/PIDController.h>
#include <memory>

class TurnAngle : public frc::Command {
private:

	const double m_angle;
	std::unique_ptr<vulcan::PIDController> m_turnController;
public:
	TurnAngle(double angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TurnAngle_H
