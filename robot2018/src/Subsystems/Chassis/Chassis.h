#ifndef Chassis_H
#define Chassis_H

#include "../../Constants.h"
#include <Commands/Subsystem.h>
#include <memory>
#include <VictorSP.h>
#include <SpeedControllerGroup.h>
#include <AHRS.h>
#include <Drive/DifferentialDrive.h>
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
	std::unique_ptr<frc::SpeedControllerGroup> m_left;
	std::unique_ptr<frc::SpeedControllerGroup> m_right;

	std::unique_ptr<AHRS> m_navx;

	std::unique_ptr<frc::Encoder> m_lEnc;
	std::unique_ptr<frc::Encoder> m_rEnc;

public:
	static Chassis& GetInstance();

	void InitDefaultCommand() override;
	void Periodic() override;

	void TankDrive(double left, double right);
	void CurveDrive(double speed, double curve);

	const float GetAngle() const;
	void ZeroYaw(); //reset angle to zero

	const float GetVelocity() const; //get from encoders(hint: average of both encoder speeds)
	const float GetDistance() const;
	void ResetEncoders() const;
};

#endif  // Chassis_H
