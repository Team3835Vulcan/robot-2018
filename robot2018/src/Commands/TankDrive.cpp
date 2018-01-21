#include "TankDrive.h"

TankDrive::TankDrive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

TankDrive::TankDrive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::chassis->get()); // need to fix
}

// Called repeatedly when this Command is scheduled to run
void TankDrive::Execute() {
	Robot::chassis->Drive(Robot::oi->GetLeftY(), Robot::oi->GetRightY());
}

// Make this return true when this Command no longer needs to run execute()
bool TankDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TankDrive::End() {
	Robot::chassis->Drive(0.0, 0.0);
}
