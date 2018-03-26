#ifndef DriveTrajectory_H
#define DriveTrajectory_H

#include <Commands/Command.h>
#include <Subsystems/Chassis/Controllers/TrajectoryController.h>
#include <Trajectory.h>

class DriveTrajectory : public frc::Command {
private:
	std::unique_ptr<Trajectory> m_traj;
	std::unique_ptr<Trajectory> m_leftTraj;
	std::unique_ptr<Trajectory> m_rightTraj;
	TrajectoryController m_leftFollower;
	TrajectoryController m_rightFollower;

public:
	DriveTrajectory(const Trajectory& traj);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveTrajectory_H
