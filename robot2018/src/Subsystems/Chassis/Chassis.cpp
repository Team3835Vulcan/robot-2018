#include "Chassis.h"
#include <Commands/Chassis/JoystickTankDrive.h>
#include <SmartDashboard/SmartDashboard.h>

Chassis::Chassis() : Subsystem("Chassis"), m_rLeft(RLEFT_MOTOR),
   m_fLeft(FLEFT_MOTOR),
   m_rRight(RRIGHT_MOTOR), m_fRight(FRIGHT_MOTOR),
   m_left(m_rLeft, m_fLeft),
   m_right(m_rRight, m_fRight),
   m_drive(m_left, m_right),
   m_navx(I2C::Port::kOnboard), // Should be constant
   m_lEnc(LEFT_ENCODER_A, LEFT_ENCODER_B),
   m_rEnc(RIGHT_ENCODER_A, RIGHT_ENCODER_B){
	m_drive.SetSafetyEnabled(false);
	m_navx.Reset();
	m_navx.ZeroYaw();
	m_lEnc.Reset();
	m_rEnc.Reset();
	m_lEnc.SetReverseDirection(true);
	m_lEnc.SetDistancePerPulse(DISTANCE_PER_PULSE);
	m_rEnc.SetDistancePerPulse(DISTANCE_PER_PULSE);
}

Chassis& Chassis::GetInstance() {
	static Chassis instance;
	return instance;
}

void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new JoystickTankDrive());
}

void Chassis::Periodic() {
	float angle = GetAngle();
	bool navxConnected = m_navx.IsConnected();
	float lDist = m_lEnc.GetDistance();
	float rDist = m_rEnc.GetDistance();
	float dist = (lDist + rDist) / 2;
	float lVel = m_lEnc.GetRate();
	float rVel = m_rEnc.GetRate();
	float vel = GetVelocity();
	frc::SmartDashboard::PutNumber("dist per pulse", DISTANCE_PER_PULSE);
	frc::SmartDashboard::PutNumber("yaw", angle);
	frc::SmartDashboard::PutNumber("robot speed", vel);
	frc::SmartDashboard::PutBoolean("navx connected", navxConnected);
	frc::SmartDashboard::PutNumber("left enc dist", lDist);
	frc::SmartDashboard::PutNumber("right enc dist", rDist);
	frc::SmartDashboard::PutNumber("distance[m]", dist);
	frc::SmartDashboard::PutNumber("left enc vel", lVel);
	frc::SmartDashboard::PutNumber("right enc vel", rVel);
	frc::SmartDashboard::PutNumber("avg enc pulses", m_rEnc.Get());

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Chassis::TankDrive(double left, double right) {
	m_drive.TankDrive(left, right, false);
}

void Chassis::CurveDrive(double speed, double curve) {
	m_drive.CurvatureDrive(speed, curve, false);
}

float Chassis::LimitSpeed(float speed) {
	if(speed > 1.0)
		return 1.0;
	if(speed < -1.0)
		return -1.0;
	return speed;
}

double Chassis::GetAngle() {
	double angle = -m_navx.GetAngle() + 90;
	return std::fmod(angle, 360.0);
}

void Chassis::ZeroYaw() {
	m_navx.ZeroYaw();
}

double Chassis::GetLeftVelocity() const {
	return m_lEnc.GetRate();
}
double Chassis::GetRightVelocity() const {
	return m_rEnc.GetRate();
}
double Chassis::GetVelocity() const {
	return (m_lEnc.GetRate() + m_rEnc.GetRate()) / 2;
}

double Chassis::GetLeftDistance() const {
	return m_lEnc.GetDistance();
}
double Chassis::GetRightDistance() const {
	return m_rEnc.GetDistance();
}
double Chassis::GetDistance() const {
>>>>>>> robotA-autoOH
	return (m_lEnc.GetDistance() + m_rEnc.GetDistance()) / 2;
}

void Chassis::ResetEncoders() {
	m_rEnc.Reset();
	m_lEnc.Reset();
}
