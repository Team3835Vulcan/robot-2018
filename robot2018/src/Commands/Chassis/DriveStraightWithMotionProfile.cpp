#include "DriveStraightWithMotionProfile.h"
#include <Subsystems/Chassis.h>
#include <Constants.h>

DriveStraightWithMotionProfile::DriveStraightWithMotionProfile(double dist) : m_dist(dist){
	// Use Requires() here to declare subsystem dependencies
	Requires(Chassis::GetInstance());
}

// Called just before this Command runs the first time
void DriveStraightWithMotionProfile::Initialize() {
	Chassis::GetInstance()->ZeroYaw();

	this->m_driveProfile = std::make_unique<vulcan::MotionProfile>(
	vulcan::Setpoint(0,0,0), vulcan::Setpoint(0,m_dist,0),
	vulcan::MotionProfileConfig(0.02, MAX_ROBOT_VELOCITY, MAX_ROBOT_ACCELERATION, 0.05)
	);
	this->m_velController = std::make_unique<vulcan::PIDController>(0.002,0,0,1/MAX_ROBOT_VELOCITY);
	m_velController->Enable();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightWithMotionProfile::Execute() {
	double currRobotSpeed = Chassis::GetInstance()->GetVelocity();
	double currTime = time->Get();
	m_velController->SetSetpoint(m_driveProfile->GetSetpoint(currTime)->GetVelocity());
	m_velController->Calculate(currRobotSpeed);
	double output = m_velController->GetOutput();

	Chassis::GetInstance()->CurveDrive(output, -m_angleKP*Chassis::GetInstance()->GetAngle());
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightWithMotionProfile::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void DriveStraightWithMotionProfile::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightWithMotionProfile::Interrupted() {

}
