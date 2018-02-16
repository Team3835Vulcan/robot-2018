#ifndef Collector_H
#define Collector_H

#include <Commands/Subsystem.h>
#include <memory>
#include "ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h"
#include <DigitalInput.h>
#include <DoubleSolenoid.h>

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;

class Collector : public frc::Subsystem {
private:
	Collector();

	std::unique_ptr<WPI_VictorSPX> m_rCollector;
	std::unique_ptr<WPI_VictorSPX> m_lCollector;
	std::unique_ptr<frc::DigitalInput> m_collectSwitch;

	std::unique_ptr<WPI_VictorSPX> m_rotor;
	std::unique_ptr<frc::DigitalInput> m_downSwitch;
	std::unique_ptr<frc::DigitalInput> m_upSwitch;

	std::unique_ptr<frc::DoubleSolenoid> m_claw;
	bool m_isOpen;

public:
	static Collector& GetInstance();


	void InitDefaultCommand();
	void Periodic();

	void Collect(double val);
	void Rotate(double val);

	bool IsUp();
	bool IsDown();
	bool CubeIn();

	void SwitchPump();
};

#endif  // Collector_H
