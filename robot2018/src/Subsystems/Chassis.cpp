#include "Chassis.h"
#include "../RobotMap.h"

Chassis::Chassis() {
	leftMotor1 = new frc::Talon(0);
	leftMotor2 = new frc::Talon(1);
	leftMotor3 = new frc::Talon(2);

	leftGroup = new frc::SpeedControllerGroup(leftMotor1, leftMotor2, leftMotor3);

	rightMotor1 = new frc::Talon(3);
	rightMotor2 = new frc::Talon(4);
	rightMotor3 = new frc::Talon(5);

	rightGroup = new frc::SpeedControllerGroup(rightMotor1, rightMotor2, rightMotor3);

	leftEncoder = new frc::Encoder(0, 3);
	rightEncoder = new frc::Encoder(3, 5);
}

Chassis* Chassis::get()
{
	if(instance == 0)
	{
		instance = new Chassis();
	}

	return instance;
}

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::Drive(double left, double right)
{
	leftGroup->Set(left);
	rightGroup->Set(right);
}
