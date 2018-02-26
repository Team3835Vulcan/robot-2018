#ifndef Collector_H
#define Collector_H

#include <Commands/Subsystem.h>
#include <memory>
#include <Talon.h>
#include <DigitalInput.h>
#include <DoubleSolenoid.h>
#include <AnalogInput.h>

using frc::Talon;

class Collector : public frc::Subsystem {
private:
	Collector();

	std::unique_ptr<Talon> m_rCollector;
	std::unique_ptr<Talon> m_lCollector;
	std::unique_ptr<frc::DigitalInput> m_collectSwitch;

	std::unique_ptr<Talon> m_rotor;
	std::unique_ptr<frc::DigitalInput> m_downSwitch;
	std::unique_ptr<frc::DigitalInput> m_upSwitch;
	std::unique_ptr<frc::AnalogInput> m_potentiometer;

	std::unique_ptr<frc::DoubleSolenoid> m_claw;

public:
	static Collector& GetInstance();

	enum ROTOR_POS {UP, DOWN};
	enum COLLECTMODE {EJECT, COLLECT};
	enum CLAWMODE {OPEN, CLOSE};

	double ROTOR_VOLT_UP;
	double ROTOR_VOLT_DOWN;

	void InitDefaultCommand();
	void Periodic();

	void Collect(COLLECTMODE mode);
	void StopCollect();

	void Rotate(double val);
	double GetRotorPos() const;

	bool IsUp();
	bool IsDown();
	bool CubeIn();

	void SwitchClaw(CLAWMODE mode);
	CLAWMODE GetClawMode();
};

#endif  // Collector_H
