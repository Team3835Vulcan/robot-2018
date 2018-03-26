#ifndef DriveStraight_H
#define DriveStraight_H

#include "Commands/Command.h"
#include <Subsystems/Chassis/Controllers/TrajectoryController.h>
#include <Trajectory.h>

/*
 * Drive x meters with gyro fixing. Uses Trajectory generation
 * for smooth driving.
 */

class DriveStraight : public frc::Command {
private:
	double m_dist;
	bool m_reverse;
	std::unique_ptr<Trajectory> m_traj;
	TrajectoryController m_controller;
public:
	DriveStraight(double dist, bool reversed = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveStraight_H
