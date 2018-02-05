#ifndef Collector_H
#define Collector_H

#include <Commands/Subsystem.h>
#include <memory>
#include <Talon.h>
#include <DigitalInput.h>
#include <DoubleSolenoid.h>

class Collector : public frc::Subsystem {
private:
	std::unique_ptr<frc::Talon> m_rCollector;
	std::unique_ptr<frc::Talon> m_lCollector;
	std::unique_ptr<frc::DigitalInput> m_collectSwitch;

	std::unique_ptr<frc::Talon> m_rotor;
	std::unique_ptr<frc::DigitalInput> m_downSwitch;
	std::unique_ptr<frc::DigitalInput> m_upSwitch;

	std::unique_ptr<frc::DoubleSolenoid> m_claw;
	bool m_isOpen;

public:
	Collector();
	void InitDefaultCommand();

	void Collect(double val);
	void Rotate(double val);

	bool IsUp();
	bool IsDown();
	bool CubeIn();

	void SwitchPump();
};

#endif  // Collector_H
