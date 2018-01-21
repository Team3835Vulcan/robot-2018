#ifndef Chassis_H
#define Chassis_H

#include <Commands/Subsystem.h>
#include <"WPILib.h">

class Chassis : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Chassis* get();
	void InitDefaultCommand();
	void Drive(double left, double right);

private:
	Chassis();
	static Chassis* instance = 0;

	frc::SpeedControllerGroup* leftGroup;
	frc::SpeedControllerGroup* rightGroup;

	frc::Talon* leftMotor1;
	frc::Talon* leftMotor2;
	frc::Talon* leftMotor3;

	frc::Talon* rightMotor1;
	frc::Talon* rightMotor2;
	frc::Talon* rightMotor3;

	frc::Encoder* leftEncoder;
	frc::Encoder* rightEncoder;
};

#endif  // Chassis_H
