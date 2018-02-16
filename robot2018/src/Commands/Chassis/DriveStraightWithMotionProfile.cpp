#include "DriveStraightWithMotionProfile.h"
#include <Constants.h>

DriveStraightWithMotionProfile::DriveStraightWithMotionProfile(double dist) : m_dist(dist),
		m_yaw0(Chassis::GetInstance().GetAngle()){
	// Use Requires() here to declare subsystem dependencies
	Requires(&Chassis::GetInstance());
}

// Called just before this Command runs the first time
void DriveStraightWithMotionProfile::Initialize() {
	Chassis::GetInstance().ZeroYaw();

	this->m_controller = std::make_unique<vulcan::MotionProfileDriveController>(
	0.05);
	vulcan::MotionProfileConfig config(MAX_ROBOT_VELOCITY, MAX_ROBOT_ACCELERATION);
	vulcan::Setpoint start(0,0,0);
	vulcan::Setpoint end(0,m_dist,0);
	m_controller->SetProfile(vulcan::MotionProfile(start,end,config));
	m_controller->SetPID(0.00005,0,0);
	m_controller->Enable();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraightWithMotionProfile::Execute() {
	m_controller->Calculate();
	double output = m_controller->GetOutput();
	double dTheta = Chassis::GetInstance().GetAngle() - m_yaw0;
	Chassis::GetInstance().CurveDrive(output, -m_angleKP * dTheta);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraightWithMotionProfile::IsFinished() {
	return m_controller->IsOnTarget();
}

// Called once after isFinished returns true
void DriveStraightWithMotionProfile::End() {
	Chassis::GetInstance().TankDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightWithMotionProfile::Interrupted() {
	Chassis::GetInstance().TankDrive(0,0);
}
