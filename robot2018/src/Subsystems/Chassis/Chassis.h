#ifndef Chassis_H
#define Chassis_H

#include "../../Constants.h"
#include <Commands/Subsystem.h>
#include <memory>
#include <VictorSP.h>
#include <SpeedControllerGroup.h>
#include <AHRS.h>
#include <Drive/DifferentialDrive.h>
#include <Encoder.h>

class Chassis : public frc::Subsystem {
private:
	Chassis();

	float LimitSpeed(float speed);

	frc::VictorSP m_rLeft;
	frc::VictorSP m_fLeft;
	frc::VictorSP m_rRight;
	frc::VictorSP m_fRight;
	std::unique_ptr<frc::SpeedControllerGroup> m_left;
	std::unique_ptr<frc::SpeedControllerGroup> m_right;

	std::unique_ptr<AHRS> m_navx;

	std::unique_ptr<frc::Encoder> m_lEnc;
	std::unique_ptr<frc::Encoder> m_rEnc;

public:
	static Chassis& GetInstance();

	void InitDefaultCommand();

	void TankDrive(double left, double right);
	void CurveDrive(double speed, double curve);

	const float GetAngle() const;
	void ZeroYaw(); //reset angle to zero

	const float GetVelocity() const; //get from encoders(hint: average of both encoder speeds)
};

#endif  // Chassis_H
