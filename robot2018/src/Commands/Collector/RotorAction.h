#ifndef RotorAction_H
#define RotorAction_H

#include <Commands/Command.h>

class RotorAction : public frc::Command {
private:
	double m_val;

public:
	RotorAction(double val);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RotorAction_H
