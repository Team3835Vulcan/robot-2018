#ifndef Conveyor_H
#define Conveyor_H

#include <Commands/Subsystem.h>
#include <memory>
#include "ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h"

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;

class Conveyor : public frc::Subsystem {
private:
	Conveyor();

	WPI_VictorSPX m_engine;
public:
	static Conveyor& GetInstance();

	enum SIDE {LEFT, RIGHT};

	void Eject(SIDE s);
	void Stop();
};

#endif  // Conveyor_H
