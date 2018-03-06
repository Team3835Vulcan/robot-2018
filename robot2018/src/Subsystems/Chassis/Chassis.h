#ifndef Chassis_H
#define Chassis_H

#include "../../Constants.h"
#include <Commands/Subsystem.h>
#include <memory>
#include <VictorSP.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <AHRS.h>
#include "ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h"

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;

class Chassis : public frc::Subsystem {
private:
	Chassis();

	float LimitSpeed(float speed);

	WPI_VictorSPX m_rLeft;
	WPI_VictorSPX m_fLeft;
	WPI_VictorSPX m_rRight;
	WPI_VictorSPX m_fRight;
	frc::SpeedControllerGroup m_left;
	frc::SpeedControllerGroup m_right;
	frc::DifferentialDrive m_drive;

	AHRS m_navx;

	frc::Encoder m_lEnc;
	frc::Encoder m_rEnc;

public:
	static Chassis& GetInstance();

	void InitDefaultCommand() override;
	void Periodic() override;

	void TankDrive(double left, double right);
	void CurveDrive(double speed, double curve);

	const double GetAngle();
	void ZeroYaw(); //reset angle to zero

	const double GetVelocity() const; //get from encoders(hint: average of both encoder speeds)
	const double GetDistance() const;
	void ResetEncoders();
};

#endif  // Chassis_H
