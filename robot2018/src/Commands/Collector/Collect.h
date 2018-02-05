#ifndef Collect_H
#define Collect_H

#include <Commands/Command.h>

class Collect : public frc::Command {
private:
	double m_val;

public:
	Collect(double val);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Collect_H
