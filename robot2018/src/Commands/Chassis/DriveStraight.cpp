#include "DriveStraight.h"
#include <Subsystems/Chassis/Chassis.h>
#include <iostream>

DriveStraight::DriveStraight(double dist, bool reversed) :
	m_dist(dist),
	m_reverse(reversed) {
	// Use Requires() here to declare subsystem dependencies
	std::cout << "FV";
	Requires(&Chassis::GetInstance());
	std::cout << "A";
}

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
	std::cout << "trilili\n";
	std::cout << "sadl;ma\n";
	std::cout << "lsamd;lasm;\n";
	double angle = Chassis::GetInstance().GetAngle();
	std::cout << "angl\n";
	if(angle > 180)
		angle = angle - 360;
	std::cout << "switched\n";
	double angleRad = angle * PI / 180;
	Path p({{{0,0}, angle},
		{{m_dist * std::cos(angleRad),m_dist * std::sin(angleRad)}, angle}});
	p.Generate();
	std::cout << "generated\n";
	m_traj =  std::make_unique<Trajectory>(std::move(p), DEFAULT_CONFIG, 0, m_reverse);
	std::cout << "created";
	m_controller.SetTrajectory(*m_traj);
	m_controller.Configure(0,0,VELOCITY_FEEDFORWARD,
				1, ACCELERATION_FEEDFORWARD);
	Chassis::GetInstance().ResetEncoders();
	m_controller.Reset();
	m_controller.Enable();
}

// Called repeatedly when this Command is scheduled to run
void DriveStraight::Execute() {
	std::cout << "calculating\n";
	double speed = Chassis::GetInstance().GetVelocity();
	double dist = Chassis::GetInstance().GetDistance();
	double heading = Chassis::GetInstance().GetAngle();
	double result = m_controller.Calculate(dist, speed);
	double deltaTheta = m_traj->GetTrajPointD(dist).GetHeadingDegrees() - heading;
	std::cout << deltaTheta << "\n";
	double turn = K_HOLD_HEADING * deltaTheta;
	std::cout << result << " " << turn << "\n";
	Chassis::GetInstance().CurveDrive(result, -turn);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveStraight::IsFinished() {
	return m_controller.IsOnTarget();
}

// Called once after isFinished returns true
void DriveStraight::End() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraight::Interrupted() {
	m_controller.Disable();
	Chassis::GetInstance().TankDrive(0,0);
}
