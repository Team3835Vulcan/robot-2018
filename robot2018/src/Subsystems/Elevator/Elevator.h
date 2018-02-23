#ifndef Elevator_H
#define Elevator_H

#include <Commands/Subsystem.h>
#include <memory>
#include <DigitalInput.h>
#include <Talon.h>

using frc::Talon;

class Elevator : public frc::Subsystem {
private:
	Elevator();

	std::unique_ptr<Talon> m_eng1;
	std::unique_ptr<Talon> m_eng2;

	std::unique_ptr<frc::DigitalInput> m_elevUp;
	std::unique_ptr<frc::DigitalInput> m_elevDown;
public:
	static Elevator& GetInstance();

	void Periodic();
	void InitDefaultCommand();

	void Set(double val);

	bool IsUp();
	bool IsDown();
};

#endif  // Elevator_H
