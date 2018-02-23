#ifndef Elevator_H
#define Elevator_H

#include <Commands/Subsystem.h>
#include <memory>
#include <DigitalInput.h>
#include "ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h"

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;

class Elevator : public frc::Subsystem {
private:
	Elevator();

	std::unique_ptr<WPI_VictorSPX> m_eng1;
	std::unique_ptr<WPI_VictorSPX> m_eng2;

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
