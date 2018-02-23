#ifndef DrivePath_H
#define DrivePath_H

#include <memory>
#include "Commands/Command.h"
#include <Subsystems/Chassis/Controllers/TrajectoryController.h>

class DrivePath : public frc::Command {
private:
	Trajectory m_traj;
	TrajectoryController m_controller;
public:
	DrivePath(const Trajectory& traj);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DrivePath_H
