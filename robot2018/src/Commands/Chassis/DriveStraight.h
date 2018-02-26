#ifndef DriveStraight_H
#define DriveStraight_H

#include "Commands/Command.h"
#include <Subsystems/Chassis/Controllers/TrajectoryController.h>

class DriveStraight : public frc::Command {
private:
	double m_dist;
	TrajectoryController m_controller;
public:
	DriveStraight(double dist);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveStraight_H
