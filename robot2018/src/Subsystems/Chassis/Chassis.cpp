#include "Chassis.h"
#include <Commands/Chassis/JoystickTankDrive.h>

Chassis::Chassis() : Subsystem("Chassis"), m_rLeft(RLEFT_MOTOR), m_fLeft(FLEFT_MOTOR),
										   m_rRight(RRIGHT_MOTOR), m_fRight(FRIGHT_MOTOR),
										   m_left(std::make_unique<frc::SpeedControllerGroup>(m_rLeft, m_fLeft)),
										   m_right(std::make_unique<frc::SpeedControllerGroup>(m_rRight, m_fRight)),
										   m_navx(std::make_unique<AHRS>(I2C::Port::kOnboard)), // Should be constant
										   m_lEnc(std::make_unique<frc::Encoder>(LEFT_ENCODER_A, LEFT_ENCODER_B)),
										   m_rEnc(std::make_unique<frc::Encoder>(RIGHT_ENCODER_A, RIGHT_ENCODER_B)){
	m_navx->Reset();
	m_left->SetInverted(true);
	m_lEnc->SetDistancePerPulse(DISTANCE_PER_PULSE);
	m_rEnc->SetDistancePerPulse(DISTANCE_PER_PULSE);
}

Chassis& Chassis::GetInstance()
{
	static Chassis instance;
	return instance;
}

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTankDrive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::TankDrive(double left, double right)
{
	m_left->Set(LimitSpeed(left));
	m_right->Set(LimitSpeed(right));
}

void Chassis::CurveDrive(double speed, double curve)
{
	m_left->Set(LimitSpeed(speed + curve));
	m_right->Set(LimitSpeed(speed - curve));
}

float Chassis::LimitSpeed(float speed)
{
	if(speed > 1.0)
		return 1.0;

	if(speed < -1.0)
		return -1.0;

	return speed;
}

const float Chassis::GetAngle() const
{
	return m_navx->GetYaw();
}

void Chassis::ZeroYaw()
{
	m_navx->ZeroYaw();
}

const float Chassis::GetVelocity() const
{
	return (m_lEnc->GetRate() + m_rEnc->GetRate()) / 2;
}
