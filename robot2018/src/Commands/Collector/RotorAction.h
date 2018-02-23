#ifndef RotorAction_H
#define RotorAction_H

#include <Commands/Command.h>
#include <memory>
#include <Subsystems/Collector/Collector.h>
#include <util/PIDController.h>

class RotorAction : public frc::Command {
private:
	Collector::ROTOR_POS m_pos;
	std::unique_ptr<vulcan::PIDController> m_controller;

public:
	RotorAction(Collector::ROTOR_POS pos);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RotorAction_H
