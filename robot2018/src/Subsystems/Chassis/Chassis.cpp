#include "Chassis.h"
#include <Commands/Chassis/JoystickTankDrive.h>
#include <SmartDashboard/SmartDashboard.h>

Chassis::Chassis() : Subsystem("Chassis"), m_rLeft(RLEFT_MOTOR),
   m_fLeft(FLEFT_MOTOR),
   m_rRight(RRIGHT_MOTOR), m_fRight(FRIGHT_MOTOR),
   m_left(std::make_unique<frc::SpeedControllerGroup>(m_rLeft, m_fLeft)),
   m_right(std::make_unique<frc::SpeedControllerGroup>(m_rRight, m_fRight)),
   m_drive(std::make_unique<frc::DifferentialDrive>(*m_left.get(), *m_right.get())),
   m_navx(std::make_unique<AHRS>(I2C::Port::kOnboard)), // Should be constant
   m_lEnc(std::make_unique<frc::Encoder>(LEFT_ENCODER_A, LEFT_ENCODER_B)),
   m_rEnc(std::make_unique<frc::Encoder>(RIGHT_ENCODER_A, RIGHT_ENCODER_B)){
	m_navx->Reset();
	m_navx->ZeroYaw();
	m_lEnc->Reset();
	m_rEnc->Reset();
	//m_left->SetInverted(true);
	m_lEnc->SetReverseDirection(true);
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

void Chassis::Periodic(){
	float angle = GetAngle();
	bool navxConnected = m_navx->IsConnected();
	float lDist = m_lEnc->GetDistance();
	float rDist = m_rEnc->GetDistance();
	float dist = (lDist + rDist) / 2;
	float lVel = m_lEnc->GetRate();
	float rVel = m_rEnc->GetRate();
	float vel = GetVelocity();
	double pulses = (m_lEnc->Get() + m_rEnc->Get()) / 2;
	frc::SmartDashboard::PutNumber("dist per pulse", DISTANCE_PER_PULSE);
	frc::SmartDashboard::PutNumber("yaw", angle);
	frc::SmartDashboard::PutNumber("robot speed", vel);
	frc::SmartDashboard::PutBoolean("navx connected", navxConnected);
	frc::SmartDashboard::PutNumber("left enc dist", lDist);
	frc::SmartDashboard::PutNumber("right enc dist", rDist);
	frc::SmartDashboard::PutNumber("distance[m]", dist);
	frc::SmartDashboard::PutNumber("left enc vel", lVel);
	frc::SmartDashboard::PutNumber("right enc vel", rVel);
	frc::SmartDashboard::PutNumber("avg enc pulses", m_rEnc->Get());

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::TankDrive(double left, double right)
{
	//m_left->Set(-LimitSpeed(left));
	//m_right->Set(-LimitSpeed(right));
	m_drive->TankDrive(left, right, false);
}

void Chassis::CurveDrive(double speed, double curve)
{
	//m_left->Set(LimitSpeed(speed + curve));
	//m_right->Set(LimitSpeed(speed - curve));
	m_drive->CurvatureDrive(speed, curve, false);
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
	float angle = -1 * m_navx->GetYaw() + 90;
	if(angle > 180)
		return angle - 360;
	return angle;
}

void Chassis::ZeroYaw()
{
	m_navx->ZeroYaw();
}

const float Chassis::GetVelocity() const
{
	return (m_lEnc->GetRate() + m_rEnc->GetRate()) / 2;
}

const float Chassis::GetDistance() const
{
	return (m_lEnc->GetDistance() + m_rEnc->GetDistance()) / 2;
}

void Chassis::ResetEncoders() const{
	m_rEnc->Reset();
	m_lEnc->Reset();
}
