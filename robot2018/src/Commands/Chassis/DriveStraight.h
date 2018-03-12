#ifndef DriveStraight_H
#define DriveStraight_H

#include "Commands/Command.h"
#include <Subsystems/Chassis/Controllers/TrajectoryController.h>

/*
 * Drive x meters with gyro fixing. Uses Trajectory generation
 * for smooth driving.
 */

class DriveStraight : public frc::Command {
private:
	double m_dist;
	bool m_reverse;
	TrajectoryController m_controller;
public:
	DriveStraight(double dist, bool reverse = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveStraight_H
