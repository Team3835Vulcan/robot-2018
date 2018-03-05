#ifndef Turn_H
#define Turn_H

#include <Commands/Command.h>
#include <util/PIDController.h>
#include <Timer.h>

/*
 * Turn x degrees from current angle
 * Be aware that the command has a timeout(proportional to the angle)
 */

class Turn : public frc::Command {
private:
	double m_angle;
	vulcan::PIDController m_controller;

	Timer t;
	double m_timeout;
public:
	Turn(double angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Turn_H
