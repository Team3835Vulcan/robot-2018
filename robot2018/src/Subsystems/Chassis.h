#ifndef Chassis_H
#define Chassis_H

#include <Commands/Subsystem.h>
#include <memory>
#include <VictorSP.h>
#include <SpeedControllerGroup.h>
#include <AHRS.h>
#include <Drive/DifferentialDrive.h>
#include <Encoder.h>

/*
 * gior,
 * we made this header for you. you must implement it. enjoy
 */

class Chassis : public frc::Subsystem {
private:
	std::shared_ptr<frc::VictorSP> m_rLeft;
	std::shared_ptr<frc::VictorSP> m_fLeft;
	std::shared_ptr<frc::VictorSP> m_rRight;
	std::shared_ptr<frc::VictorSP> m_fRight;
	std::unique_ptr<frc::SpeedControllerGroup> m_left;
	std::unique_ptr<frc::SpeedControllerGroup> m_right;

	std::unique_ptr<AHRS> m_navx;

	std::unique_ptr<frc::Encoder> m_lEnc;
	std::unique_ptr<frc::Encoder> m_rEnc;
public:
	Chassis();
	void InitDefaultCommand();

	void TankDrive(double left, double right);
	void CurveDrive(double speed, double curve);

	float GetAngle();
	void ZeroYaw(); //reset angle to zero

	float GetVelocity(); //get from encoders(hint: average of both encoder speeds)
};

#endif  // Chassis_H
