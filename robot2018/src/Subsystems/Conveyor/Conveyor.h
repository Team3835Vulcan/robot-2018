#ifndef Conveyor_H
#define Conveyor_H

#include <Commands/Subsystem.h>
#include <memory>
#include <Talon.h>

using frc::Talon;

class Conveyor : public Subsystem {
private:
	Conveyor();

	std::unique_ptr<Talon> m_engine;
public:
	static Conveyor& GetInstance();

	enum SIDE {LEFT, RIGHT};

	void Eject(SIDE s);
	void Stop();
};

#endif  // Conveyor_H
