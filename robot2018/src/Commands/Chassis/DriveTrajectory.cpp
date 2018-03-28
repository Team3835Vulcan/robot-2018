#include "DriveTrajectory.h"
#include <Constants.h>
#include <Subsystems/Chassis/Chassis.h>
#include <path/TankFitter.h>
#include <iostream>

DriveTrajectory::DriveTrajectory(const Trajectory& t) :
	m_traj(std::make_unique<Trajectory>(t)){
	TankFitter fitter(WHEELBASE);
	fitter.Fit(*m_traj);
	m_leftTraj = std::make_unique<Trajectory>(fitter.GetLeft());
	m_rightTraj = std::make_unique<Trajectory>(fitter.GetRight());
	Requires(&Chassis::GetInstance());
}

// Called just before this Command runs the first time
void DriveTrajectory::Initialize() {
	m_leftFollower.SetTrajectory(*m_leftTraj);
	m_leftFollower.Configure(0,0,VELOCITY_FEEDFORWARD,
			0, ACCELERATION_FEEDFORWARD);
	m_leftFollower.Reset();
	m_rightFollower.SetTrajectory(*m_rightTraj);
	m_rightFollower.Configure(0,0,VELOCITY_FEEDFORWARD,
			0, ACCELERATION_FEEDFORWARD);
	m_rightFollower.Reset();
	Chassis::GetInstance().ResetEncoders();

	m_leftFollower.Enable();
	m_rightFollower.Enable();
}

// Called repeatedly when this Command is scheduled to run
void DriveTrajectory::Execute() {
	std::cout << "calculate\n";
	double leftDist = Chassis::GetInstance().GetLeftDistance();
	double leftVel = Chassis::GetInstance().GetLeftVelocity();

	double rightDist = Chassis::GetInstance().GetRightDistance();
	double rightVel = Chassis::GetInstance().GetRightVelocity();

	double dist = Chassis::GetInstance().GetDistance();
	double heading = Chassis::GetInstance().GetAngle();

	double leftRes = m_leftFollower.Calculate(leftDist, leftVel);
	double rightRes = m_rightFollower.Calculate(rightDist, rightVel);


	double deltaTheta = m_traj->GetTrajPointD(dist).GetHeadingDegrees() - heading;
	double turn = K_TURN_HEADING * deltaTheta;
	std::cout << deltaTheta << '\n';
	std::cout << leftRes << " " << rightRes << " " << turn << '\n';

	Chassis::GetInstance().TankDrive(leftRes + turn, rightRes - turn);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveTrajectory::IsFinished() {
	double len = m_traj->GetDistance();
	double dist = Chassis::GetInstance().GetDistance();
	return std::fabs(len - dist) <= m_traj->GetConfig().tolerance;
	//return m_leftFollower.IsOnTarget() || m_rightFollower.IsOnTarget();
}

// Called once after isFinished returns true
void DriveTrajectory::End() {
	m_leftFollower.Disable();
	m_rightFollower.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveTrajectory::Interrupted() {
	m_leftFollower.Disable();
	m_rightFollower.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}
