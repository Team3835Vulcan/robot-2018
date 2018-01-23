#include "JoystickTankDrive.h"
#include <Subsystems/Chassis/Chassis.h>
#include <OI.h>

JoystickTankDrive::JoystickTankDrive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Chassis::GetInstance());
}

// Called repeatedly when this Command is scheduled to run
void JoystickTankDrive::Execute() {
	Chassis::GetInstance()->TankDrive(OI::GetInstance()->GetLeftY(), OI::GetInstance()->GetRightY());
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickTankDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickTankDrive::End() {
	Chassis::GetInstance()->TankDrive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickTankDrive::Interrupted() {
	End();
}
