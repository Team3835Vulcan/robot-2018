#ifndef ElevCtrl_H
#define ElevCtrl_H

#include <Commands/Command.h>

class ElevCtrl : public frc::Command {
private:
	double m_val;

public:
	ElevCtrl(double val);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ElevCtrl_H
